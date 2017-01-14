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

#include "disp.hpp"

using namespace std;

int main(int argc,char **argv)
{
  QApplication app(argc,argv);
  Display disp(argc,argv);
  MeterContents data;
  //  disp.show_meter(&data);
  
  while(1){
    sleep(1);
    data.kph = 10;
    if(data.kph > 180){
      data.kph=0;
      break;
    }else{
      data.kph+=10;
    }
    disp.show_meter(&data);
    disp.set_fullscreen();
  }
  

  return app.exec();
}
