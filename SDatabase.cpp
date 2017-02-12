/*
 * SDatabase.cpp
 *
 *      Author: Mohamed El Sayed
 *      email : m.elsayed4420@gmail.com
 *      lowlevelcode.blogspot.com
 */


#include "SDatabase.h"

string SDatabase::reader(const string path)
{
		ifstream read;
			string text;
			read.open(path.c_str());
			if(read.is_open())
			{
				while(!read.eof())
				{
					getline(read,text);
				}
				read.close();
			}

		return hash(text);
}

bool SDatabase::exists(const string id)
{
	string text = reader(dbName);
	string::size_type check = text.find(id);
	if(check==string::npos)
	return false;
	else
	return true;
}

void SDatabase::writer(string data)
{
	string prev_data = reader(dbName);
	ofstream write;
	write.open(dbName.c_str());
	write<<hash(prev_data)<<hash(data);
	write.close();
}

bool SDatabase::addNew()
{
		string data, temp;

		for(int loop = 0; loop < entry_count; loop++)
		{
			temp = temp+entries[loop];
		}
		if((temp.find(';')!=string::npos) || (temp.find('%')!=string::npos))
		{
				return false;
		}

		if(enable_empty_entries==false)
		{
			for(int loop = 0; loop < entry_count; loop++)
				{
					if(entries[loop]=="")
						return false;
				}
		}

		if(enable_duplication==true)
		{
			for(int i = 0; i < entry_count; i++)
			{
				data = data+entries[i]+'%';
			}
			data=data+';';
			writer(data);

			return true;
		}
		else if(enable_duplication==false)
		{
			if(exists(entries[0])==true)
				return false;
			else
			{
				for(int i = 0; i < entry_count; i++)
				{
					data = data+entries[i]+'%';
				}

				data=data+';';
				writer(data);

				return true;
			}
		}
		delete [] entries;

	return true;
}

int SDatabase::viewAll()
{

string data = reader(dbName);

if(data.find(';')==string::npos){
	return -1;
}
else
{
	vector<string> columns;
	string::size_type i = 0;
	string::size_type colon = data.find(';');
	while(colon != string::npos)
	{
		columns.push_back(data.substr(i, colon-i));
		i = ++colon;
		colon = data.find(';', colon);

		if(colon == string::npos)
			columns.push_back(data.substr(i, data.length()));
	}
	for(unsigned int columns_count = 0; columns_count < columns.size(); columns_count ++)
	{
		vector<string> elements;
		string::size_type i2 = 0;
		string::size_type perc = columns[columns_count].find('%');
		while(perc != string::npos)
		{
			elements.push_back(columns[columns_count].substr(i2, perc-i2));
			i2 = ++perc;
			perc = columns[columns_count].find('%',perc);
			if(perc==string::npos)
				elements.push_back(columns[columns_count].substr(i2,columns[columns_count].length()));
		}
		for (unsigned int count =0; count<elements.size(); count++)
		{
			cout<<elements[count]<<endl;
		}
		cout<<endl;
	}

}
	return 0;
}


bool SDatabase::searchById(const string id)
{
	string result;
	string data = reader(dbName);
	if (id=="") return false;
	string::size_type get = data.find(id);
	if(get==string::npos) {return false;}
	else
	{
		string temp = data.substr(get, data.length());
		get = temp.find(id);
		string::size_type colon = temp.find(';');
		result = temp.substr(get, colon);
	}
	vector<string> result_vector;
	string::size_type i = 0;
	string::size_type colon_pos = result.find('%');
	while(colon_pos!=string::npos)
	{
		result_vector.push_back(result.substr(i, colon_pos-i));
		i=++colon_pos;
		colon_pos = result.find('%', colon_pos);
		if(colon_pos==string::npos)
			result_vector.push_back(result.substr(i, result.length()));
	}
	for(unsigned int count = 0; count < result_vector.size(); count++)
	{
		cout<<result_vector[count]<<endl;
	}

	return true;
}

bool SDatabase::deleteById(const string id)
{
	ofstream append;
	string data, left, right, temp;
	data = reader(dbName);
	if(id=="") return false;

	string::size_type get = data.find(id);
	if(get==string::npos){return false;}
	else
	{
		right = data.substr(0,get);
		temp = data.substr(get, data.length());
		string::size_type colon = temp.find(';');
		left = temp.substr(colon+1, temp.length());
		data=right+left;
		append.open(dbName.c_str());
		append << hash(data);
		append.close();
		return true;
	}
}

void SDatabase::clear()
{
	ofstream clear;
	clear.open(dbName.c_str());
	clear << "";
	clear.close();

}


int SDatabase::count()
{
	string temp = reader(dbName);
	size_t c = std::count(temp.begin(), temp.end(), ';');

	return c;
}

string SDatabase::hash(const string data)
{
	char key = 'X';
	string output = data;

	for ( unsigned int i = 0; i < data.length(); i++){

		output[i] = data[i] ^ key;
	}

	return output;
}

bool SDatabase::db_exists(const string db)
{
	ifstream f(db.c_str());
	return f.good();
}

int SDatabase::load_db(const string dbPath)
{
	if(db_exists(dbPath+".ogc")==false)
		return 0;
	if(db_exists(dbPath+".ogdb")==false)
		return -1;

	string data = reader(dbPath+".ogc");
	if(data[1]!='n'){
		enable_duplication = true;}
	else {enable_duplication = false;}

	if(data[3]!='n'){
		enable_empty_entries = true;}
	else {enable_empty_entries = false;}

	char temp = data[5];
	entry_count = (int)temp-'0';

	string::size_type i = data.find(';');
	string::size_type colon = data.find(';');
	while( colon != string::npos){
		if(data.substr(i, colon-i)=="") goto xx;
		out_msgs.push_back(data.substr(i, colon-i));
		xx:
		i = ++colon;
		colon = data.find(';', colon);
	}

	dbName = dbPath+".ogdb";
	return 1;
}












