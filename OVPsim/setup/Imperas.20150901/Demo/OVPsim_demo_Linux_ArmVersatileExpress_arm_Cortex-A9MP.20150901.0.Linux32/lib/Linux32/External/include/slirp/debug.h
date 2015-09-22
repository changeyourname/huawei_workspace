/*
 *
 * Please read the file COPYRIGHT for the
 * terms and conditions of the copyright.
 */
#ifndef SLIRP_DEBUG_H
#define SLIRP_DEBUG_H

#define DEBUG_SLIRP_ON  1
#define DEBUG_SOCKET_ON 1

#    if DEBUG_SLIRP_ON
#        define DEBUG_SLIRP(fmt, ...)    { if(slirp_debug()) vmiPrintf(fmt, ## __VA_ARGS__); }
#    else
#        define DEBUG_SLIRP(...)
#    endif


#    if DEBUG_SOCKET_ON
#        define DEBUG_SOCKET(fmt, ...)    { if(slirp_debug()) vmiPrintf(fmt, ## __VA_ARGS__); }
#    else
#        define DEBUG_SOCKET(...)
#    endif

#endif
