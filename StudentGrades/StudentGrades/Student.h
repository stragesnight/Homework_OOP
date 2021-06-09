#pragma once

// определение класса
class Student
{
private:

public:
    // ФИО
    char name[21];
    // оценки
    int marks[3];

    // прототип метода вычисления среднего балла
    double getAver();
};
