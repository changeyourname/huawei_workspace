/* Common header file that is included by all of qemu.  */
#ifndef COMMON_H
#define COMMON_H

/* we put basic includes here to avoid repeating them in device drivers */
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>
#include <string.h>
#include <strings.h>
#include <inttypes.h>
#include <limits.h>
#include <time.h>
#include <ctype.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <assert.h>
#include <signal.h>

#include "hostapi/hostMacros.h"

#ifndef O_LARGEFILE
#define O_LARGEFILE 0
#endif
#ifndef O_BINARY
#define O_BINARY 0
#endif
#ifndef MAP_ANONYMOUS
#define MAP_ANONYMOUS MAP_ANON
#endif
#ifndef ENOMEDIUM
#define ENOMEDIUM ENODEV
#endif
#if !defined(ENOTSUP)
#define ENOTSUP 4096
#endif
#ifndef TIME_MAX
#define TIME_MAX LONG_MAX
#endif

#if (IMPERAS_WINDOWS==1)
#define fsync _commit
#define lseek _lseeki64
int qemu_ftruncate64(int, int64_t);
#define ftruncate qemu_ftruncate64

static inline char *realpath(const char *path, char *resolved_path)
{
    _fullpath(resolved_path, path, _MAX_PATH);
    return resolved_path;
}
#endif

void pstrcpy(char *buf, int buf_size, const char *str);
char *pstrcat(char *buf, int buf_size, const char *s);

#if (IMPERAS_WINDOWS==1)
#define tosRecv(sockfd, buf, len, flags) recv(sockfd, (void *)buf, len, flags)
#else
#define tosRecv(sockfd, buf, len, flags) recv(sockfd, buf, len, flags)
#endif

#define MIN(x,y)  ((x) < (y) ? (x) : (y))
#define MAX(x,y)  ((x) > (y) ? (x) : (y))

#endif
