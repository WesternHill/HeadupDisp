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
#include "frame.hpp"

#define OUTBUF_LEN 500

using namespace std;

int main(int argc,char **argv)
{
	MeterController *mctrl = new MeterController();
  ConnectionManager *conn_mng = new ConnectionManager();
	Coder *coder = new Coder();
  can_decoded_value value;

	mctrl->start_thread(&value);

  int skt = 0;
  int conn_result = 0;
  conn_result = conn_mng->setup_srv(&skt);
  if(conn_result < 0){
    fprintf(stderr,"[FTL] Setup server failed.\n");
    return -1;
  }

	int write_len = 0;
	int sent_len = 0;
	int result = 0;
  char buf[OUTBUF_LEN] = {0};
  while(1){
    usleep(5000);
    // printf("[SEND] %d\n",value.speed);
    // sprintf(buf,"%d",value.speed);
 		result = coder->encode_json(&value, OUTBUF_LEN, buf ,&write_len);
		if(result == FAIL){
			fprintf(stderr,"[ERR] Encoding failure\n");
		}

    result = conn_mng->send_data(&skt,buf,sizeof(buf),&sent_len);//　TODO: re-make socket when connection discarded.
		if(result == FAIL){
			conn_mng->conn_srv(&skt);
			fprintf(stderr,"[ERR] Sending failure\n");
		}
  }


	// return app.exec();
  return 0;
}
