/*
 * can.cpp
 *
 *  Created on: Apr 2, 2017
 *      Author: tetsurou
 */
#include "can.hpp"
#include "lib.h"
#include "can.h"

#define MAXSOCK 2

static int skt[MAXSOCK] = {0};
static int sktidx = 0;
struct ifreq ifr;

void CanContoller::get_candev(char *devname,struct sockaddr_can *addr){
	/* check parameters*/
	if((NULL != devname) && (NULL != addr)){
		printf("devname=%s\n",devname);
	}else{
		assert(false && "Null passed to get_candev"); // Illegal parameters
	}

	/* Read specified can-dev name */
	int devname_len = strlen(devname); /* no ',' found => no filter definitions */
	memset(&ifr.ifr_name, 0, sizeof(ifr.ifr_name));
	strncpy(ifr.ifr_name, devname, devname_len);

	if (strcmp("any", ifr.ifr_name)) {
		if (ioctl(skt[sktidx], SIOCGIFINDEX, &ifr) < 0) { //Retrieve the interface index of the interface into ifr_ifindex
			perror("SIOCGIFINDEX");
		}else{
			printf("dev:%s(%d)\n",ifr.ifr_name,ifr.ifr_ifindex);
		}
		addr->can_ifindex = ifr.ifr_ifindex;
	} else{
		addr->can_ifindex = 0; /* any can interface */
	}
}

int CanContoller::read_can(char *devname){
	fd_set rdfs;
	struct msghdr msg;
	struct sockaddr_can addr;
	struct iovec iov;
	struct canfd_frame frame;
	struct timeval *timeout_current = NULL;
	char ctrlmsg[CMSG_SPACE(sizeof(struct timeval)) + CMSG_SPACE(sizeof(__u32))];
	int devnum = 1;
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

				/* check interface is available */
				if (nbytes < 0) {
					if (errno == ENETDOWN) {
						fprintf(stderr, "ERR : interface down\n");
						continue;
					}
					perror("read");
					return 1;
				}

				/* check size property */
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

				// regist
				CanInfoStorage strg;
				CanInfo caninfo;
				caninfo.id = frame.can_id;
				caninfo.dlc = frame.len;
				caninfo.kind = strg.get_cankind(frame.can_id);
				strg.regist_canid(caninfo);
			}
			fflush(stdout);
		}
	}
}
