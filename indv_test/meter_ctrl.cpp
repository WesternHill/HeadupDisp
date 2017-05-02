/*
 * MeterController.cpp
 *
 *  Created on: Jan 26, 2017
 *      Author: tetsurou
 */

#include <iostream>
#include <stdio.h>

#include "../indv_test/meter_ctrl.hpp"
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

void MeterController::start_thread()
{
	// Get ready for run thread
	pthread_mutex_init(&(this->thrd_mutex),NULL); // control priority for variables
	pthread_create(
			&(this->thrd_handler),
			NULL,
			&MeterController::start_main_loop,
			this); // building thread
	cout << "pthread process done" << endl;

}

/**
 *  Start main_loop func at parallel thread
 */
void* MeterController::start_main_loop(void *args)
{
	cout << " starting main_loop(MeterController)" << endl;
	reinterpret_cast<MeterController *>(args)->main_loop();
	return (void *)NULL;
}

void MeterController::main_loop(void){
	//set up
	char *devname="can0";
	struct sockaddr_can addr;
	addr.can_family = AF_CAN;

	get_candev(devname,addr);

	while(1){
		read_can();
		cout << "CAN received" << endl;
		// FUNC: convert to MeterContents-type
	    pthread_mutex_lock(&(this->thrd_mutex));   // Block until get priority-right, then lock
		// FUNC: save as latest MeterContent-type data
	    pthread_mutex_unlock(&(this->thrd_mutex)); // Unlock
	    // FUNC: send to Meter
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
