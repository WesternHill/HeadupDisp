/*
 * disp.cpp
 *
 *  Created on: Dec 31, 2016
 *      Author: tetsurou
 */

#include <sstream>
#include <iostream>
#include <QApplication>
#include <QLabel>
#include <QFont>


#include "disp.hpp"

using namespace std;

Display::Display(int argc,char **argv)
{
  spdlabel = new QLabel("init");
  spdlabel->setFont(QFont("Times", 40, QFont::Bold));
}

/**
 *
 */
void Display::show_meter(MeterContents *src)
{
  ostringstream strs;
  strs << src->kph;
  QString qstr_kph = QString::fromStdString(strs.str());
  spdlabel->setText(qstr_kph);
  spdlabel->show();
}

/**
 * 
 */
void Display::set_fullscreen(void)
{
  //	MyWidget *widget = new MyWidget(this);
  //	widget->setGeometry((QApplication::desktop()->screenGeometry(0)));
  //	widget->showFullScreen();
}

