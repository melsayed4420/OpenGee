/*
 * SDatabase.h
 *
 *      Author: Mohamed El Sayed
 *      email : m.elsayed4420@gmail.com
 *      lowlevelcode.blogspot.com
 */


#ifndef SDATABASE_H_
#define SDATABASE_H_


#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>
#include "OpenGC.h"

using namespace std;

class SDatabase{
	friend class OpenGeeControler;
private:
	string reader(const string);
	void writer(string);
	string dbName;
	string hash (const string);
	bool enable_empty_entries = false;
	bool enable_duplication = true;
	bool db_exists(const string);

public:
	int entry_count=20;
	string *entries = new string[entry_count];
	vector<string> out_msgs;
	int load_db(const string);
	bool exists(const string);
	bool addNew();
	bool deleteById(const string);
	bool searchById(const string);
	int viewAll();
	int count();
	void clear();
};


#endif /* SDATABASE_H_ */
