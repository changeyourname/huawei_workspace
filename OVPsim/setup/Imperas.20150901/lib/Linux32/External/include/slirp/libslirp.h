#ifndef _LIBSLIRP_H
#define _LIBSLIRP_H

#include "common.h"
#include "slirp.h"

struct Slirp;
typedef struct Slirp Slirp;

int get_dns_addr(Slirp *slirp, struct in_addr *pdns_addr);


Slirp *net_slirp_init(
        int         restricted,
        const char *vnetwork,
        const char *netmask,
        const char *vhost,
        const char *vhostname,
        const char *tftp_export,
        const char *bootfile,
        const char *vdhcp_start,
        const char *vnameserver,
        void       *netObject
);

void slirp_cleanup(Slirp *slirp);

void slirp_select_fill(Slirp *slirp, int *pnfds, fd_set *readfds, fd_set *writefds, fd_set *xfds);

void slirp_select_poll(Slirp *slirp, fd_set *readfds, fd_set *writefds, fd_set *xfds, u_int timeMS, Bool selectOK);

void slirp_input(Slirp *slirp, const uint8_t *pkt, int pkt_len);

/* you must provide the following functions: */

int slirp_add_hostfwd(Slirp *slirp, int is_udp,
                      struct in_addr host_addr, int host_port,
                      struct in_addr guest_addr, int guest_port,
                      Uns32 *actualHostPort);
//int slirp_remove_hostfwd(Slirp *slirp, int is_udp,
//                         struct in_addr host_addr, int host_port);
//int slirp_add_exec(Slirp *slirp, int do_pty, const void *args,
//                   struct in_addr *guest_addr, int guest_port);

void slirp_connection_info(Slirp *slirp);

//void slirp_socket_recv(Slirp *slirp, struct in_addr guest_addr,
//                       int guest_port, const uint8_t *buf, int size);
//size_t slirp_socket_can_recv(Slirp *slirp, struct in_addr guest_addr,
//                             int guest_port);

#endif
