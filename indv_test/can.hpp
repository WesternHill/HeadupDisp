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

class CanController
{
public:
	void get_candev(char *devname,struct sockaddr_can *addr);
	int read_can(char *devname);
private:
};

#endif /* SRC_CAN_HPP_ */
