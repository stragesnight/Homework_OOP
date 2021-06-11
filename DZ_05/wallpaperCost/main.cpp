#include <iostream>
#ifdef _WIN32
    #include <Windows.h>
#else
    #include <clocale>
#endif

#include "Apartament.h"

int main()
{
#ifdef _WIN32
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
#else
    setlocale(LC_ALL, "");
#endif

    Apartament apartament;    

    return 0;
}
