/*
 * slirpReplay.c
 *
 *  Created on: Feb 3, 2012
 *      Author: hall
 *
 * This module records all system calls to the socket interface so a simulation
 * can be played back without external dependencies, hence exactly reproducing
 * a previous run. The replay file is space separated plain text.
 *
 * To record:
 * export IMPERAS_SLIRP_REC=r<ecord>
 * export IMPERAS_SLIRP_LOG=filename
 *
 * to play back:
 * export IMPERAS_SLIRP_REC=p<lay>
 * export IMPERAS_SLIRP_LOG=filename
 */

#include <stdio.h>
#include <string.h>

#include "hostapi/impTypes.h"

#include "vmi/vmiTypes.h"
#include "vmi/vmiMessage.h"
#include "slirp.h"

typedef enum stateTS {
    S_UNKNOWN,
    S_NONE,
    S_RECORD,
    S_REPLAY
} stateT;

static FILE *recordFile;
static Uns32 lineNumber = 1;

#define KEYWORD 128

static stateT getState(void) {
#if (IMPERAS_WINDOWS==1)
    return S_NONE;
#else
    static stateT state = S_UNKNOWN;
    if (state == S_UNKNOWN) {
        const char *fn = getenv("IMPERAS_SLIRP_REC");
        if(fn) {
            switch(fn[0]) {
                case 'r' : state = S_RECORD; break;
                case 'p' : state = S_REPLAY; break;
                default  : state = S_NONE;   break;
            }
        }
    }
    return state;
#endif
}

static FILE *getFile(void) {
#if (IMPERAS_WINDOWS==1)
#else
    if (!recordFile) {
        const char *fn = getenv("IMPERAS_SLIRP_LOG");

        if(fn) {
            switch(getState()) {
                case S_RECORD:
                    recordFile = fopen(fn, "w");
                    vmiPrintf("Recording to %s\n", fn);
                    break;

                case S_REPLAY:
                    recordFile = fopen(fn, "r");
                    vmiPrintf("Replaying from %s\n", fn);
                    break;

                default:
                    break;
            }
            VMI_ASSERT(recordFile, "Failed to open file '%s'", fn);
        }
    }
#endif
    return recordFile;
}

static void checkKeyword(const char *expect, const char *act) {
    VMI_ASSERT( (strcmp(expect,act) == 0), "keyword differs;   exp:%s act:%s    line:%d", expect, act, lineNumber);
}

static void checkSocket(int expect, int act) {
    VMI_ASSERT( (expect == act), "socket differs;   exp:%d act:%d    line:%d", expect, act, lineNumber);
}

static void putBuf(FILE *f, const char *buf, int bytes) {
    while(bytes--) {
        fprintf(f, "%02x", *buf++);
    }
}

static void getBuf(FILE *f, char *buf, int bytes) {
    while(bytes--) {
        int r;
        VMI_ASSERT(fscanf(f, "%02x", &r) == 1, "getBuf failed    line:%d", lineNumber);
        *buf++ = r & 0xff;
    }
}


static void putFDs(FILE *f, int n, int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds) {
    if(n) {
        int i;
        for(i = 0; i < nfds; i++) {
            int r = FD_ISSET(i, readfds);
            int w = FD_ISSET(i, writefds);
            int x = FD_ISSET(i, exceptfds);
            fprintf(f, "   %d %d %d", r,w,x);
        }
    }
    fprintf(f, "\n");
}

static void getFDs(FILE *f, int n, int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds) {
    FD_ZERO(readfds);
    FD_ZERO(writefds);
    FD_ZERO(exceptfds);
    if(n) {
        int i;
        for(i = 0; i < nfds; i++) {
            int r, w, x;
            VMI_ASSERT(fscanf(f, "   %d %d %d", &r, &w, &x) == 3, "    line:%d", lineNumber);

            if(r) FD_SET(i, readfds);
            if(w) FD_SET(i, writefds);
            if(x) FD_SET(i, exceptfds);
        }
    }
}

//
// Cannot set errno on Windows, butthis is only for in-house testing
// so not to worry
static void setErrno(int e) {
#if (IMPERAS_WINDOWS==1)

#else
     errno = e;
#endif
}

