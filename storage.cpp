/*
 * storage.cpp
 *
 *  Created on: Nov 19, 2016
 *      Author: tetsurou
 */

#include <fstream>
#include "storage.hpp"

using namespace std;

void CanInfoStorage::regist_canid(CanInfo caninfo){

}

void CanInfoStorage::get_canid(can_kind_t key){

}

can_kind_t CanInfoStorage::get_cankind(canid_t canid){
	//search canid
	map<canid_t,CanInfo>::iterator itr = canid_storage.find(canid);

	//return cankind
	return itr->second.kind;
}
