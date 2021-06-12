/*
    -= ДЗ №6, ЗАДАНИЕ №1 =-
        Ученик: Шелест Александр
    
    Создать приложение "Телефонная книга". Нужно сохранять данные об абоненте
    внутри соответствующего класса. Наполнить класс переменными-членами, методами,
    конструкторами и деструктором. Реализовать возможности для взаимодействия с базой.
*/

#ifdef _WIN32
    #include <Windows.h>
    #define clrscr() system("cls")
#else
    #include <clocale>
    #define clrscr() system("clear")
#endif

#include <vector>
#include "Contact.h"


void displayContacts(Contact* const* contacts, int size)
{
    for (int i = 0; i < size; i++)
    {
        if (contacts[i] != nullptr)
        {
            std::cout << i + 1 << ". ";
            contacts[i]->display();
        }
    }
}

std::vector<Contact*> searchContacts(Contact* const* contacts, int size, const char* query)
{
    std::vector<Contact*> found;
    found.resize(0);

    for (int i = 0; i < size; i++)
    {
        if (contacts[i]->isMatchFor(query))
            found.push_back(contacts[i]);
    }

    return found;
}

int main()
{
// добавление поддержки кириллицы
#ifdef _WIN32
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
#else
    setlocale(LC_ALL, "");
#endif

    std::cout   << "\t-= ДЗ №6, ЗАДАНИЕ №1 =-\n"
                << "\t\tУченик: Шелест Александр\n"
                << "\nСоздать приложение \"Телефонная книга\". Нужно сохранять данные об абоненте\n"
                << "внутри соответствующего класса. Наполнить класс переменными-членами, методами,\n"
                << "конструкторами и деструктором. Реализовать возможности для взаимодействия с базой.\n\n";

    // объявление массива из объектов класса Контакт
    Contact* contacts[13] {
        new Contact("+380665554231", "Валерий"),
        new Contact("+88005553535", "Ярополк", "Занимательный", "Бургундиевич"),
        new Contact("+25338774564", "Хидэо", "Кинтама"),
        new Contact("+556812235895", "Александр", "Шелестенко"),
        new Contact("+802734057114", "Валерьян", "Карасёвич", "Аркадьевич"),
        new Contact("+38419016354", "Рей", "Аянами"),
        new Contact("+0010010101", "Бинарий"),
        new Contact("+346345798032", "Роман", "Пачинкин"),
        new Contact("+380645552953", "Мама лайф"),
        new Contact("+FF89CEBBA0", "Создание", "Шестнадцатеричное", "Разума"),
        new Contact("+220344678111", "Пётр", "Несторенко", "Альбертович"),
        new Contact("+23849028304", "Валерий", "Жмышенко", "Альбертович"),
        new Contact("+483109-82390", "Хидэо", "Кодзима")
    };

    int input = -1;

    while (input != 0)
    {
        clrscr();

        std::cout << "==============\n";
        std::cout << "||   МЕНЮ   ||\n";
        std::cout << "==============\n\n";

        std::cout << "1. Показать список контактов;\n";
        std::cout << "2. Поиск контактов;\n\n";
        std::cout << "0. Выход из проограммы.\n\n";

        std::cout << "Выберите действие по его номеру в меню: ";
        std::cin >> input;

        switch (input)
        {
        case 1:
            clrscr();
            displayContacts(contacts, 13); 
            break;
        case 2:
        {
            char buff[128] = {};
            do
            {
                std::cout << "Введите критерий для поиска (Имя, фамилия, отчество или номер телефона):\n";
                std::cin.ignore(1, '\0');
                std::cin.getline(buff, 128);

            } while (strlen(buff) == 0);

            clrscr();

            std::vector<Contact*> found = searchContacts(contacts, 13, buff);

            std::cout << "Контактов найдено по запросу \"" << buff << "\": " << found.size() << "\n\n";
            if (found.size() > 0)
                displayContacts(found.data(), found.size());

            break;
        }
        case 0:
            return 0;
        default:
            std::cout << "Введите существующий пункт меню.";
            break;
        }

        std::cout << "\n\nНажмите любую клавишу для выхода в меню...";
        std::cin.ignore(1, '\0');
        std::cin.get();
    }

    // завершение программы
    return 0;
}