int recOpenSocket(int domain, int type, int protocol) {
    const char *key = "socket";
    int ret;

    switch(getState()) {
    case S_UNKNOWN:
    case S_NONE:
        ret = socket(domain, type, protocol);
        break;
    case S_RECORD:
        ret = socket(domain, type, protocol);
        fprintf(getFile(), "%s %d %d %d  %d\n", key, domain, type, protocol, ret);
        fflush(getFile());
        break;

    case S_REPLAY: {
            char akey[KEYWORD];
            int adom, atype, aprot;
            VMI_ASSERT(fscanf(getFile(), "%s %d %d %d %d", akey, &adom, &atype, &aprot, &ret) == 5, "    line:%d", lineNumber);
            checkKeyword(key, akey);
            VMI_ASSERT( (adom   == domain  ),  "domain differs    line:%d", lineNumber);
            VMI_ASSERT( (atype  == type    ),  "type differs    line:%d", lineNumber);
            VMI_ASSERT( (aprot  == protocol),  "protocol differs    line:%d", lineNumber);
            lineNumber++;
            break;
        }
    }
    DEBUG_SOCKET("%s(%d,%d,%d)   result = %d\n", key, domain, type, protocol, ret);
    return ret;
}

int recSendSocket(int s, const void *buf, int bytes, int flags) {
    const char *key = "send";
    int ret;

    switch(getState()) {
    case S_UNKNOWN:
    case S_NONE:
        ret = send(s, buf, bytes, flags);
        break;

    case S_RECORD:
        ret = send(s, buf, bytes, flags);
        fprintf(getFile(), "%s %d %d %d %d\n", key, s, bytes, flags, ret);
        fflush(getFile());
        break;

    case S_REPLAY: {
            char akey[KEYWORD];
            int as, abytes, aflags;
            VMI_ASSERT(fscanf(getFile(), "%s %d %d %d %d", akey, &as, &abytes, &aflags, &ret) == 5, "recSendSocket    line:%d", lineNumber);
            checkKeyword(key, akey);
            VMI_ASSERT( (s == as),         "socket differs    line:%d", lineNumber);
            VMI_ASSERT( (bytes == abytes), "bytes  differ    line:%d", lineNumber);
            VMI_ASSERT( (flags == aflags), "flags  differ    line:%d", lineNumber);
            lineNumber++;
            break;
        }
    }
    DEBUG_SOCKET("%s(%d,%d, %d) = %d\n", key, s, bytes, flags, ret);
    return ret;
}

int recRecvSocket(int s, void *buf, int bytes, int flags) {
    const char *key = "recv";
    int ret;

    switch(getState()) {
    case S_UNKNOWN:
    case S_NONE:
        ret = recv(s, buf, bytes, flags);
        break;

    case S_RECORD:
        ret = recv(s, buf, bytes, flags);
        fprintf(getFile(), "%s %d %d %d %d ", key, s, bytes, flags, ret);
        putBuf(getFile(), buf, ret);
        fprintf(getFile(), "\n");
        fflush(getFile());
        break;

    case S_REPLAY: {
            char akey[KEYWORD];
            int as, abytes, aflags;
            VMI_ASSERT(fscanf(getFile(), "%s %d %d %d %d", akey, &as, &abytes, &aflags, &ret) == 5, "    line:%d", lineNumber);
            checkKeyword(key, akey);
            VMI_ASSERT( (s == as),         "socket differs    line:%d", lineNumber);
            VMI_ASSERT( (bytes == abytes), "bytes  differ    line:%d", lineNumber);
            VMI_ASSERT( (flags == aflags), "flags  differ    line:%d", lineNumber);
            getBuf(getFile(), buf, ret);
            lineNumber++;
            break;
        }
    }
    DEBUG_SOCKET("%s(%d,%d,%d) = %d\n", key, s, bytes, flags, ret);
    return ret;
}

