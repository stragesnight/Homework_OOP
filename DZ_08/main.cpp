/*
 *  .-=: Домашнее Задание №8 :=-.
 *      Ученик: Шелест Александр
 *    
 * 	Реализовать класс "Автомобиль" (длина, клиренс (высота посадки), объем двигателя, 
 * 	мощность двигателя, диаметр колёс, тип коробки передач).
 * 	Создать функции для задания, отображения и поиска значений.
*/

#include <iostream>
#include <cmath>
#include <clocale>

#if defined (_WIN32) || defined (_WIN64)
# define clrscr() system("cls")
#else
# define clrscr() system("clear")
#endif

#define symval(v) #v << " - " << v
#define diff(a, b) fabs(fabs(a) - fabs(b))

// Двигатель
struct Engine
{
	float volume; 		 				// объем
	float power; 						// мощность
};


// Тип коробки передач
enum TRANSMISSION_TYPE { MANUAL, AUTOMATIC };


// Автомобиль
class Automobile
{
private:
	float length; 						// длина
	float clearance; 					// клиренс
	Engine engine; 						// двигатель
	float wheelDiameter; 				// диаметр колёс
	TRANSMISSION_TYPE transmission; 	// тип коробки передач

public:
	// Конструктор
	Automobile()
	{
		length = clearance = wheelDiameter = 0;
		engine = {};
		transmission = MANUAL;
	}

	// Конструктор
	Automobile(float length, float clearance, const Engine& engine, 
			float wheelDiameter, TRANSMISSION_TYPE transmission)
	{
		// скопировать значения параметров в поля
		
		this->length = length;
		this->clearance = clearance;
		this->engine = { engine.volume, engine.power };
		this->wheelDiameter = wheelDiameter;
		this->transmission = transmission;
	}

	// Деструктор
	~Automobile()
	{
		// обнулить значения полей

		length = clearance = wheelDiameter = 0;
		engine = {};
	}

	// Геттеры

	float getLength() { return length; }
	float getClearance() { return clearance; }
	const Engine& getEngine() { return engine; }
	float getWheelDiameter() { return wheelDiameter; }
	TRANSMISSION_TYPE getTransmissionType() { return transmission; }

	// Сеттеры

	void setLength(float length) { this->length = fabs(length); }
	void setClearance(float clearance) { this->clearance = fabs(clearance); }
	void setEngine(const Engine& engine)
	{
		this->engine.volume = fabs(engine.volume);
		this->engine.power = fabs(engine.power);
	}
	void setWheelDiameter(float wheelDiameter) { this->wheelDiameter = fabs(wheelDiameter); }
	void setTransmissionType(TRANSMISSION_TYPE transmission) { this->transmission = transmission; }

	// Отобразить информацию об автомобиле на экран
	void displayInfo()
	{
		clrscr();

		std::cout << "Длина - " << length << " см\n";
		std::cout << "Клиренс - " << clearance << " см\n\n";
		std::cout << "Двигатель:\n";
		std::cout << "\tОбъем - " << engine.volume << " л\n";
		std::cout << "\tМощность - " << engine.power << " кВ\n\n";
		std::cout << "Диаметр колёс - " << wheelDiameter << " см\n";
		std::cout << "Тип коробки передач - ";
		if (transmission == MANUAL)
			std::cout << "ручная.";
		else
			std::cout << "автоматическая.";
		std::cout << "\n\n";

		std::cout << "оценка автомобиля - " << float(*this) << "\n\n";
	}

	// Искать поле по значению
	float getClosestMatch(float query)
	{
		int closestMatch = 0;
		float minDiff = 0xFFFFFFFF;

		const char* names[] = { "длина", "клиренс", "объем двигателя", "мощность двигателя", "диаметр колёс" };
		const float values[] = { length, clearance, engine.volume, engine.power, wheelDiameter };

		for (int i = 0; i < 5; i++)
		{
			if (diff(values[i], query) < minDiff)
			{
				closestMatch = i;
				minDiff = diff(values[i], query);
			}
		}

		std::cout << "Ближайшее значение к \"" << query << "\" имеет "
			<< names[closestMatch] << " (" << values[closestMatch] << ")\n";

		return values[closestMatch];
	}

	// получить условный "счёт" машины для сравнения с другими
	operator float()
	{
		return (length + clearance + (engine.volume * engine.power) + wheelDiameter);
	}
};


int main()
{
	setlocale(LC_ALL, "rus");

	std::cout << "\t.-=: Домашнее Задание №8 :=-.\n"
 			<< "\t\tУченик: Шелест Александр\n\n"
			<< "Реализовать класс \"Автомобиль\",\n"
			<< "(длина, клиренс (высота посадки), объем двигателя,"
 			<< "мощность двигателя, диаметр колёс, тип коробки передач).\n"
 			<< "Создать функции для задания, отображения и поиска значений.\n\n";
		
	Automobile auto1;

	{

		float input;
		int transmission;
		Engine eng = {};

		std::cout << "Введите данные автомобиля.\n";
		
		std::cout << "\tДлина (см) - ";
		std::cin >> input;
		auto1.setLength(input);

		std::cout << "\tКлиренс (см) - ";
		std::cin >> input;
		auto1.setClearance(input);

		std::cout << "\tДвигатель:\n";

		std::cout << "\t - Объем (л) - ";
		std::cin >> eng.volume;
		std::cout << "\t - мощность (кВ) - ";
		std::cin >> eng.power;
		auto1.setEngine(eng);
		
		std::cout << "\tДиаметр колёс (см) - ";
		std::cin >> input;
		auto1.setWheelDiameter(input);

		std::cout << "\tТип коробки передач:\n";
		std::cout << "\t\t1. Ручная;\n";
		std::cout << "\t\t2. Автоматическая.\n";
		std::cout << "\tВаш выбор - ";
		std::cin >> transmission;
		auto1.setTransmissionType((TRANSMISSION_TYPE)(transmission - 1));
	}


	int menuAction = -1;

	while (menuAction != 0)
	{
		clrscr();

		std::cout << "============\n";
		std::cout << "||  МЕНЮ  ||\n";
		std::cout << "============\n\n";

		std::cout << "1. Отобразить информацию об автомобиле;\n";
		std::cout << "2. Поиск поля по значению;\n\n";
		std::cout << "0. Вызод из программы.\n\n";

		std::cout << "ваш выбор: ";
		std::cin >> menuAction;

		switch (menuAction)
		{
		case 1: 
			auto1.displayInfo(); 
			break;
		case 2:
		{
			float query;
			std::cout << "Введите значение для поиска в автомобиле: ";
			std::cin >> query;
			auto1.getClosestMatch(query);
			break;
		}
		case 0: return 0;
		default:
			std::cout << "Выбран неверный пункт меню."; 
			break;
		}

		std::cin.ignore(1, '\0');
		std::cin.get();
	}

	return 0;
}

