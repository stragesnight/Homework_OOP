// файл, содержащий объявление класса Building

#include "Apartament.h"

// Дом
class Building
{
private:
    char* name;                 // имя дома
    int nApartaments;           // количество квартир
    Apartament** apartaments;   // массив квартир

    void generateString(char*& field, const char* src);

public:
    // конструктор
    Building(const char* name, int nApartaments = 0, 
            const Apartament* const* apartaments = nullptr);
    // конструктор копирования
    Building(const Building& other);
    // деструктор
    ~Building();

    // геттеры для полей

    const Apartament* getApartament(const int index);
    const Apartament* const* getApartaments() { return apartaments; }
    const char* getName() { return name; }
    const int getNumberOfApartaments() { return nApartaments; }
    
    // сеттеры для полей

    void setApartament(const int index, const Apartament& apartament);
    void setApartaments(const Apartament* const* apartaments, const int size);
    void setName(const char* name);

    // добавить новую квартиру (условимся что дом умеет расти)
    void addApartament(const Apartament& apartament);
    // удалить квартиру
    void removeApartament(const int index);

    // вывести информацию о доме на экран
    void displayInfo();
};

