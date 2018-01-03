/*
 * can.hpp
 *
 *  Created on: Apr 17, 2017
 *      Author: tetsurou
 */

#ifndef SRC_CAN_HPP_
#define SRC_CAN_HPP_

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <net/if.h>
#include <unistd.h>
#include <assert.h>


#define CANID_ENG 0x410
#define CANID_VDC_ABS 0x512
#define CANID_GEAR 0x411

typedef struct st_can_decoded_value{
	int speed;
	double tach;
	int fuel_lv;
	char gear;
}can_decoded_value;

class CanController
{
public:
	int get_candev(const char *devname,struct sockaddr_can *addr);
	int read_can(const char *devname);
	int rdy_recv_can(const char *devname,struct sockaddr_can *addr,can_decoded_value *can_dv);

	double speed;
	double tach;
	can_decoded_value *can_value;

private:

	void decode(struct canfd_frame *frame);
	double decodeSpeed(struct canfd_frame *frame);
	double decodeEng(struct canfd_frame *frame);
	char decodeGear(struct canfd_frame *frame);


};


#endif /* SRC_CAN_HPP_ */
