/*
	-= ДЗ №5, Задание №1 =-
		Ученик: Шелест Александр
	
	Реализовать класс Дробь. Необходимо хранить числитель и знаменатель 
    в качестве переменных-членов.
	Реализовать методы для ввода данных в переменные-члены 
    и для выполнения арифметических операций.
    Класс вынести в отдельный заголовочнй файл.
*/

#include <iostream>
#include <clocale>
#include "Fraction.h"

int main()
{
// добавить поддержку кирилиицы
	setlocale(LC_ALL, "Russian");
	// объявить два объекта класса Fraction
	Fraction a;
	Fraction b;

	// вывести начальный текст на экран
	std::cout << "\t-= ДЗ №4, Задание №1 =-\n";
	std::cout << "Реализовать класс Дробь. Необходимо хранить числитель и знаменатель в качестве переменных-членов.\n";
	std::cout << "Реализовать методы для ввода данных в переменные-члены и для выполнения арифметических операций.\n";
    std::cout << "Класс вынести в отдельный заголовочный файл.\n\n";

	// ввод данных с клавиатуры и обновление полей дроби
	int input;
	std::cout << "Введите первое дробное число (пример: ввод \"5 6\" соответствует дроби 5/6): ";
	std::cin >> input;
	a.setNumerator(input);
	std::cin >> input;
	a.setDenominator(input);

	std::cout << "Введите второе дробное число: ";
	std::cin >> input;
	b.setNumerator(input);
	std::cin >> input;
	b.setDenominator(input);

	std::cout << "\nДробь А: ";
	a.print();
	std::cout << " (" << a.asFloat() << ")";

	std::cout << "\nДробь Б: ";
	b.print();
	std::cout << " (" << b.asFloat() << ")";

	std::cout << "\n\nОбратите внимание - дроби сокращаются автоматически.\n";

	// сложение
	Fraction tmp = a;
	tmp.add(b);
	std::cout << "\n\nА + Б = ";
	tmp.print();
	std::cout << " (" << tmp.asFloat() << ")";

	// вычитание
	tmp = a;
	tmp.subtract(b);
	std::cout << "\nА - Б = ";
	tmp.print();
	std::cout << " (" << tmp.asFloat() << ")";

	// умножение
	tmp = a;
	tmp.multiply(b);
	std::cout << "\nА * Б = ";
	tmp.print();
	std::cout << " (" << tmp.asFloat() << ")";

	// деление
	tmp = a;
	tmp.divide(b);
	std::cout << "\nА / Б = ";
	tmp.print();
	std::cout << " (" << tmp.asFloat() << ")\n\n";

	// завершение программы
    std::cout << "\n\nНажмите любую клавишу для выхода из программы...";
    std::cin.ignore(1, '\0');
	std::cin.get();
	return 0;
}
