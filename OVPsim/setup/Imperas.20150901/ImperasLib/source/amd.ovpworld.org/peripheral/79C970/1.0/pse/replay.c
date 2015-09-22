/*
 * Copyright (c) 2005-2015 Imperas Software Ltd., www.imperas.com
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
 * either express or implied.
 *
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

/* Records network traffic to a file and allows replay without network.
 * Note that this operates on the network card model, so records raw
 * ethernet packets.
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#include "replay.h"
#include "net.h"
#include "peripheral/bhm.h"


#define PREFIX          "NET_REPLAY"
#define BHM_DIAG_REPLAY (bhmGetDiagnosticLevel() & 8)
#define PACKETS         8
#define MTU             1600

typedef enum logTypeE {
    LT_INPUT_PACKET = 172,
    LT_OUTPUT_PACKET,
    LT_END_OF_GROUP,
    LT_NULL,
    LT_FINISH
} logType;

typedef struct packetS {
    Uns32 length;
    Uns8  data[MTU];
} packet, *packetP;


typedef struct recordStateS {
    Bool  record;               // recording
    Bool  replay;               // replaying
    Int32 etherFD;              // ethereal file number
    Int32 sequence;             // replay sequence number
    Int32 maxLength;            // truncate long etherreal packets?
    Bool  finishedReplay;       // no more in the file, though the simulation could continue
                                // for a few more instructions.
} recordState, *recordStateP;

static recordState state = { 0, 0, -1, 1, 0, False };

Bool recordMode(void)
{
    return state.record;
}

static inline const char *recordType(logType t)
{
    switch(t) {
        case LT_END_OF_GROUP  : return "LT_EOG";
        case LT_INPUT_PACKET  : return "LT_INPUT";
        case LT_OUTPUT_PACKET : return "LT_OUTPUT";
        case LT_FINISH        : return "LT_FINISH";
        case LT_NULL          : return "NULL";
        default               : return "unknown";
    }
}

//
// Open a new log, if logging is turned on.
//
void recordOpen(void)
{
    if (bhmRecordStart()) {
        state.record = True;
        if(BHM_DIAG_REPLAY) {
            bhmMessage("I", PREFIX, "Record Start");
        }
    }
}

//
// Record a finish record.
//
void recordClose(void)
{
    if(recordMode()) {
        bhmRecordFinish();
        state.record = False;
    }
}

//
// Record that a bunch of packets is finished
//
void recordEndOfGroup(void)
{
    if(recordMode()) {
        bhmRecordEvent(LT_END_OF_GROUP, 0, NULL);
    }
}

//
// Record another null poll
//
void recordNull(void)
{
    if(recordMode()) {
        bhmRecordEvent(LT_NULL, 0, NULL);
    }
}

//
// Record one packet (must be preceeded by a Bunch record)
//
void recordPacket(Uns32 bytes, Uns8 *data)
{
    if(recordMode()) {
        bhmRecordEvent(LT_INPUT_PACKET, bytes, data);
    }
}

//
// Complete replay
//
static void replayFinish(double time) {

    if(!state.finishedReplay) {

        if(!time) {
            time = bhmGetCurrentTime();
        }

        if(BHM_DIAG_REPLAY) {
             bhmMessage("I", PREFIX, "%f: Replay finished", time);
        }

        state.finishedReplay = True;
    }
}


//////////////////////////// REPLAY MODE //////////////////////////////////
//
// Use this to see if we are replay mode
//
Bool replayMode(void)
{
    return (state.replay);
}

void replayOpen()
{
    state.replay = bhmReplayStart();
    if(!state.replay){
        return;
    }
    if(BHM_DIAG_REPLAY) {
        bhmMessage("I", PREFIX, "Replay Start");
    }
}

//
// In replay mode this is called every poll period.
//
void replayPoll(void)
{
    Uns8   data[MTU];
    double then;
    Uns32  type;

    while (!state.finishedReplay) {

        Int32 bytes = bhmReplayEvent(&then, &type, sizeof(data), data);

        if (bytes < 0) {

            // detect end-of-file
            replayFinish(0);

        } else {

            state.sequence++;

            switch(type) {

                case LT_NULL:
                    return;

                case LT_END_OF_GROUP:
                    // no more for this poll.
                    return;

                case LT_INPUT_PACKET:
                    if(etherMode()) {
                        etherWriteEntry(bhmGetCurrentTime(),bytes, data);
                    }
                    pcnet_receive(data, bytes);
                    // possibly more for this poll, so go around
                    break;

                case LT_OUTPUT_PACKET:
                    //bhmMessage("I", PREFIX, "Output pkt (null)");
                    break;

                case LT_FINISH:
                    // legacy finish state (no longer generated, may be present
                    // in pre-recorded files)
                    replayFinish(then);
                    return;

                default:
                    bhmMessage("F", PREFIX, "Invalid replay file (strange type)");
                    break;
            }
        }
    }
}

//
// Ethereal compatible log format.
//
// pcap file header

typedef struct pcap_hdr_s {
        Uns32       magic_number;   // magic number
        Uns16       version_major;  // major version number
        Uns16       version_minor;  // minor version number
        Int32       thiszone;       // GMT to local correction
        Uns32       sigfigs;        // accuracy of timestamps
        Uns32       snaplen;        // max length of captured packets, in octets
        Uns32       network;        // data link type
} pcap_hdr_t;

// pcap record header
typedef struct pcaprec_hdr_s {
        Uns32       ts_sec;         // timestamp seconds
        Uns32       ts_usec;        // timestamp microseconds
        Uns32       incl_len;       // number of octets of packet saved in file
        Uns32       orig_len;       // actual length of packet
} pcaprec_hdr_t;

//
// Write a packet to the etherreal log.
// Packets can be truncated to save space. The header records the
// amount logged and the original length of the packet.
// Time is held in unix time format; seconds and microseconds since the epoch.
//
void etherWriteEntry(double time, Uns32 bytes, void *data)
{
    pcaprec_hdr_t hdr;
    Uns64      us = time;
    hdr.ts_sec    = us / 1000000;
    hdr.ts_usec   = us % 1000000;

    hdr.orig_len  = bytes;
    hdr.incl_len  = bytes;
    if(state.maxLength > 0 && hdr.incl_len > state.maxLength) {
        hdr.incl_len = state.maxLength;
    }

    if(write(state.etherFD, &hdr, sizeof(hdr)) == -1) {
        bhmMessage("F", PREFIX, "Failed to write header");
    }
    if(write(state.etherFD, data, hdr.incl_len) == -1) {
        bhmMessage("F", PREFIX, "Failed to write data");
    }
}

//
// if maxLength > -1, all records are truncated to this length
//
void etherOpenLog(const char *logName, Uns32 maxLength)
{
    state.etherFD = open(logName, O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if(!etherMode()) {
        bhmMessage("F", PREFIX, "Failed to open etherreal log '%s'", logName);
    }

    if(maxLength != 0 && maxLength < 32) {
        bhmMessage("F", PREFIX, "Cannot truncate packets to less than 32 bytes");
    }
    state.maxLength = maxLength;

    pcap_hdr_t      pcap_hdr;

    memset(&pcap_hdr, 0, sizeof(pcap_hdr_t));
    pcap_hdr.magic_number   = 0xa1b2c3d4;
    pcap_hdr.version_major  = 2;
    pcap_hdr.version_minor  = 4;
    pcap_hdr.snaplen        = 0xffff;
    pcap_hdr.network        = 1;

    if (write(state.etherFD, &pcap_hdr, sizeof(pcap_hdr_t)) == -1) {
        bhmMessage("F", PREFIX, "Failed to write log");
    }
}

void etherCloseLog(void)
{
    close(state.etherFD);
}

Bool etherMode(void)
{
    return (state.etherFD >= 0);
}
