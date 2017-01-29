/*
 * meter_ctrl.hpp
 *
 *  Created on: Jan 26, 2017
 *      Author: tetsurou
 */

#ifndef INDV_TEST_METER_CTRL_CPP_
#define INDV_TEST_METER_CTRL_CPP_

#include <pthread.h>
#include "disp.hpp"

class MeterController{

public:
	MeterController();
	void main_loop(void);
	void get_MeterContents(MeterContents *mc);
	void start_thread();
	static void* start_main_loop(void *args);

private:
	pthread_t thrd_handler;
	pthread_mutex_t thrd_mutex;
	MeterContents latestMcData;
};

#endif /* INDV_TEST_METER_CTRL_CPP_ */
