// файл, содержащий реализацию класса Building

#include <iostream>
#include <cstring>
#include "Building.h"

Building::Building(const char* name, int nApartaments, const Apartament* const* apartaments)
{
    // скопировать данные в поля объекта

    generateString(this->name, name);
    this->nApartaments = nApartaments;

    // завершить, если количество квартир равно нулю
    if (nApartaments == 0)
        return;

    this->apartaments = new Apartament*[nApartaments];

    // завершить, если квартиры не инициализированы
    if (apartaments == nullptr)
        return;

    // скопировать квартиры в поле объекта
    for (int i = 0; i < nApartaments; i++)
        this->apartaments[i] = new Apartament(*(apartaments[i]));
}

Building::Building(const Building& other)
{
    // те же действия, что и в первом конструкторе
    // за исключением источника данных

    generateString(this->name, other.name);
    this->nApartaments = other.nApartaments;

    if (other.nApartaments == 0)
        return;

    this->apartaments = new Apartament*[other.nApartaments];

    if (other.apartaments == nullptr)
        return;

    for (int i = 0; i < other.nApartaments; i++)
        this->apartaments[i] = new Apartament(*(other.apartaments[i]));
}

Building::~Building()
{
    // освободить динамическую память квартир,
    // если есть что освобождать

    if (apartaments == nullptr)
        return;

    for (int i = 0; i < nApartaments; i++)
        delete apartaments[i];

    delete[] apartaments;
    apartaments = nullptr;
}

void Building::generateString(char*& field, const char* src)
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

const Apartament* Building::getApartament(const int index)
{
    // проверить индекс на корректонсть
    if (index < 0 || index >= nApartaments)
        return nullptr;

    return apartaments[index];
}

void Building::setApartament(const int index, const Apartament& apartament)
{
    // проверить индекс на корректонсть
    if (index < 0 || index >= nApartaments)
        return;

    apartaments[index] = new Apartament(apartament);
}

void Building::setApartaments(const Apartament* const* apartaments, const int size)
{
    // освободить память старых квартир
    if (this->apartaments != nullptr)
        delete[] this->apartaments; 
    this->apartaments = nullptr;

    this->nApartaments = size;

    // завершить, если размер равен нулю
    if (size == 0)
        return;

    // скопировать новые квартиры в поле объекта
    this->apartaments = new Apartament*[size];
    for (int i = 0; i < size; i++)
        this->apartaments[i] = new Apartament(*(apartaments[i]));
}

void Building::setName(const char* name)
{
    // удалить старое имя и скопировать новое

    if (this->name != nullptr)
        delete[] this->name;
    generateString(this->name, name);
}

void Building::addApartament(const Apartament &apartament)
{
    // создать новый динамический массив размером на один больше
    this->nApartaments++;
    Apartament** newApartaments = new Apartament*[nApartaments];

    // скопировать данные со старого массиа
    for (int i = 0; i < this->nApartaments - 1; i++)
        newApartaments[i] = new Apartament(*(this->apartaments[i]));

    // добавить новую квартиру в конец
    newApartaments[this->nApartaments - 1] = new Apartament(apartament);

    // присвоить полю новый массив
    this->apartaments = newApartaments;
}

void Building::removeApartament(const int index)
{
    // проверить индекс на корректность
    if (index < 0 || index >= this->nApartaments)
        return;

    // создать новый массив размером на один меньше
    
    this->nApartaments--;
    Apartament** newApartaments = new Apartament*[this->nApartaments];
    
    // скопировать квартиры до удаляемого индекса
    for (int i = 0; i < index; i++)
        newApartaments[i] = new Apartament(*(this->apartaments[i]));

    // скопировать остальные квартиры, сместив индекс
    for (int i = index; i < this->nApartaments; i++)
        newApartaments[i] = this->apartaments[i + 1];

    // присвоить полю новый массив
    this->apartaments = newApartaments;
}

void Building::displayInfo()
{
    // вывести информацию о доме

    std::cout << "Дом \"" << name << "\", количество квартир - "
        << nApartaments << "\n\n";

    // вывести информацию каждой квартиры
    for (int i = 0; i < nApartaments; i++)
    {
        apartaments[i]->displayInfo();
        std::cout << '\n';
    }
}

