#pragma once
#include<string>
using std::string;
class Directory
{
private:
	string name;
	string owner;
	string number_phone;
	string address;
	string type_activity;
public:
	Directory();
	Directory(string n, string ow, string nph, string ad, string ta);
	~Directory();
	void setData();
	string getName();
	string getOwner();
	string getNumberP();
	string getTypeA();
	void show();
	friend std::ostream& operator<<(std::ostream& os, Directory& d);
	friend std::istream& operator>>(std::istream& is, Directory& d);
};

