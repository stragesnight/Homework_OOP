/*
	-= Домашнее Задание №18 =-
		Ученик: Шелест Александр

	Создать родительский класс Pet и дочерние классы Dog, Cat, Parrot.
	Использовать конструктор для задания характеристик объектам классов.
*/

#include <iostream>	// std::cout
#include <string.h>	// std::string; memset()


#if defined (_WIN32) or defined (_WIN64)
# include <Windows.h>
# define handle_locale() SetConsoleCP(1251); SetConsoleOutputCP(1251)
#else
# include <clocale>
# define handle_locale() setlocale(LC_ALL, "")
#endif

class Pet
{
protected:
	std::string name;		// имя
	std::string breed;	// порода
	std::string phrase;	// фраза
	unsigned age; 		// возраст

public:
	// конструктор
	Pet(std::string name, std::string breed, std::string phrase, unsigned age)
	{
		this->name = name;
		this->breed = breed;
		this->phrase = phrase;
		this->age = age;
	}

	// ввести данные с клавиатуры
	void setData()
	{
		char buff[128]{};
		
		std::cout << "Введите имя (строка): ";
		std::cin.ignore(1, '\0');
		std::cin.getline(buff, 128);
		name = std::string(buff);
		memset(buff, 0, 128);

		std::cout << "Введите породу (строка): ";
		std::cin.getline(buff, 128);
		breed = std::string(buff);
		memset(buff, 0, 128);
		
		std::cout << "Введите фразу (строка): ";
		std::cin.getline(buff, 128);
		phrase = std::string(buff);

		std::cout << "Введите возраст (целое число, в годах): ";
		std::cin >> age;
	}

	// вывести данные на экран
	void display()
	{
		std::cout << "Имя: \"" << name << "\";\n";
		std::cout << "Порода: \"" << breed << "\";\n";
		std::cout << "Возраст (в годах): " << age << ";\n";
	}

	// "подать голос"
	void giveSound()
	{
		std::cout << name << " говорит \"" << phrase << "\"!\n";
	}
};

// Класс Dog, наследуемый от Pet
class Dog : public Pet
{
private:
	float tailLength; 		// длина хвоста
	bool isChewingBones;	// грызет ли кости

public:
	// конструктор
	Dog(std::string name, std::string breed, std::string phrase, unsigned age,
		float tailLength, bool isChewingBones)
		: Pet(name, breed, phrase, age)
	{
		this->tailLength = tailLength;
		this->isChewingBones = isChewingBones;
	}

	// ввести данные с клавиатуры
	void setData()
	{
		std::cout << "\t-= Собака =-\n";

		// вызвать этот метод родительского класса
		Pet::setData();
	
		std::cout << "Введите длину хвоста (число с плавающей точкой, в см): ";
		std::cin >> tailLength;

		std::cout << "Введите, грызет ли собака кость (0 = нет, 1 = да): ";
		std::cin >> isChewingBones;
	}

	// вывести характеристики на экран
	void display()
	{
		std::cout << "\t-= Собака =-\n";

		// вызвать этот метод родительского класса
		Pet::display();
		
		std::cout << "Длина хвоста: " << tailLength << " см;\n";
		std::cout << "Грызет кости?: ";
		if (isChewingBones)
		{
			std::cout << "да.\n\n";
		}
		else
		{
			std::cout << "нет.\n\n";
		}
	}
};


// Класс Cat, наследуемый от Pet
class Cat : public Pet
{
private:
	float sleepTime; 			// время сна
	bool isSleepingOnTheKeyboard;	// спит ли на клавиатуре

public:
	// конструктор
	Cat(std::string name, std::string breed, std::string phrase, unsigned age,
		float sleepTime, bool isSleepingOnTheKeyboard)
		: Pet(name, breed, phrase, age)
	{
		this->sleepTime = sleepTime;
		this->isSleepingOnTheKeyboard = isSleepingOnTheKeyboard;
	}

