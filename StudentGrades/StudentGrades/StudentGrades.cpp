// StudentGrades.cpp : ��������� ������� ������ ��������
//

#include <iostream>
#include <conio.h>
#include <iomanip>
#include "Student.h"

using namespace std;

int main()
{
    setlocale(LC_ALL, "");

    cout << "������������ ��������." << endl << endl;

    // ����������� �������
    Student student;
    
    // ���������� �������� �������
    strcpy_s(student.name, 20, "������ �.�. ");
    student.marks[0] = 10;
    student.marks[1] = 10;
    student.marks[2] = 9;

    // ���������� ������ �������
    double aver = student.getAver();

    // ��������� �������� �������
    cout << student.name << " : " << fixed << setprecision(2) << aver << endl;

    _getch();
    return 0;
}

// ����� ���� ������ �� �����