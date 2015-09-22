
#ifndef SLIRP_H
#define SLIRP_H

#include "vmi/vmiMessage.h"
#include "vmi/vmiOSAttrs.h"
#include "vmi/vmiOSLib.h"
#include "vmi/vmiRt.h"
#include "vmi/vmiTypes.h"
#include "vmi/vmiVersion.h"
#include "hostapi/impTypes.h"

#define CPU_PREFIX "slirp"

#define PACKED_STRUCT __attribute__((gcc_struct, packed))


/* Define to 1 if you want KEEPALIVE timers */
#define DO_KEEPALIVE 0

/* Define to sizeof(char) */
#define SIZEOF_CHAR (sizeof(char))

/* Define to sizeof(short) */
#define SIZEOF_SHORT 2

/* Define to sizeof(int) */
#define SIZEOF_INT (sizeof(int))

/* Define to sizeof(char *) */
#define SIZEOF_CHAR_P (sizeof(char*))

#if (IMPERAS_WINDOWS==1)
# include <inttypes.h>

typedef char *caddr_t;

# include <winsock2.h>
# include <windows.h>
# include <ws2tcpip.h>
# include <sys/timeb.h>
# include <iphlpapi.h>

# define EWOULDBLOCK WSAEWOULDBLOCK
# define EINPROGRESS WSAEINPROGRESS
# define ENOTCONN WSAENOTCONN
# define EHOSTUNREACH WSAEHOSTUNREACH
# define ENETUNREACH WSAENETUNREACH
# define ECONNREFUSED WSAECONNREFUSED

struct iovec {
    void *iov_base;
    size_t iov_len;
};

#else
# define ioctlsocket ioctl
# define closesocket(s) close(s)
# if !defined(__HAIKU__)
#  define O_BINARY 0
# endif

#include <sys/uio.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <sys/socket.h>
#include <sys/un.h>
#include <sys/signal.h>
#include <sys/ioctl.h>
#include <sys/select.h>

#endif

#include <sys/types.h>
#include <sys/stat.h>
#include <stddef.h>
#include <sys/time.h>

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <time.h>
#include <string.h>
#include <stdarg.h>

#include <fcntl.h>

int inet_aton(const char *cp, struct in_addr *ia);



/* Avoid conflicting with the libc insque() and remque(), which
   have different prototypes. */
#define insque slirp_insque
#define remque slirp_remque

#include "debug.h"
#include "queue.h"

#include "libslirp.h"
#include "ip.h"
#include "tcp.h"
#include "tcp_timer.h"
#include "tcp_var.h"
#include "tcpip.h"
#include "udp.h"
#include "ip_icmp.h"
#include "mbuf.h"
#include "sbuf.h"
#include "socket.h"
#include "if.h"
#include "main.h"
#include "misc.h"
#include "bootp.h"
#include "tftp.h"

/* osdep.c */
int clo_socket(int domain, int type, int protocol);

#define ETH_ALEN 6
#define ETH_HLEN 14

#define ETH_P_IP  0x0800        /* Internet Protocol packet  */
#define ETH_P_ARP 0x0806        /* Address Resolution packet */

#define ARPOP_REQUEST 1         /* ARP request */
#define ARPOP_REPLY   2         /* ARP reply   */

struct ethhdr {
    unsigned char  h_dest[ETH_ALEN];   /* destination eth addr */
    unsigned char  h_source[ETH_ALEN]; /* source ether addr    */
    unsigned short h_proto;            /* packet type ID field */
};

struct arphdr {
    unsigned short ar_hrd;      /* format of hardware address */
    unsigned short ar_pro;      /* format of protocol address */
    unsigned char  ar_hln;      /* length of hardware address */
    unsigned char  ar_pln;      /* length of protocol address */
    unsigned short ar_op;       /* ARP opcode (command)       */

    /*
     *  Ethernet looks like this : This bit is variable sized however...
     */
    unsigned char ar_sha[ETH_ALEN]; /* sender hardware address */
    uint32_t      ar_sip;           /* sender IP address       */
    unsigned char ar_tha[ETH_ALEN]; /* target hardware address */
    uint32_t      ar_tip;           /* target IP address       */
} PACKED_STRUCT;

#define ARP_TABLE_SIZE 16

typedef struct ArpTable {
    struct arphdr table[ARP_TABLE_SIZE];
    int next_victim;
} ArpTable;

void arp_table_add(Slirp *slirp, uint32_t ip_addr, uint8_t ethaddr[ETH_ALEN]);

bool arp_table_search(Slirp *slirp, uint32_t ip_addr,
                      uint8_t out_ethaddr[ETH_ALEN]);

struct Slirp {
    //QTAILQ_ENTRY(Slirp) entry;
    u_int slirpNumber;

    /* virtual network configuration */
    struct in_addr vnetwork_addr;
    struct in_addr vnetwork_mask;
    struct in_addr vhost_addr;
    struct in_addr vdhcp_startaddr;
    struct in_addr vnameserver_addr;

