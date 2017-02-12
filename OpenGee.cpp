/*
 * OpenGee Database engine
 * Based on an edited version of SDatabase class
 *
 *      Author : Mohamed El Sayed
 *      email  : m.elsayed4420@gmail.com
 *      lowlevelcode.blogspot.com
 */


#include <iostream>
#include "SDatabase.h"
#include <cstdlib>
#include <sstream>
#include "OpenGC.h"

using namespace std;
void loadDb(string);
void clearScreen()
{
#ifdef _WIN32
	system("cls");
#elif __linux__
	system("clear");
#endif
}
int main(int argc, char* argv[])
{

	if(argc <= 1){
		cout<<"Invalid arguments, type -h for more info.\n";
		return 0;
	}

	string arg = argv[1];

	if(arg=="-n")
	{
		OpenGeeControler db;
		db.createNew();
	}
	else if(arg=="-o")
	{
		if(argc <=2){
			cout<<"Invalid arguments, type -h for more info.\n";
			return 0;}
		string path = argv[2];
		loadDb(path);

	}
	else if(arg=="-h")
	{
		cout<<"OpenGee Database Version 1.0.0\n"<<
				"\nCommands : \n"<<
				"-o [db name] \t\t Open an existing database.\n"<<
				"-n \t\t\t Create a new database.\n"<<
				"-v \t\t\t View version info.\n"<<
				"-a \t\t\t About OpenGee Database.\n";
		cout<<"\nExample : \n"<<
				"opengee -o clients\nLoad a database called 'clients'.\n";
	}
	else if(arg == "-v")
	{
		cout<<"OpenGee Database Version 1.0.0\n";
	}
	else if(arg == "-a")
	{
		cout<<"About OpenGee Database"<<
				"\n\nCreated By : Mohamed El Sayed"<<
				"\nm.elsayed4420@gmail.com"<<
				"\nlowlevelcode.blogspot.com\n";
	}
	else
		cout<<"Invalid arguments, type -h for more info.\n";
	return 0;
}

void loadDb(string path){

	char input[10];
	char confirm[10];
	string id;

	string temp;
	SDatabase db;
	if(db.load_db(path)==0)
	{
		cout<<"The configration file for "<<path<<" database is not exists\n";
		return ;
	}
	else if(db.load_db(path)==-1)
	{
		cout<<"The database "<<path<<" is not exists\n";
		return ;
	}
	else
	{

		do{
			clearScreen();
		cout<<"Select an opertaion : \n"<<
				"\t1- Add New\n"<<
				"\t2- Search By ID\n"<<
				"\t3- Delete By ID\n"<<
				"\t4- View All\n"<<
				"\t5- Count total entries\n"<<
				"\t6- Clear The Database\n"<<
				"\t7- Exit\n"<<
				"\nYour Choice : >> ";
		cin.getline(input, 20);
		if(input[0]=='1'){
			do{
				clearScreen();
				for(int i=0; i<db.entry_count; i++)
				{
					cout<<db.out_msgs[i];
					getline(cin, db.entries[i]);
				}

				if(db.addNew()==false)
				{
						cout<<"An error occurred\n";
						cin.ignore();
						break;
					}
					else
					{
						cout<<"Done\nAdd more [y/n] ? ";
						cin.getline(confirm, 20);
				}

			}while(tolower(confirm[0])=='y');
		}
		else if(input[0]=='2')
		{
			do
					{

						clearScreen();
						cout<<"Enter the user ID : ";
						getline(cin, id);
						cout<<endl;
						if(db.searchById(id)==false)
						{
							cout<<"ID not found\nSearch again [y/n] ? ";
							cin.getline(confirm, 20);
						}
						else
						{

							cout<<"\nSearch again [y/n] ? ";
							cin.getline(confirm, 20);
						}
					}
					while(tolower(confirm[0]=='y'));
		}
		else if(input[0]=='3')
		{
			do{
					clearScreen();

					cout<<"Enter the user ID : ";
					getline(cin, id);

					if(db.deleteById(id)==true)
						{
							cout<<endl<<"Done\nDelete more [y/n] ? ";
							cin.getline(confirm, 20);
						}
					else
					{
						cout<<"An error occurred\nDelete more [y/n] ?";
						cin.getline(confirm, 20);
					}

				  }
				  while(tolower(confirm[0])=='y');
		}
		else if(input[0]=='4')
		{
			clearScreen();
					if(db.viewAll()< 0)
					{
						cout<<"Database is empty\n";
					}

					cout<<"Press enter to continue.";
					cin.ignore();
		}
		else if(input[0]=='5')
		{
				clearScreen();
				int count = db.count();
				cout<<"There are "<<count<<" row(s) stored in the database\n";
				cout<<"Press enter to continue.";
				cin.ignore();
		}
		else if(input[0]=='6')
		{
				clearScreen();
				cout << "Are you sure [y/n] ? ";
				cin.getline(confirm, 20);
				if(tolower(confirm[0]=='y')){
					db.clear();
					cout<<"Done\n";
				}
		}
		}

		while(input[0]!='7');
	}
}

