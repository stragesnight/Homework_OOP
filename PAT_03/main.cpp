/*
 * 	-= Паттерны Проектирования, ДЗ №3 =-
 * 	 	Ученик: Шелест Александр
 * 	
 * 	Пользуясь примерами из методичной книги, создать многофайловый проект
 * 	для выбранного паттерна.
*/

#include "Car.h"

int main() 
{
	//Введем данные
	std::string manufacturer;
	std::string description;
	std::string color;
	int year;

	std::cout << std::endl << "Input manufacturer of car: " << std::endl;
	std::getline(std::cin, manufacturer);
	std::cout << "Input description of car: " << std::endl;
	std::getline(std::cin, description);
	std::cout << "Input color of car: " << std::endl;
	std::getline(std::cin, color);
	std::cout << "Input year of car: " << std::endl;
	std::cin >> year;

	//создадим объект
	Car c(manufacturer, description, color, year);
	c.Show();
	std::cout << "Let's clone!\nLet's prototype!" << std::endl;
	
	//клонируем объект
	Car* copy = (Car*)c.Clone();
	copy->Show();

	//удаляем клонированный объект
	delete copy;
	return 0;
}
