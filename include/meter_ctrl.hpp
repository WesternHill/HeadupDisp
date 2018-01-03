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
#include "meter_ctrl.hpp"
#include "conn.hpp"
#include "storage.hpp"
#include "can.hpp"

typedef struct st_thread_arg{
	void *mctrl;
	can_decoded_value *can_db;
}thread_arg;

class MeterController{

public:
	MeterController();
	void main_loop(can_decoded_value *can_db);
	void get_MeterContents(MeterContents *mc);
	void start_thread(can_decoded_value *can_db);
	static void* start_main_loop(void *args);
	// int get_spd(void);
	// int get_canvalue(can_decoded_value *can_db);

	int spd;

private:
	pthread_t thrd_handler;
	pthread_mutex_t thrd_mutex;
	MeterContents latestMcData;
	ConnectionManager *root_conn_mng;
};

#endif /* INDV_TEST_METER_CTRL_CPP_ */
