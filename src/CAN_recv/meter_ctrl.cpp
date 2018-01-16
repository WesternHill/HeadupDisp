/*
 * MeterController.cpp
 *
 *  Created on: Jan 26, 2017
 *      Author: tetsurou
 */

#include <iostream>
#include <stdio.h>
#include <pthread.h>
#include <assert.h>
#include <thread>

#include "can.h"
#include "type.hpp"

#include "meter_ctrl.hpp"
#include "disp.hpp"
#include "can.hpp"



using namespace std;

// pre declare

/**
 * Construct MeterController class
 */
MeterController::MeterController()
{
}

void MeterController::start_thread(can_decoded_value *can_db)
{
	assert(can_db != NULL);

	thread_arg th_arg;
	th_arg.mctrl = this;
	th_arg.can_db = can_db;
	printf("[DBG] th_arg(%p): mctrl(%p),can_db(%p)\n",&th_arg,(th_arg.mctrl),(th_arg.can_db));

	can_db->speed = 0;
	can_db->tach = 0;
	can_db->fuel_lv = 0;
	can_db->fuel_consumpt = 0;

	// Get ready for run thread
	pthread_mutex_init(&(this->thrd_mutex),NULL); // control priority for variables
	// pthread_create(
	// 		&(this->thrd_handler),
	// 		NULL,
	// 		&MeterController::start_main_loop,
	// 		(void *)&th_arg); // building thread
	std::thread th1(start_main_loop,&th_arg);
  th1.detach();

	cout << "pthread process done" << endl;

}

/**
 *  Start main_loop func at parallel thread
 */
void* MeterController::start_main_loop(void *args)
{
	assert(args != NULL);

	thread_arg *th_arg = (thread_arg *)args;
	printf("[DBG] passed th_arg(%p): mctrl(%p),can_db(%p)\n",th_arg,(th_arg->mctrl),(th_arg->can_db));

	cout << " starting main_loop(MeterController)" << endl;
	(reinterpret_cast<MeterController *>(th_arg->mctrl))->main_loop(th_arg->can_db);

	return (void *)NULL;
}

void MeterController::main_loop(can_decoded_value *can_dtbs){
	assert(can_dtbs != NULL);

	//set up
	CanController *canctrl = new CanController;
	const char *devname="vcan0";
	struct sockaddr_can addr;
	addr.can_family = AF_CAN;

	int rdy_result = 0;
	rdy_result = canctrl->rdy_recv_can(devname,&addr,can_dtbs);
	if(rdy_result < 0){
		fprintf(stderr,"[FTL] Failed to get ready for receive CAN.\n");
		return;
	}

	while(1){
	    pthread_mutex_lock(&(this->thrd_mutex));   // Block until get priority-right, then lock
			int ret = canctrl->read_can(devname);
	    pthread_mutex_unlock(&(this->thrd_mutex)); // Unlock

			if(0 > ret){
					fprintf(stderr,"[ERR] read_can halt with err.¥n");
					return ;
			}
	}
}


/**
 * Get latest meter contents
 */
void MeterController::get_MeterContents(MeterContents *mc)
{
    pthread_mutex_lock(&(this->thrd_mutex));   // Block until get priority-right, then lock
    *mc = latestMcData;
    pthread_mutex_unlock(&(this->thrd_mutex)); // Unlock

}
