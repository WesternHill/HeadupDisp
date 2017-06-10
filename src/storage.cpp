/*
 * storage.cpp
 *
 *  Created on: Nov 19, 2016
 *      Author: tetsurou
 */

#include <fstream>
#include <map>

#include "storage.hpp"

using namespace std;

void CanInfoStorage::regist_canid(CanInfo caninfo){
	can_storage.insert(make_pair(caninfo.id,caninfo));
	can_kind_descripter.insert(make_pair(caninfo.id,caninfo.kind));
}

canid_t CanInfoStorage::get_canid(can_kind_t key){
	canid_t ret;
	map<canid_t,CanInfo>::iterator itr = can_storage.find(key);
	if(itr!= can_storage.end()){
		return itr->first;
	}

	return UNDEFINED;
}

can_kind_t CanInfoStorage::get_cankind(canid_t canid){
	//search canid
	map<canid_t,CanInfo>::iterator itr = can_storage.find(canid);

	//return cankind
	return itr->second.kind;
}
