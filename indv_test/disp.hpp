/*
 * disp.hpp
 *
 *  Created on: Dec 31, 2016
 *      Author: tetsurou
 */

#ifndef INDV_TEST_DISP_HPP_
#define INDV_TEST_DISP_HPP_

#include <QtWidgets>

class MeterContents{
public:
	double kph;

	MeterContents& operator=(const MeterContents &arg){
		kph = arg.kph;
		return *this;
	}
};

class MeterWidget : public QWidget
{
public:
	MeterWidget(int,char**);
  void show_meter(void);
  void set_fullscreen(void);
  void set_contents(MeterContents *src);

private:
  QWidget *window;
  QApplication *app;
  QLabel *spdlabel;
  MeterContents *showing;
};

#endif /* INDV_TEST_DISP_HPP_ */
