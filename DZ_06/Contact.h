// файл, содержащий объявление класса Контакт

#include <iostream>
#include <cstring>

// Контакт телефонной книги
class Contact
{
private:
    char* name;         // имя
    char* surname;      // фамилия
    char* fathers;      // отчество
    char* phoneNumber;  // номер телефона

    // скопировать строку src в dst
    void copyString(char*& dst, const char* src);

public:
    // конструктор
    Contact(const char* phoneNumber = "", const char* name = "", 
            const char* surname = "", const char* fathers = "");
    // деструктор
    ~Contact();

    // геттеры для полей

    const char* getName() { return name; }
    const char* getSurname() { return surname; }
    const char* getFathers() { return fathers; }
    const char* getPhoneNumber() { return phoneNumber; }

    // сеттеры для полей

    void setName(const char* name) { copyString(this->name, name); }
    void setSurname(const char* surname) { copyString(this->surname, surname); }
    void setFathers(const char* fathers) { copyString(this->fathers, fathers); }
    void setPhoneNumber(const char* phoneNumber) { copyString(this->phoneNumber, phoneNumber); }

    // проверить, подходит ли этот контакт по критерию поиска
    bool isMatchFor(const char* query);
    // вывести информацию об объекте на экран
    void display();
};

