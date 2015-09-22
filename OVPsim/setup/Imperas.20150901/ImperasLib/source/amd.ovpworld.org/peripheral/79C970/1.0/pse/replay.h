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

/* Records network traffic to a file and allows replay without network. */

#ifndef REPLAY_H
#define REPLAY_H

#include "peripheral/impTypes.h"

//////////////////////////// Record ////////////////////////////////
//
// Return true if recording is active
//
Bool recordMode(void);

//
// Start recording (exits if failure)
//
void recordOpen(void);

//
// Finish recording
//
void recordClose(void);

//
// Record one packet
//
void recordPacket(Uns32 bytes, Uns8 *data);

//
// Record that a bunch of packets is finished
//
void recordEndOfGroup(void);

//
// Record another null poll
//
void recordNull(void);

//////////////////////////////// Replay ////////////////////////////////
//
// Start replay mode
//
void replayOpen(void);

//
// Return true of replay is active
//
Bool replayMode(void);

//
// Fetch from replay file and inject packets into NIC accordingly
// Note that replayPoll will be called exactly as many times and at the
// same simulation times (and deltas) as recordPoll() is called in net.c
//
void replayPoll(void);

////////////////////////// Etherreal compatible log ////////////////////

void etherWriteEntry(double time, Uns32 bytes, void *data);

void etherOpenLog(const char *logName, Uns32 maxLength);

void etherCloseLog(void);

Bool etherMode(void);

#endif /*REPLAY_H*/
