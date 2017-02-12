/*
 * OpenGC.cpp
 *
 *      Author: Mohamed El Sayed
 *      email : m.elsayed4420@gmail.com
 *      lowlevelcode.blogspot.com
 */


#include "SDatabase.h"
#include "OpenGC.h"

void OpenGeeControler::createNew(){
	SDatabase x;
	string dbName, cfgFile, final_cfg, columns_s;
	ofstream out;
	string dup="y", empty="y";
	vector<string> args;
	args.push_back(";ID : ");
	int columns = 0;
	retry:
	cout<<"Enter the name of the database : ";
	cin>>dbName;
	cfgFile=dbName+".ogc";
	dbName=dbName+".ogdb";
	if(x.db_exists(dbName) || x.db_exists(cfgFile)){
		cout<<"The database already exists, choose another name.\n";
		goto retry;
	}

	cout<<"Enter the number of the columns(the first entry is the ID by default) : ";
	cin.ignore();
	cin>>columns;
	while(columns<=1)
	{
		cout<<"The data columns cannot be less than 2. Enter a valid value : ";
		cin>>columns;
	}
	cin.ignore();
	cout<<"Enter the "<<columns<<" message(s) which will be displayed while entering the data:\n";
	cout<<"("<<"1"<<")>> ID : \n";
	for (int i=2; i<=columns; i++){
		string temp = "";
		cout<<"("<<i<<")>> ";
		getline(cin, temp);
		args.push_back(temp);
	}
	cout<<"Enable ID duplication? enter Y for yes, otherwise for no :";
	cin>>dup;
	if(tolower(dup[0])!='y') dup='n';
	cout<<"Enable empty entries? enter Y for yes, otherwise for no :";
	cin>>empty;
	if(tolower(empty[0])!='y') empty='n';
	out.open(cfgFile.c_str());

	stringstream s;
	s<<columns;
	s>>columns_s;

	final_cfg = "#"+dup+"#"+empty+"#"+columns_s+"#{";
	for(unsigned int i=0; i<args.size(); i++){
		final_cfg+=args[i]+";";
	}
	final_cfg+="}";
	out<<x.hash(final_cfg);
	out.close();
	out.open(dbName.c_str());
	out<<"";
	out.close();
	if(x.db_exists(dbName) && x.db_exists(cfgFile)){
			cout<<"The database has been created successfully.\n";
	}
	else
	{
		cout<<"An error occurred.\n";
	}

}
