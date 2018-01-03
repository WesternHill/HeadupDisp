/*
 * tester.cpp
 *
 *  Created on: Jan 1, 2017
 *      Author: tetsurou
 */
#include <iostream>
#include <unistd.h>
#include <string.h>
#include <stdio.h>


#include "meter_ctrl.hpp"
#include "conn.hpp"
#include "disp.hpp"

using namespace std;

int main(int argc,char **argv)
{
	MeterController *mctrl = new MeterController();
  ConnectionManager *conn_mng = new ConnectionManager();
  can_decoded_value value;

	mctrl->start_thread(&value);

  int skt = 0;
  int conn_result = 0;
  conn_result = conn_mng->setup_srv(&skt);
  if(conn_result < 0){
    fprintf(stderr,"[FTL] Setup server failed.\n");
    return -1;
  }

  char buf[50] = {0};
  while(1){
    usleep(5000);
    printf("[SEND] %d\n",value.speed);
    sprintf(buf,"%d",value.speed);
    conn_mng->send_data(&skt,buf,sizeof(buf));//　TODO: re-make socket when connection discarded.
  }


	// return app.exec();
  return 0;
}
