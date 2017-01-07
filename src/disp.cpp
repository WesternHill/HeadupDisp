/*
 * disp.cpp
 *
 *  Created on: Dec 31, 2016
 *      Author: tetsurou
 */

#include <QApplication>
#include <QLabel>
#include <QFont>

#include "disp.hpp"

QLabel spdlabel;

using namespace std;

Display::Display(int argc,char **argv){
	QApplication app(argc,argv);
	spdlabel = new QLabel("init");
	label->setfont(QFont("Times", 40, QFont::Bold));

	return app.exec();
}


void Display::show_meter(const MeterContents *src)
{
	String str_kph = new String(src->kph);
	QString qstr_kph = QString::fromStdString(std_kph);
	label->setText(qstr_kph);
	label->show();
}

void Display::set_fullscreen(void)
{
	MyWidget *widget = new MyWidget(this);
	widget->setGeometry((QApplication::desktop()->screenGeometry(0)));
	widget->showFullScreen();
}



