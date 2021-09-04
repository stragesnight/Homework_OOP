#pragma once
#include <string>
#include <iostream>

/*
* 	Это абстрактный базовый класс Device.
* 	Он определяет функцию Clone, которая составляет
* 	основу паттерна Prototype
*/
class Device 
{
private:
	std::string name; 	// название устройства

public:
	// конструктора
	Device() : Device("Unknown device") {}
	Device(std::string dname)
	{
		SetName(dname);
	}

	// вспомогательные функции
	std::string GetName() const { return name; }
	void SetName(std::string dname) { name = dname; }

	// Чисто виртуальная функция
	// Она будет использоваться для создания копий
	virtual Device* Clone() const = 0;

	// отображение данных
	void Show() const
	{
		std::cout << "\nName is\n" << GetName() << "\n";
	}
};
