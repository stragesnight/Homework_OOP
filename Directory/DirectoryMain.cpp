#include <iostream>
#include <string>
#include "Directory.h"
#include <fstream>

using std::cout;
using std::cin;
using std::endl;
using std::cerr;
using std::string;
using std::ifstream;
using std::ofstream;

void menu();
void showfile(ifstream& in, string namefile);
void add(Directory& d, ofstream& out, string namefile);
void searchName(ifstream& in, string namefile);
// �������, ����������� �������� ���� ��� �������� 
// � ������ � ���� ���� ����� �����������
Directory readFile(ifstream& in);

int main()
{
	Directory d;
    string namefile = "directory.txt";
    ofstream out;
    ifstream in;
    char exit;

    do
    {
        system("cls");
        menu();
        char key;
        cout << "Make your choose: "; cin >> key; 

        switch (key)
        {
        case's':
            showfile(in, namefile);
            break;
        case'+':
            cin.get();
            add(d, out, namefile);
            break;
        case'n':
            searchName(in, namefile);
            break;
        }
        cout << "If you want to exit press 'e'"; cin >> exit; 
    } while (exit != 'e');
    system("pause");
    return 0;
}

void menu()
{
    cout << "If you want to review the directory, press 's'\n";
    cout << "If you want to add the directory, press '+'\n";
    cout << "If you want to find the company by name, press 'n'\n";
    cout << "If you want to find the company by owner, press 'o'\n";
    cout << "If you want to find the company by address, press 'a'\n";
    cout << "If you want to find the company by phone number 'p'\n";
    cout << "If you want to find the company by type of the activity 't'\n";
}


void showfile(ifstream& in, string path)
{
    in.open(path);
    if (!in.is_open())
    {
        cerr << "Can not open file for output.\n";
        exit(1);
    }
    else
    {
        char ch;
        while (in.get(ch))
            cout << ch;
    }
    in.close();
}

void add(Directory& d, ofstream& out, string namefile)
{
    out.open(namefile, std::ios::out | std::ios::app);
    if (out.is_open())
    {
        d.setData();
		// ����� � ���� ����� ������������� ��������, � �� ����� out.read
		// ��� ��� �� ����� ��������� ����, � �� ��������
		out << d;
    }
    else
    {
        cerr << "Can not open " << namefile << " file for output.\n";
        exit(1);
    }
    out.close();
}

// // � ��� ������� � ���� ���������� ����� �� ������ ������, ��� ����� ��� ��������� ��������� ���� � ��'���
// ���������� ������� readFile (��, ��� ��������� �����) ����� ������ ������ �� �����. ������ ����� �� ����������.
void searchName(ifstream& in, string namefile)
{
    in.open(namefile);
    
    if(in.is_open())
    {
        string searchname;
        cout << "Enter the name of the company: "; 
		std::cin.ignore(1, '\0'); // ��� ���������� ������ getline
		getline(cin, searchname);

		// ���� ���� �� ����� ������ ���������...
		while (!in.eof())
		{
			// ��������� ���������� �������� �� �����
			Directory d = readFile(in);

			// ���� ��� ������� � ������ ���������...
			if (d.getName() == searchname)
			{
				// ��������! �� ����������!

				cout << "found directory:\n";
				cout << d << endl;
			}
		}
    }
    else
    {
       cerr << "Can not open " << namefile << " file for output.\n";
       exit(1);
    }
    in.close();
}

// �������, ����������� �������� ���� ��� �������� 
// � ������ � ���� ���� ����� �����������
Directory readFile(ifstream& in)
{
	// ������, � ������� ����� ����������� ����� � �����
	char bff[256];
	// ������-���� ��������� �������
	string name;
	string owner;
	string number_phone;
	string address;
	string type_activity;

	// ������ ����� ���������, ��������� �������� ������

	// "The name of the company: "
	in.read(bff, 25);
	getline(in, name);

	// "The owner of the company: "
	in.read(bff, 26);
	getline(in, owner);

	// "The phone number of the company: "
	in.read(bff, 33);
	getline(in, number_phone);

	// "The address of the company: "
	in.read(bff, 28);
	getline(in, address);

	// "The type of activity of the company: "
	in.read(bff, 37);
	getline(in, type_activity);

	// �������� � ����������� ���������������� �������
	return Directory(name, owner, number_phone, address, type_activity);
}

