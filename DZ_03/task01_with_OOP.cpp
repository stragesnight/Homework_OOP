/*
	-= ДЗ №3, Задание №1 =-
		Ученик: Шелест Александр
	
	Реализовать класс Дробь. Необходимо хранить числитель и знаменатель в качестве переменных-членов.
	Реализовать методы для ввода данных в переменные-члены и для выполнения арифметических операций.
*/

#include <iostream>
#ifdef _WIN32
	#include <Windows.h>
#else
	#include <clocale>
#endif

// Дробь
class Fraction
{
// приватные поля класса, недоступные извне
private:
	int numerator;		// числитель
	int denominator;	// знаменатель

	// получить наибольшее общее кратное
	int getGreatestCommonDivisor()
	{
		// выбрать большее из двух полей
		int tmp = numerator > denominator ? numerator : denominator;

		// поиск наибольшего общего кратного
		for (int i = tmp; i > 0; i--)
			if (numerator % i == 0 && denominator % i == 0)
				return i;

		// возвратить один если общех кратных не было найдено
		return 1;
	}

// публичные поля класса, доступные для вызова извне
public:
	// конструктор
	// если параметров не предоставлено, дробь будет равна 0/1
	Fraction(int numerator = 0, int denominator = 1)
	{
		// вызвать сеттеры для полей (в сеттерах есть дополнительные проверки)
		setNumerator(numerator);
		setDenominator(denominator);

		// сократить дробь
		normalize();
	}

	// деструктор
	~Fraction()
	{
		// присвоить полям значения ноля
		this->numerator = 0;
		this->denominator = 0;
	}

	// геттеры для полей

	// получить числитель 
	int getNumerator() { return numerator; }
	// получить знаменатель
	int getDenominator() { return denominator; }

	// сеттеры для полей

	// присвоить числитель
	void setNumerator(int numerator) 
	{ 
		this->numerator = numerator;
	}
	// присвоить знаменатель
	void setDenominator(int denominator) 
	{
		// проверка на ноль (на ноль делить невоможно) 
		if (denominator != 0)
			this->denominator = denominator;
		else
			std::cout << "\nERROR: denominator of a fraction number cannot be zero.\n";
	}

	// возвратить дробь как число с плавающей точкой
	float asFloat() { return (float)numerator / (float)denominator; }

	// перевернуть дробь (5/6 ==> 6/5)
	void reverse()
	{
		std::swap(numerator, denominator);
	}

	// сократить дробь
	void normalize()
	{
		// найти наибольшее общее кратное
		int gcd = getGreatestCommonDivisor();

		// поделить поля на наибольшее общее кратное
		numerator /= gcd;
		denominator /= gcd;
	}

	// сложить дробь с другой
	void add(Fraction& other)
	{
		// временная дробь, хранящая изначальное состояние дроби other
		Fraction tmp = other;
		
		// если знаменатели не равны...
		if (denominator != other.getDenominator())
		{
			// умножить обе дроби на знаменатель другой (для уравнения знаменателей)
			tmp.multiply(this->getDenominator());
			this->multiply(other.getDenominator());
		}
		
		// прибавить числитель другой дроби к текущей
		numerator += tmp.getNumerator();

		// сократить дробь
		normalize();
	}
	
	// вычесть другую дробь с этой
	void subtract(Fraction& other)
	{
		// временная дробь, хранящая изначальное состояние дроби other
		Fraction tmp = other;
		
		// если знаменатели не равны...
		if (denominator != other.getDenominator())
		{
			// умножить обе дроби на знаменатель другой (для уравнения знаменателей)
			tmp.multiply(this->getDenominator());
			this->multiply(other.getDenominator());
		}
	
		// вычесть числитель другой дроби с этой
		numerator -= tmp.getNumerator();
		
		// сократить дробь
		normalize();
	}

	// умножить дробь на определённый фактор
	void multiply(int factor)
	{
		// умножить оба поля на фактор
		numerator *= factor;
		denominator *= factor;
	}

	// умножить дробь на другую
	void multiply(Fraction& other)
	{
		// умножить оба поля
		numerator *= other.getNumerator();
		denominator *= other.getDenominator();

		// сократить дробь
		normalize();
	}

	// поделить дробь на определённый фактор
	void divide(int factor)
	{
		// поделить оба поля на фактор
		numerator /= factor;
		denominator /= factor;

		// присвоить знаменателю один, если он равен нулю
		if (denominator == 0)
			denominator++;
	}

	// поделить дробь на другую
	void divide(Fraction& other)
	{
		// временная дробь, хранящяя изначальное состояние дроби other
		Fraction tmp = other;

		// перевернуть другую дробь
		tmp.reverse();
		// кмножить эту дробь на перевёрнутую
		multiply(tmp);
	}

	// вывести дробь на экран консоли
	void print()
	{
		std::cout << numerator << "/" << denominator;
	}
};

int main()
{
// добавить поддержку кирилиицы
#ifdef _WIN32
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
#else
	setlocale(LC_ALL, "Russian");
#endif
	// объявить два объекта класса Fraction
	Fraction a;
	Fraction b;

	// вывести начальный текст на экран
	std::cout << "\t-= ДЗ №3, Задание №1 =-\n";
	std::cout << "Реализовать класс Дробь. Необходимо хранить числитель и знаменатель в качестве переменных-членов.\n";
	std::cout << "Реализовать методы для ввода данных в переменные-члены и для выполнения арифметических операций.\n\n";

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
	std::cin.get();
	return 0;
}
