/*
    .-=: Домашнее Задание №7 :=-.
        Ученик - Шелест Александр

    Создать программу, имитирующую многоквартирный дом.
    Нужно создать классы: "Человек", "Квартира", "Дом".

    Каждый из классов наполнить конструкторами, деструкторами, 
    методами для предметной области класса. Использовать динамические массивы.
*/

#if defined(_WIN32) || defined(_WIN64)
    #include <Windows.h>
    #define handlelocale() SetConsoleCP(1251); SetConsoleOutputCP(1251)
#else // !_WIN32 && !_WIN64
    #include <cstdlib>
    #include <clocale>
    #define handlelocale() setlocale(LC_ALL, "")
#endif

#include <iostream>
#include <ctime>
#include "Building.h"

#define N_NAMES 10
const char* names[] = { "Имя", "Имя2", "Николай", "Арсений", "Ангелина", "Камилла", "Александр", "Игорь", "Валерий", "Анна" };
#define N_SURNAMES 8
const char* surnames[] = { "", "Фамилия", "Фамильн(-ый/-ая)", "Фамиль", "Фамильченко", "Шелестенко", "Тестов(-ый/-ая)", "Кондрат" };
#define N_FATHERS 6
const char* fathers[] = { "", "Николаев(-ич/-на)", "Арсеньев(-ич/-на)", "Александров(-ич/-на)", "Игорев(-ич/-на)", "Валерьев(-ич/-на)" };

#define PAUSE_INFO  std::cout << "Нажмите любую клавишу для отображения информации о доме...\n"; \
                    std::cin.get(); \
                    building.displayInfo()

Human generateHuman()
{
    Human newHuman;

    newHuman.setAge(rand() % 70);
    newHuman.setName(names[rand() % N_NAMES]);
    newHuman.setSurname(surnames[rand() % N_SURNAMES]);
    newHuman.setFathers(fathers[rand() % N_FATHERS]);

    return newHuman;
}

Apartament generateApartament(int number)
{
    int nTenants = rand() % 5 + 1;
    Human** tenants = new Human*[nTenants];

    for (int i = 0; i < nTenants; i++)
        tenants[i] = new Human(generateHuman());

    Apartament apartament(number, nTenants, tenants);

    for (int i = 0; i < nTenants; i++)
        delete tenants[i];
    delete[] tenants;

    return apartament;
}

Building generateBuidling(const char* name)
{
    int nApartaments = rand() % 4 + 4;

    Apartament** apartaments = new Apartament*[nApartaments];

    for (int i = 0; i < nApartaments; i++)
        apartaments[i] = new Apartament(generateApartament(i + 1));

    Building building(name, nApartaments, apartaments);

    for (int i = 0; i < nApartaments; i++)
        delete apartaments[i];
    delete[] apartaments;

    return building;
}

int main()
{
    // добавить поддержку кириллицы
    handlelocale();

    srand(time(0));

    std::cout << "\t.-=: Домашнее Задание №7 :=-.\n"
              << "\t\tУченик - Шелест Александр\n"
              << "\nСоздать программу, имитирующую многоквартирный дом.\n"
              << "Нужно создать классы: \"Человек\", \"Квартира\", \"Дом\".\n"
              << "Каждый из классов наполнить конструкторами, деструкторами,\n"
              << "методами для предметной области класса. Использовать динамические массивы.\n\n\n";

    std::cout << "Генерируем дом...\n";

    Building building = generateBuidling("test building 1");
    
    PAUSE_INFO;

    std::cout << "Добавляем новую квартиру №23...\n";

    Human** newtenants = new Human*[3] {
        new Human("Вручную", "Добавленный", "Житель1", 16),
        new Human("Вручную", "Добавленный", "Житель2", 26),
        new Human("Вручную", "Добавленный", "Житель3", 36)
    };
    Apartament newApartament(23, 3, newtenants);
    building.addApartament(newApartament);

    PAUSE_INFO;

    std::cout << "Пытаемся удалить 3 случайных квартиры (возможно попадутся несуществующие индексы)...\n";
    for (int i = 0; i < 3; i++)
        building.removeApartament(rand() % 6);

    PAUSE_INFO;
    
    std::cout << "Добавляем нового жителя во вторую по счету квартиру...\n";
    Apartament* apartament = (Apartament*)building.getApartament(1);
    apartament->addTenant(generateHuman());

    PAUSE_INFO;

    std::cout << "Пытаемся удалить 3 случайных жителя в этой же квартире...\n";
    for (int i = 0; i < 3; i++)
        apartament->removeTenant(rand() % apartament->getNumberOfTenants());

    PAUSE_INFO;


    std::cout << "Тест завершен. Нажмите любую клавишу для выхода...\n";
    std::cin.get();
    return 0;
}

