/*
    -= ДЗ №4, Задание №1 =-
        Ученик: Шелест Александр

    Создать класс "Лифт", обеспечивающий:
        - установку диапазона движения лифта;
        - включение / выключение лифта;
        - возвращение текущего состояния лифта;
        - возвращение текущего положения лифта;
        - обработку вызова лифта.
 */

#include <iostream>
#include "Lift.h"

#define step_test(func) std::cin.get(); std::cout << "<-- test action -->\n"; func

void displayLiftInfo(Lift& lift)
{
    std::cout << "===============\n";
    std::cout << "|| LIFT INFO ||\n";
    std::cout << "===============\n";

    std::cout << "Lift: { " << lift.getMinFloor() << ", " << lift.getMaxFloor() << " }\n";
    std::cout << "\tcurrent floor - " << lift.getCurrentFloor() << '\n';
    std::cout << "\tstate - ";
    if (lift.getState() == WORKING)
        std::cout << "working\n\n";
    else
        std::cout << "not working\n\n";
}

int main()
{

    std::cout << "-= ДЗ №4, Задание №1 =-\n\t"
        << "Ученик: Шелест Александр\n\n"
        << "Создать класс \"Лифт\", обеспечивающий:\n\t"
        << "- установку диапазона движения лифта;\n\t"
        << "- включение / выключение лифта;\n\t"
        << "- возвращение текущего состояния лифта;\n\t"
        << "- возвращение текущего положения лифта;\n\t"
        << "- обработку вызова лифта.;\n\n";

    std::cout << "Шагайте по тесту, нажимая клавишу Enter...\n";

    step_test(Lift lift(-2, 12));

    step_test(displayLiftInfo(lift));

    step_test(lift.setMaxFloor(-2));
    step_test(lift.setMaxFloor(14));
    
    step_test(displayLiftInfo(lift));

    step_test(lift.setMinFloor(0));
    step_test(lift.setMinFloor(14));
    step_test(lift.setMinFloor(24));
    step_test(lift.setMaxFloor(0));

    step_test(displayLiftInfo(lift));

    step_test(lift.requestLift(5));
    step_test(lift.requestLift(13));
    step_test(lift.requestLift(-3));
    step_test(lift.setMinFloor(-10));
    step_test(lift.requestLift(-2));

    step_test(displayLiftInfo(lift));

    return 0; 
}

