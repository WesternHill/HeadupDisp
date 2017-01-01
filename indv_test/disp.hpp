/*
 * disp.hpp
 *
 *  Created on: Dec 31, 2016
 *      Author: tetsurou
 */

#ifndef INDV_TEST_DISP_HPP_
#define INDV_TEST_DISP_HPP_

typedef struct struct_meter_contents{
	double kph;

}MeterContents;

class Display{

void show_meter(MeterContents src);
void set_fullscreen(void);

};

#endif /* INDV_TEST_DISP_HPP_ */
