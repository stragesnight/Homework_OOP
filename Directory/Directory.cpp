#include "Directory.h"
#include<iostream>
using std::cout;
using std::cin;
using std::endl;

Directory::Directory()
{
	name = "";
	owner = "";
	number_phone = "";
	address = "";
	type_activity = "";
}

Directory::Directory(string n, string ow, string nph, string ad, string ta)
{
	name = n;
	owner = ow;
	number_phone = nph;
	address = ad;
	type_activity = ta;
}

Directory::~Directory()
{
}

void Directory::setData()
{
	std::cout << "Enter the name and press Enter-key: "; getline(cin,name);
	std::cout << "Enter the owner of the company and press Enter-key: "; getline(cin, owner);
	std::cout << "Enter the phone number of the company and press Enner-key: "; getline(cin, number_phone);
	std::cout << "Enter the address of the company and press Enter-key: "; getline(cin, address);
	std::cout << "Enter the type of activity of the company and press Enter-key: "; getline(cin, type_activity);

}

string Directory::getName()
{
	return name;
}

string Directory::getOwner()
{
	return owner;
}

string Directory::getNumberP()
{
	return number_phone;
}

string Directory::getTypeA()
{
	return type_activity;
}

void Directory::show()
{
	cout<< "The name of the company: " << name << "\nThe owner of the company: " << owner
		<< "\nThe phone number of the company: " << number_phone << "\nThe address of the company: "
		<< address << "\nThe type of activity of the company: " << type_activity << endl;
}

std::ostream& operator<<(std::ostream& os, Directory& d)
{
	os << "The name of the company: " << d.name << "\nThe owner of the company: " << d.owner
		<< "\nThe phone number of the company: " << d.number_phone << "\nThe address of the company: "
		<< d.address << "\nThe type of activity of the company: " << d.type_activity << endl;
	return os;
}

std::istream& operator>>(std::istream& is, Directory& d)
{
	is >> d.name >> d.owner >> d.number_phone >> d.address >> d.type_activity;
	return is;
}
