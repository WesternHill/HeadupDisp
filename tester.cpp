/*
 * tester.cpp
 *
 *  Created on: Jan 1, 2017
 *      Author: tetsurou
 */
#include "disp.hpp"

int main(int argc,char **argv)
{
	Display disp = new Display(argc,argv);
	MeterContents data;
	while(1){
		sleep(1);
		data.kph = 10;
		if(data.kph > 180){
			data.kph=0;
		}else{
			data.kph+=10;
		}
		disp.show_meter();
		disp.set_fullscreen();
	}
}
