// файл, содержащий реализацию класса Human

#include <iostream>
#include <cstring>
#include "Human.h"

Human::Human(const char* name, const char* surname, const char* fathers, int age)
{
    // скопировать строковые параметры в поля
    generateString(this->name, name);
    generateString(this->surname, surname);
    generateString(this->fathers, fathers);
    // присвоить возраст
    this->age = age;
}

Human::Human(const Human& other)
{
    // присвоить полям значения полей объекта other
    generateString(this->name, other.name);
    generateString(this->surname, other.surname);
    generateString(this->fathers, other.fathers);

    this->age = other.age;
}

Human::~Human()
{
    // освободить динамическую память полей
    // если есть что свобождать

    if (name != nullptr)
        delete[] name;
    if (surname != nullptr)
        delete[] surname;
    if (fathers != nullptr)
        delete[] fathers;
}

void Human::generateString(char*& field, const char* src)
{
    // длина исходной строки 
    int len = strlen(src);
    // занять новую динамическую память
    field = new char[len + 1];

    // скопировать строку
    for (int i = 0; i < len; i++)
        field[i] = src[i];

    field[len] = '\0';
}

void Human::setName(const char* name)
{
    // освободить старую память и скопировать новое значение
    delete[] this->name;
    generateString(this->name, name);
}

void Human::setSurname(const char* surname)
{
    // освободить старую память и скопировать новое значение
    delete[] this->surname;
    generateString(this->surname, surname);
}

void Human::setFathers(const char* fathers)
{
    // освободить старую память и скопировать новое значение
    delete[] this->fathers;
    generateString(this->fathers, fathers);
}

void Human::setAge(const int age)
{
    if (age < 0)
        return;

    this->age = age;
}

void Human::displayInfo()
{
    // последовательно вывести поля на экран
    // если в них содержится информация
    if (*surname != '\0')
        std::cout << surname << ' ';
    if (*name != '\0')
        std::cout << name << ' ';
    if (*fathers != '\0')
        std::cout << fathers << ' ';

    if (age != -1)
        std::cout << "\b, " << age << " лет.";

    std::cout << '\n';
}