void recCloseSocket(int s) {
    const char *key = "close";

    switch(getState()) {
    case S_UNKNOWN:
    case S_NONE:
        closesocket(s);
        break;

    case S_RECORD:
        fprintf(getFile(), "%s %d\n", key, s);
        closesocket(s);
        fflush(getFile());
        break;

    case S_REPLAY: {
            char akey[KEYWORD];
            int as;
            VMI_ASSERT(fscanf(getFile(), "%s %d", akey, &as) == 2, "    line:%d", lineNumber);
            lineNumber++;
            checkKeyword(key, akey);
            checkSocket(s, as);
            break;
        }
    }
    DEBUG_SOCKET("%s(%d)\n", key, s);
}

int recSetSockOpt(int fd, int level, int optname, void *optval, socklen_t optlen) {
    int ret = -1;

    switch(getState()) {
        case S_UNKNOWN:
        case S_NONE:
        case S_RECORD:
            ret = setsockopt(fd, level, optname, optval, optlen);
            break;

        case S_REPLAY:
            ret = 0;
            break;
    }
    DEBUG_SOCKET("%s(%d,%d,%d) = %d\n", "setsockopt", fd, level, optname, ret);
    return ret;
}

int recConnectSocket(int fd, const struct sockaddr *addr, socklen_t addrlen) {
    const char *key = "connect";
    int ret;
    switch(getState()) {
        case S_UNKNOWN:
        case S_NONE:
            ret = connect(fd, addr, addrlen);
            break;

        case S_RECORD:
            ret = connect(fd, addr, addrlen);
            fprintf(getFile(), "%s %d %d %d\n", key, fd, ret, errno);
            break;

        case S_REPLAY: {
            char akey[KEYWORD];
            int afd;
            int tmperrno;

            VMI_ASSERT(fscanf(getFile(), "%s %d %d %d", akey, &afd, &ret, &tmperrno) == 4, "    line:%d", lineNumber);
            lineNumber++;
            checkKeyword(key, akey);
            checkSocket(fd, afd);
            setErrno(tmperrno);
            break;
        }
    }

    DEBUG_SOCKET("%s(%d,%p,%d) = %d  errno=%d\n", key, fd, addr, addrlen, ret, errno);
    return ret;
}

int recSelectSocket(int nfds,  fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout) {
    const char *key = "select";
    int ret;
    switch(getState()) {
        case S_UNKNOWN:
        case S_NONE:
            setErrno(0);
            ret = select(nfds, readfds, writefds, exceptfds, timeout);
            break;

        case S_RECORD:
            setErrno(0);
            ret = select(nfds, readfds, writefds, exceptfds, timeout);
            fprintf(getFile(), "%s %d %d %d", key, nfds, ret, errno);
            putFDs(getFile(), ret, nfds, readfds, writefds, exceptfds);
            break;

        case S_REPLAY: {
            char akey[KEYWORD];
            int afds;
            int tmperrno;

            VMI_ASSERT(fscanf(getFile(), "%s %d %d %d", akey, &afds, &ret, &tmperrno) == 4, "    line:%d", lineNumber);
            checkKeyword(key, akey);
            checkSocket(nfds, afds);
            getFDs(getFile(), ret, nfds, readfds, writefds, exceptfds);
            lineNumber++;
            setErrno(tmperrno);
            break;
        }
    }

    DEBUG_SOCKET("%s(%d) = %d  errno=%d\n", key, nfds, ret, errno);
    return ret;
}

int recBindSocket(int fd, const struct sockaddr *addr, socklen_t addrlen) {
    const char *key = "bind";
    int ret;
    switch(getState()) {
        case S_UNKNOWN:
        case S_NONE:
            setErrno(0);
            ret = bind(fd, addr, addrlen);
            break;

        case S_RECORD:
            setErrno(0);
            ret = bind(fd, addr, addrlen);
            fprintf(getFile(), "%s %d  %d %d\n", key, fd, ret, errno);
            break;

        case S_REPLAY: {
            char akey[KEYWORD];
            int afd;
            int tmperrno;

            VMI_ASSERT(fscanf(getFile(), "%s %d %d %d", akey, &afd, &ret, &tmperrno) == 4, "    line:%d", lineNumber);
            checkKeyword(key, akey);
            checkSocket(fd, afd);
            lineNumber++;

            // should we only set this if return < 0?
            // That would leave a non-zero errno hanging around
            setErrno(tmperrno);
            break;
        }
    }
    DEBUG_SOCKET("%s(%d) = %d  errno=%d\n", key, fd, ret, errno);
    return ret;
}


