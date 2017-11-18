/*
 * disp.cpp
 *
 *  Created on: Dec 31, 2016
 *      Author: tetsurou
 */

#include "disp.hpp"

#include <sstream>
#include <iostream>
#include <QApplication>
#include <QLabel>
#include <QFont>
#include <QVBoxLayout>


using namespace std;

MeterWidget::MeterWidget(int argc,char **argv)
{
  //app = new QApplication(argc,argv);
  QVBoxLayout *layout = new QVBoxLayout();

  // configure window
  this->setGeometry(0, 0, 200, 300);
  this->setWindowTitle("MeterDisp");

  // configure labels
  spdlabel = new QLabel("SPD",this);
  spdlabel->setFont(QFont("Times", 40, QFont::Bold));
  spdlabel->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
  spdlabel->setGeometry(0,0,300,300);
  layout->addWidget(spdlabel);

  setLayout(layout);
}

void MeterWidget::set_contents(MeterContents *src)
{
  if(src == NULL){ return; } // invalid arguments

  *showing = *src;

  // reflesh spdlabel
  ostringstream strs;
  strs << showing->kph;
  QString qstr_kph = QString::fromStdString(strs.str());
  spdlabel->setText(qstr_kph);
  spdlabel->show();
}

void MeterWidget::setValue(double param_spd){
  if(param_spd == speed){
    return;
  }
  speed = param_spd;
  //emit valueChanged(speed);
}

/**
 *
 */
void MeterWidget::show_meter(void)
{
	this->show();
}

/**
 *
 */
void MeterWidget::set_fullscreen(void)
{
  	this->setGeometry((QApplication::desktop()->screenGeometry(0)));
  	this->showFullScreen();
}