	// ввести данные с клавиатуры
	void setData()
	{
		std::cout << "\t-= Кот =-\n";

		// вызвать этот метод родительского класса
		Pet::setData();
	
		std::cout << "Введите время сна кошки (число с плавающей точкой, в часах): ";
		std::cin >> sleepTime;

		std::cout << "Введите, спит ли кот на клавиатуре (0 = нет, 1 = да): ";
		std::cin >> isSleepingOnTheKeyboard;
	}

	// вывести характеристики на экран
	void display()
	{
		std::cout << "\t-= Кот =-\n";

		// вызвать этот метод родительского класса
		Pet::display();

		std::cout << "Время сна: " << sleepTime << " час(-а/-ов);\n";
		std::cout << "Спит на клавиатуре?: ";
		if (isSleepingOnTheKeyboard)
		{
			std::cout << "да.\n\n";
		}
		else
		{
			std::cout << "нет.\n\n";
		}
	}
};


// Класс Parrot, наследуемый от Pet
class Parrot : public Pet
{
private:
	unsigned numOfKnownMelodies; // количество известных мелодий
	float flySpeed; 		// скорость полёта

public:
	// конструктор
	Parrot(std::string name, std::string breed, std::string phrase, unsigned age,
		unsigned numOfKnownMelodies, float flySpeed)
		: Pet(name, breed, phrase, age)
	{
		this->numOfKnownMelodies = numOfKnownMelodies;
		this->flySpeed = flySpeed;
	}

	// ввести данные с клавиатуры
	void setData()
	{
		std::cout << "\t-= Попугай =-\n";

		// вызвать этот метод родительского класса
		Pet::setData();
	
		std::cout << "Введите количество мелодий, которые знает попугай (целое число): ";
		std::cin >> numOfKnownMelodies;

		std::cout << "Введите скорость полёта попугая (в м/с): ";
		std::cin >> flySpeed;
	}
	
	// вывести характеристики на экран
	void display()
	{
		std::cout << "\t-= Попугай =-\n";

		// вызвать этот метод родительского класса
		Pet::display();

		std::cout << "Количество известных мелодий: " << numOfKnownMelodies << " шт.;\n";
		std::cout << "Скорость полёта: " << flySpeed << " м/с.\n\n";
	}
};



int main()
{
	handle_locale();

	std::cout << "\t-= Домашнее Задание №18 =-\n"
		<< "\t\tУченик: Шелест Александр\n\n"
		<< "Создать родительский класс Pet и дочерние классы Dog, Cat, Parrot.\n"
		<< "Использовать конструктор для задания характеристик объектам классов.\n\n";

	int input;
		
	std::cout << "Выберите животное для создания по его номеру в списке: \n";
	std::cout << "1. Собака\n";
	std::cout << "2. Кошка\n";
	std::cout << "3. Попугай\n\n";
	
	std::cout << "ваш выбор: ";
	std::cin >> input;

#	define display_wrapper(v) \
	std::cout << "\nХарактеристики введённого вами животного: \n"; \
	v.display(); \
	v.giveSound()
		
	switch (input)
	{
	case 1:
	{
		Dog dog("Собака", "без породы", "гав", 0, 0, 0);
		dog.setData();
		display_wrapper(dog);

		break;
	}
	case 2:
	{
		Cat cat("Кот", "без породы", "мяв", 0, 0, 0);
		cat.setData();
		display_wrapper(cat);
		
		break;
	}
	case 3:
	{
		Parrot parrot("Попугай", "без породы", "твиньк", 0, 0, 0);
		parrot.setData();
		display_wrapper(parrot);

		break;
	}
	default:
		std::cout << "Введены некорректные данные.";
		std::cin.ignore(1, '\0');
		std::cin.get();
		return 0;
	}

	std::cin.ignore(1, '\0');
	std::cin.get();
	return 0;
}

