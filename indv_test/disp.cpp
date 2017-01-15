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
  // configure window
  window = new QWidget;
  this->setGeometry(0, 0, 200, 300);
  this->setWindowTitle("MeterDisp");

  // configure labels
  spdlabel = new QLabel(window);
  spdlabel->setFont(QFont("Times", 40, QFont::Bold));
  spdlabel->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
  spdlabel->setGeometry(0,0,300,300);
  spdlabel->setText("Hello world");

  this->show();
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
  	this->setGeometry((QApplication::desktop()->screenGeometry(0)));
  	this->showFullScreen();
}
