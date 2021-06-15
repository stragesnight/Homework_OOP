// файл, содержащий объявление класса Apartament

#include "Human.h"

// Квартира
class Apartament
{
private:
    // (программа отказывалась корректно вызывать деструкторы с Human*,
    // поэтому пришлось использовать Human**)
    Human** tenants;        // массив жителей квартиры
    int nTenants;           // количество жителей
    int number;             // номер квартиры

public:
    // конструктор
    Apartament(int number = 0, int nTenants = 0, const Human* const* tenants = nullptr);
    // конструктор копирования
    Apartament(const Apartament& other);
    // деструктор
    ~Apartament();

    // геттеры для полей

    const Human* getTenant(const int index);
    const Human* const* getTenants() { return tenants; }
    const int getNumberOfTenants() { return nTenants; }
    const int getNumber() { return number; }

    // сеттеры для полей

    void setTenant(const int index, const Human& tenant);
    void setTenants(const Human* const* tenants, const int size);
    void setNumber(const int number);

    // добавить жильца
    void addTenant(const Human& tenant);
    // убрать жильца
    void removeTenant(const int index);

    // вывести информацию о квартире на экран
    void displayInfo();
};

