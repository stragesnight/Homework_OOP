 // файл, содержащий реализацию класса Контакт
 
#include "Contact.h"

Contact::Contact(const char* phoneNumber, const char* name, 
        const char* surname, const char* fathers)
{
    // скопировать исходные строки в поля объекта
    copyString(this->name, name);
    copyString(this->surname, surname);
    copyString(this->fathers, fathers);
    copyString(this->phoneNumber, phoneNumber);
}

Contact::~Contact()
{
    // освободить динамическую память полей объекта
    if (name != nullptr)
        delete[] name;
    if (surname != nullptr)
        delete[] surname;
    if (fathers != nullptr)
        delete[] fathers;
    if (phoneNumber != nullptr)
        delete[] phoneNumber;
}

void Contact::copyString(char*& dst, const char* src)
{
    // освободить динамическую память, если есть что освобождать
    if (dst != nullptr)
        delete[] dst;

    // длина исходной строки + '\0'
    int len = strlen(src);

    // занять новую динамическую память
    dst = new char[len + 1];

    // скопировать исходную строку в dst
    for (int i = 0; i < len; i++)
        dst[i] = src[i];

    dst[len] = '\0';
}

bool Contact::isMatchFor(const char* query)
{
    // сравнить поля c критерием поиска
    // возвратить true, если хотя бы одно поле совпало
    if (strcmp(name, query) == 0)
        return true;
    if (strcmp(surname, query) == 0)
        return true;
    if (strcmp(fathers, query) == 0)
        return true;
    if (strcmp(phoneNumber, query) == 0)
        return true;

    // возвратить false, если ни одно из полей не совпало
    return false;
}

void Contact::display()
{
    // вывести поля на экран с проверкой на наличие в них информации
    if (*surname != 0)
        std::cout << surname << ' ';

    if (*name != 0)
        std::cout << name << ' ';
    else
        std::cout << "Имя не указано.";

    if (*fathers != 0)
        std::cout << fathers << ' ';

    if (*phoneNumber != 0)
        std::cout << "\n\t" << phoneNumber;
    else
        std::cout << "\n\tНомер телефона не указан.";

    std::cout << '\n';
    for (int i = 0, len = strlen(phoneNumber) + 9; i < len; i++)
        std::cout << '-';
    std::cout << '\n';
}

