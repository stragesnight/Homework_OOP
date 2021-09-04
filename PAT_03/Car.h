#pragma once

#include "Device.h"


/*
 * Конкретный потомок устройства класс Car
 */
class Car : public Device 
{
private:
	//свойства машины
	std::string manufacturer;
	std::string description;
	std::string color;
	int year;

public:
	//конструктора
	Car() : Car("No information", "No description", "No color", 0)
	{ SetName("Car"); }

	Car(std::string cmanufacturer, std::string cdescription,
		std::string ccolor, int cyear);
	
	//вспомогательные функции
	int GetYear() const { return year; }
	std::string GetManufacturer() const { return manufacturer; }
	std::string GetDescription() const { return description; }
	std::string GetColor() const { return color; }

	void SetYear(int cyear) { year = cyear; }
	void SetManufacturer(std::string cmanufacturer) 
	{
		manufacturer = cmanufacturer;
	}
	void SetColor(std::string ccolor) 
	{
		color = ccolor;
	}
	void SetDescription(std::string cdescription) 
	{
		description = cdescription;
	}

	//реализация виртуальной функции в потомке
	Device* Clone() const override;
	void Show() const;
};

