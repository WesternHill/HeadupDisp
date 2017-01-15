/*
 * disp.hpp
 *
 *  Created on: Dec 31, 2016
 *      Author: tetsurou
 */

#ifndef INDV_TEST_DISP_HPP_
#define INDV_TEST_DISP_HPP_

#include <QtWidgets>

typedef struct struct_meter_contents{
	double kph;

}MeterContents;

class Display : public QMainWindow
{
public:
  Display(int,char**);
  void show_meter(MeterContents *src);
  void set_fullscreen(void);

private:
  QWidget *window;
  QLabel *spdlabel;
};

#endif /* INDV_TEST_DISP_HPP_ */
