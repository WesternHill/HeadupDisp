/*
 * storage.hpp
 *
 *  Created on: Nov 19, 2016
 *      Author: tetsurou
 */

#ifndef STORAGE_HPP_
#define STORAGE_HPP_

#include <iostream>
#include <map>

class CanInfoStorage;

using namespace std;

typedef unsigned int canid_t;

typedef enum e_can_kind_t{
	ENGINE_REV,
	FUEL,
	BLINKER,
}can_kind_t;

typedef struct struct_CanInfo{
	canid_t id; //CAN-ID
	int dlc;	//Data length (typical)
	can_kind_t kind; // descript for canid
}CanInfo;

class CanInfoStorage{
public:
	void regist_canid(CanInfo caninfo);
	void get_canid(can_kind_t key);
	can_kind_t get_cankind(canid_t canid);

private:
	map<can_kind_t,CanInfo> can_storage;
	map<canid_t,CanInfo> canid_storage;
};


#endif /* STORAGE_HPP_ */
