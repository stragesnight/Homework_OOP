// файл, содержащий реализацию класса Apartament

#include <iostream>
#include "Apartament.h"

Apartament::Apartament(int number, int nTenants, const Human* const* tenants)
{
    // скопировать данные в поля объекта
    this->number = number;
    this->nTenants = nTenants;

    // закончить, если жильцов нету
    if (nTenants == 0)
        return;
    
    // выделить память для жильцов
    this->tenants = new Human*[nTenants];

    // закончить, если жильцы не инициализированы
    if (tenants == nullptr)
        return;
    
    // скопировать жильцов при помощи конструктора копирования
    for (int i = 0; i < nTenants; i++)
        this->tenants[i] = new Human(*(tenants[i]));
    
}

Apartament::Apartament(const Apartament& other)
{
    // скопировать данные в поля объекта, 
    // действия идентичны первому конструктору

    this->number = other.number;
    this->nTenants = other.nTenants;

    if (other.nTenants == 0)
        return;

    this->tenants = new Human*[other.nTenants];

    if (other.tenants == nullptr)
        return;

    for (int i = 0; i < nTenants; i++)
        this->tenants[i] = new Human(*(other.tenants[i]));
}

Apartament::~Apartament()
{
    // освободить память жильцов, если нужно
    
    if (tenants == nullptr)
        return;

    for (int i = 0; i < nTenants; i++)
        delete tenants[i];

    delete[] tenants;
    tenants = nullptr;
}

const Human* Apartament::getTenant(const int index)
{
    // проверить индекс на корректонсть
    if (index < 0 || index >= nTenants)
        return nullptr;

    return tenants[index];
}

void Apartament::setTenant(const int index, const Human& tenant)
{
    // проверить индекс на корректность
    if (index < 0 || index >= nTenants)
        return;

    // использовать конструктор копирования
    tenants[index] = new Human(tenant);
}

void Apartament::setTenants(const Human* const* tenants, const int size)
{
    // освободить память старых жильцов

    if (this->tenants != nullptr)
        delete[] this->tenants;
    this->tenants = nullptr;

    this->nTenants = size;

    if (size == 0)
        return;
    
    // скопировать новых жильцов

    this->tenants = new Human*[size];
    for (int i = 0; i < size; i++)
        this->tenants[i] = new Human(*(tenants[i]));
}

void Apartament::setNumber(const int number)
{
    // проверить номер на корректность
    if (number < 0)
        return;
    this->number = number;
}

void Apartament::addTenant(const Human& tenant)
{
    // создать новый массив размером на один больше
    this->nTenants++;
    Human** newTenants = new Human*[nTenants];

    // скопировать старых жильцов
    for (int i = 0; i < this->nTenants - 1; i++)
        newTenants[i] = new Human(*(this->tenants[i]));

    // поместить нового жильца
    newTenants[this->nTenants - 1] = new Human(tenant);

    // присвоить полю новый массив
    this->tenants = newTenants;
}

void Apartament::removeTenant(const int index)
{
    // проверить индекс на корректность
    if (index < 0 || index >= this->nTenants)
        return;

    // создать новый массив, на один меньше
    
    this->nTenants--;

    Human** newTenants = new Human*[this->nTenants];
    
    // скопировать старых жильцов до места удаления старого
    for (int i = 0; i < index; i++)
        newTenants[i] = new Human(*(this->tenants[i]));

    // скопировать остальных жильцов, сместив индекс
    for (int i = index; i < this->nTenants; i++)
        newTenants[i] = this->tenants[i + 1];

    // присвоить полю новый массив
    this->tenants = newTenants;
}

void Apartament::displayInfo()
{
    // вывести информацию о каждом жильце на экран
    
    std::cout << "Квартира №" << number 
        << ", количество жильцов - " << nTenants << ";\n\n";

    for (int i = 0; i < nTenants; i++)
    {
        std::cout<< '\t' << i + 1 << ". ";
        tenants[i]->displayInfo();
    }
}

