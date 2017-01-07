/*
 * main.hpp
 *
 *  Created on: Oct 30, 2016
 *      Author: tetsurou
 */

#ifndef MAIN_HPP_
#define MAIN_HPP_

#include <iostream>
#include <map>

using namespace std;

class CarConfig{
public:
	bool available(void);

private:
	string car_name;
	map<int,string> canid_store; // key:id value:description
};

#endif /* MAIN_HPP_ */
