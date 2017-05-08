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
	UNDEFINED,
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
	canid_t get_canid(can_kind_t key);
	can_kind_t get_cankind(canid_t canid);

private:
	map<canid_t,CanInfo> can_storage;
	map<canid_t,can_kind_t> can_kind_descripter;
};


#endif /* STORAGE_HPP_ */