    struct in_addr client_ipaddr;
    char client_hostname[33];

    int restricted;
    struct timeval tt;
    struct ex_list *exec_list;

    /* mbuf states */
    struct mbuf m_freelist, m_usedlist;
    int mbuf_alloced;

    /* if states */
    int if_queued;          /* number of packets queued so far */
    struct mbuf if_fastq;   /* fast queue (for interactive data) */
    struct mbuf if_batchq;  /* queue for non-interactive data */
    struct mbuf *next_m;    /* pointer to next mbuf to output */

    /* ip states */
    struct ipq ipq;         /* ip reass. queue */
    uint16_t ip_id;         /* ip packet ctr, for ids */

    /* bootp/dhcp states */
    BOOTPClient bootp_clients[NB_BOOTP_CLIENTS];
    char *bootp_filename;

    /* tcp states */
    struct socket tcb;
    struct socket *tcp_last_so;
    tcp_seq tcp_iss;        /* tcp initial send seq # */
    uint32_t tcp_now;       /* for RFC 1323 timestamps */

    /* udp states */
    struct socket udb;
    struct socket *udp_last_so;

    /* icmp states */
    struct socket icmp;
    struct socket *icmp_last_so;

    /* tftp states */
    char *tftp_prefix;
    struct tftp_session tftp_sessions[TFTP_SESSIONS_MAX];

    ArpTable arp_table;

    /* host loopback address */
    struct in_addr loopback_addr;

    u_int time_fasttimo, last_slowtimo;

    struct in_addr dns_addr;
    u_int dns_addr_time;

    // file descriptor masks used by select
    fd_set rfds, wfds, xfds;
    Bool   inPoll;

    void *opaque;
};

#ifndef NULL
#define NULL (void *)0
#endif

#ifndef FULL_BOLT
void if_start(Slirp *);
#else
void if_start(struct ttys *);
#endif


#if (IMPERAS_LINUX==1)
#include <netdb.h>
#endif

#define DEFAULT_BAUD 115200

#define SO_OPTIONS DO_KEEPALIVE
#define TCP_MAXIDLE (TCPTV_KEEPCNT * TCPTV_KEEPINTVL)

/* cksum.c */
int cksum(struct mbuf *m, int len);

/* if.c */
void if_init(Slirp *);
void if_output(struct socket *, struct mbuf *);

/* ip_input.c */
void ip_init(Slirp *);
void ip_input(struct mbuf *);
void ip_slowtimo(Slirp *);
void ip_stripoptions(register struct mbuf *, struct mbuf *);

/* ip_output.c */
int ip_output(struct socket *, struct mbuf *);

/* tcp_input.c */
void tcp_input(register struct mbuf *, int, struct socket *);
int tcp_mss(register struct tcpcb *, u_int);

/* tcp_output.c */
int tcp_output(register struct tcpcb *);
void tcp_setpersist(register struct tcpcb *);

/* tcp_subr.c */
void tcp_init(Slirp *);
void tcp_template(struct tcpcb *);
void tcp_respond(struct tcpcb *, register struct tcpiphdr *, register struct mbuf *, tcp_seq, tcp_seq, int);
struct tcpcb * tcp_newtcpcb(struct socket *);
struct tcpcb * tcp_close(register struct tcpcb *);
void tcp_sockclosed(struct tcpcb *);
int tcp_fconnect(struct socket *);
void tcp_connect(struct socket *);
int tcp_attach(struct socket *);
uint8_t tcp_tos(struct socket *);
int tcp_emu(struct socket *, struct mbuf *);
int tcp_ctl(struct socket *);
struct tcpcb *tcp_drop(struct tcpcb *tp, int err);

#define MIN_MRU 128
#define MAX_MRU 16384

#if (IMPERAS_LINUX==1)
#define min(x,y) ((x) < (y) ? (x) : (y))
#define max(x,y) ((x) > (y) ? (x) : (y))
#endif

#if (IMPERAS_WINDOWS==1)
#undef errno
#define errno (WSAGetLastError())
#endif

#define container_of(ptr, type, member) (  {                    \
        const typeof(((type *) 0)->member) *__mptr = (ptr);     \
        (type *) ((char *) __mptr - offsetof(type, member));})

int  recOpenSocket    (int domain, int type, int protocol);
int  recSendSocket    (int s, const void *buf, int bytes, int flags);
int  recRecvSocket    (int s, void *buf, int bytes, int flags);
void recCloseSocket   (int s);
int  recSetSockOpt    (int fd, int level, int optname, void *optval, socklen_t optlen);
int  recConnectSocket (int fd, const struct sockaddr *addr, socklen_t addrlen);
int  recSelectSocket  (int nfds,  fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout);
int  recBindSocket    (int fd, const struct sockaddr *addr, socklen_t addrlen);
int  recListenSocket  (int fd, int backlog);
int  recAcceptSocket  (int fd, struct sockaddr *addr, socklen_t *addrlen);
int  recShutdownSocket(int fd, int how);

#endif
