/*
 * canid_finder.cpp
 *
 *  Created on: Oct 24, 2016
 *      Author: tetsurou
 */

#include <fstream>
#include "canid_finder.hpp"

using namespace std;
//
//void CanInfoStorage::regist_canid(CanInfo caninfo){
//
//}
//
//void CanInfoStorage::get_canid(can_kind_t key){
//
//}
//
//void CanInfoStorage::get_cankind(canid_t canid){
//	//search canid
//	map<can_id_t,caninfo>::iterator itr = canid_storage.find(canid);
//
//	//return cankind
//	return itr->second().kind;
//}

//void Finder::canid_finder_main(map<int,string> *canid_store){
//	// ask for operation name
//
//	// get whole can signals
//	string ifstr = "can0";
//	string fout = "./";
//	if(!candump(&ifstr,&fout)){
//		/* TASK ** error processing **/
//	}
//
//	// find specific can-id
//	ifstream canfile;
//	canfile.open(fout,ios::in);
//
//	while(1 < leftline(target_fp)){
//		const int devidenum = 3;
//		devide_file(&fp,devidenum); //devide into 3 pieces
//		for(int i = 0; i < devidenum;i++){
//			canplay(&devided_file);
//			if(operation_repeated()){ break; }
//		}
//		target_fp = devided_file;
//	}
//}

///**
// * canplayer for specified interfaces
// */
//int Finder::canplayer(string *write_if,string *read_if,string *finput){
//	string cmdstr;
//	cmdstr = "canplayer " + write_if + "=" + read_if + " -I " + finput;
//	return exec_cmd(cmdstr);
//}
//
//int Finder::candump(string *ifstr,string *fout){
//	string cmdstr;
//	cmdstr = "candump " + ifstr + "-l >> " + fout;
//	return exec_cmd(cmdstr);
//}
//
//void Finder::exec_cmd(string cmdstr){
//	const char *cmd = cmdstr.c_str();
//	system(cmd);
////	/*TASK -- error processing */
////	if(err){
////		return -1
////	}
//	return 0;
//}
//
//
//void Finder::devide_file(ifstream *fp,int devide){
//
//	// get file line num
//	unsigned int fline_num = 0;
//	string linebuf;
//	while(!File.fail()){
//		string buf;
//		getline(fp,buf);
//		if(!fp->eof()){
//			fline_num++;
//		}
//	}
//
//
//	for(int i = 0; i < devide; i++){
//		unsigned int split_line = fline_num / devide;
//
//		fline_num=0;
//		ofstream split_file("split_file"+i,ios_base::binary);
//		while(fline_num < split_line){
//			string buf;
//			getline(fp,buf);
//			ofs<<buf;
//		}
//
//	}
//}

