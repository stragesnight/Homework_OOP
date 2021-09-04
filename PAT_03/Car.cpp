#include "Car.h"

//реализация конструктора
Car::Car(std::string cmanufacturer, std::string cdescription,
std::string ccolor, int cyear) 
{
	SetName("Car");
	SetManufacturer(cmanufacturer);
	SetDescription(cdescription);
	SetColor(ccolor);
	SetYear(cyear);
}

//функция клонирования
Device* Car::Clone() const
{
	Car* tempCar = new Car();
	/* Обратите внимание!
	 * При при работе с динамической памятью нужно
	 * определить конструктор копирования, конструктор
	 * переноса и перегрузить оператор =
	 */
	*tempCar = *this;

	return tempCar;
}

//Отображение на экран данных
void Car::Show() const
{
	Device::Show();

	std::cout << "\nDescription of car is\n" << GetDescription() << "\n";
	std::cout << "\nManufacturer of car is\n" << GetManufacturer() << "\n";
	std::cout << "\nYear of car is\n" << GetYear() << "\n";
	std::cout << "\nColor of car is\n" << GetColor() << "\n";
}