int recListenSocket(int fd, int backlog) {
    const char *key = "listen";
    int ret;
    switch(getState()) {
        case S_UNKNOWN:
        case S_NONE:
            setErrno(0);
            ret = listen(fd, backlog);
            break;

        case S_RECORD:
            setErrno(0);
            ret = listen(fd, backlog);
            fprintf(getFile(), "%s %d %d %d %d\n", key, fd, backlog, ret, errno);
            break;

        case S_REPLAY: {
            char akey[KEYWORD];
            int afd;
            int abacklog;
            int tmperrno;

            VMI_ASSERT(fscanf(getFile(), "%s %d %d %d %d", akey, &afd, &abacklog, &ret, &tmperrno) == 5, "    line:%d", lineNumber);
            checkKeyword(key, akey);
            checkSocket(fd, afd);
            VMI_ASSERT( (backlog == abacklog), "backlog differs;   exp:%d act:%d    line:%d", backlog, abacklog, lineNumber);

            lineNumber++;
            setErrno(tmperrno);
            break;
        }
    }
    DEBUG_SOCKET("%s(%d) = %d  errno=%d\n", key, fd, ret, errno);
    return ret;
}

int recAcceptSocket(int fd, struct sockaddr *addr, socklen_t *addrlen) {

    const char *key = "accept";
    int ret;
    switch(getState()) {
        case S_UNKNOWN:
        case S_NONE:
            setErrno(0);
            ret = accept(fd, addr, addrlen);
            break;

        case S_RECORD: {
            setErrno(0);
            ret = accept(fd, addr, addrlen);

            // get contents of address structure

            struct sockaddr_in *sin = (struct sockaddr_in*) addr;
            Uns32 port = sin->sin_port;
            Uns32 ip   = sin->sin_addr.s_addr;
            Uns32 len  = *addrlen;

            fprintf(getFile(), "%s %d %x %d %d   %d %d\n", key, fd, ip, port, len, ret, errno);
            break;
        }
        case S_REPLAY: {
            char akey[KEYWORD];
            int afd;
            int tmperrno;

            Uns32 port;
            Uns32 ip;
            Uns32 len;

            VMI_ASSERT(fscanf(getFile(), "%s %d %x %d %d %d %d", akey, &afd, &ip, &port, &len, &ret, &tmperrno) == 7, "    line:%d", lineNumber);
            checkKeyword(key, akey);
            checkSocket(fd, afd);

            // write back to address structure
            struct sockaddr_in *sin = (struct sockaddr_in*) addr;
            sin->sin_port        = port;
            sin->sin_addr.s_addr = ip;
            *addrlen             = len;

            lineNumber++;
            setErrno(tmperrno);
            break;
        }
    }
    DEBUG_SOCKET("%s(%d) = %d  errno=%d\n", key, fd, ret, errno);
    return ret;
}

int recShutdownSocket(int fd, int how) {
    const char *key = "shutdown";
    int ret;
    switch(getState()) {
        case S_UNKNOWN:
        case S_NONE:
            setErrno(0);
            ret = shutdown(fd, how);
            break;

        case S_RECORD:
            setErrno(0);
            ret = shutdown(fd, how);
            fprintf(getFile(), "%s %d %d %d %d\n", key, fd, how, ret, errno);
            break;

        case S_REPLAY: {
            char akey[KEYWORD];
            int afd;
            int ahow;
            int tmperrno;

            VMI_ASSERT(fscanf(getFile(), "%s %d %d %d %d", akey, &afd, &ahow, &ret, &tmperrno) == 5, "    line:%d", lineNumber);
            checkKeyword(key, akey);
            checkSocket(fd, afd);
            VMI_ASSERT( (how == ahow), "how differs;   exp:%d act:%d    line:%d", how, ahow, lineNumber);

            lineNumber++;
            setErrno(tmperrno);
            break;
        }
    }
    DEBUG_SOCKET("%s(%d,%d) = %d  errno=%d\n", key, fd, how, ret, errno);
    return ret;
}






