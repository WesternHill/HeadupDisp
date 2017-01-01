#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <net/if.h>
#include <unistd.h>

#include "can.h"
#include "lib.h"
#include "main.hpp"

#define MAXSOCK 2
#define MAXIFNAMES 10

static int  dindex[MAXIFNAMES];
extern int optind, opterr, optopt;


int idx2dindex(int ifidx, int skt) {

	int i;
	struct ifreq ifr;

	for (i=0; i < MAXIFNAMES; i++) {
		if (dindex[i] == ifidx)
			return i;
	}

	/* create new interface index cache entry */

	/* remove index cache zombies first */
	for (i=0; i < MAXIFNAMES; i++) {
		if (dindex[i]) {
			ifr.ifr_ifindex = dindex[i];
			if (ioctl(skt, SIOCGIFNAME, &ifr) < 0)
				dindex[i] = 0;
		}
	}

	for (i=0; i < MAXIFNAMES; i++)
		if (!dindex[i]) /* free entry */
			break;

	if (i == MAXIFNAMES) {
		fprintf(stderr, "Interface index cache only supports %d interfaces.\n",
		       MAXIFNAMES);
	}

	dindex[i] = ifidx;

	ifr.ifr_ifindex = ifidx;
	if (ioctl(skt, SIOCGIFNAME, &ifr) < 0){
		perror("SIOCGIFNAME");
	}

	return i;
}

int main(int argc, char *argv[]){
	fd_set rdfs;
	struct iovec iov;
	struct msghdr msg;
	struct canfd_frame frame;
	struct sockaddr_can addr;
	struct timeval *timeout_current = NULL;
	char ctrlmsg[CMSG_SPACE(sizeof(struct timeval)) + CMSG_SPACE(sizeof(__u32))];
	int devnum = 1;
	int skt[MAXSOCK] = {0};
	int sktidx = 0;
	int running = 1;
	int maxdlen = 0;

	/* these settings are static and can be held out of the hot path */
	iov.iov_base = &frame;
	msg.msg_name = &addr;
	msg.msg_iov = &iov;
	msg.msg_iovlen = 1;
	msg.msg_control = &ctrlmsg;

	addr.can_family = AF_CAN;

	skt[sktidx] = socket(PF_CAN, SOCK_RAW, CAN_RAW);
	if (skt[sktidx] < 0) {
		perror("skt");
		return 1;
	}

	/* Read specified can-dev name */
	char *devname = argv[optind];
	int devname_len = strlen(devname); /* no ',' found => no filter definitions */
	struct ifreq ifr;
	memset(&ifr.ifr_name, 0, sizeof(ifr.ifr_name));
	strncpy(ifr.ifr_name, devname, devname_len);
	if (strcmp("any", ifr.ifr_name)) {
		if (ioctl(skt[sktidx], SIOCGIFINDEX, &ifr) < 0) { //Retrieve the interface index of the interface into ifr_ifindex
			perror("SIOCGIFINDEX");
		}else{
			printf("dev:%s(%d)\n",ifr.ifr_name,ifr.ifr_ifindex);
		}
		addr.can_ifindex = ifr.ifr_ifindex;
	} else{
		addr.can_ifindex = 0; /* any can interface */
	}

	if (bind(skt[sktidx], (struct sockaddr *)&addr, sizeof(addr)) < 0) {
		perror("bind");
		return 1;
	}else{
		printf("binding socket : OK\n");
	}

	while (1 == running) {

		FD_ZERO(&rdfs);
		for (int i=0; i < devnum; i++){
			FD_SET(skt[i], &rdfs);
		}

		if (select(skt[devnum-1]+1, &rdfs, NULL, NULL, timeout_current) <= 0) {
			//perror("select");
			running = 0; //end of mainroop
			continue;
		}

		for (int i=0; i < devnum; i++) {  /* check all CAN RAW skts */

			if (FD_ISSET(skt[i], &rdfs)) {
				int nbytes = 0;

				/* these settings may be modified by recvmsg() */
				iov.iov_len = sizeof(frame);
				msg.msg_namelen = sizeof(addr);
				msg.msg_controllen = sizeof(ctrlmsg);
				msg.msg_flags = 0;

				nbytes = recvmsg(skt[i], &msg, 0);
//				int idx = idx2dindex(addr.can_ifindex, skt[i]);

				if (nbytes < 0) {
					if (errno == ENETDOWN) {
						fprintf(stderr, "interface down\n");
						continue;
					}
					perror("read");
					return 1;
				}

				if ((size_t)nbytes == CAN_MTU)
					maxdlen = CAN_MAX_DLEN;
				else if ((size_t)nbytes == CANFD_MTU)
					maxdlen = CANFD_MAX_DLEN;
				else {
					fprintf(stderr, "read: incomplete CAN frame\n");
					return 1;
				}

				int view = 0x0;
				char buf[1000] = {0};
				sprint_long_canframe(buf, &frame, view, maxdlen);
				printf("recv : %s\n",buf);
			}
			fflush(stdout);
		}
	}

	return 0;
}


