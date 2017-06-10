/*
 * tester.cpp
 *
 *  Created on: Jan 1, 2017
 *      Author: tetsurou
 */
#include <iostream>
#include <unistd.h>
#include <QApplication>
#include <QLabel>
#include <QFont>

#include "../src/meter_ctrl.hpp"
#include "../src/disp.hpp"

using namespace std;

int main(int argc,char **argv)
{
	QApplication app(argc,argv);

	MeterController *mctrl = new MeterController();
	MeterWidget disp(argc,argv);
	MeterContents data;

	mctrl->start_thread();

	data.kph = 10;
	cout << "showing kph:" << data.kph << endl;
	disp.set_fullscreen();
//	disp.set_contents(&data);
	disp.show_meter();

	return app.exec();
}
