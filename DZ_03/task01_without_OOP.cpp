/*
	-= ДЗ №3, Задание №1 =-
		Ученик: Шелест Александр
	
	Реализовать класс Дробь. Необходимо хранить числитель и знаменатель в качестве переменных-членов.
	Реализовать методы для ввода данных в переменные-члены и для выполнения арифметических операций.
    Этот файл содержит подход к заданию без использования классов.
*/

#include <iostream>
#include <Windows.h>

// Дробь
struct Fraction
{
    int numerator;
    int denominator;
};

// получить наибольшее общее кратное
int getGreatestCommonDivisor(const Fraction& fract)
{
    // выбрать большее из двух полей
    int tmp = fract.numerator > fract.denominator ? fract.numerator : fract.denominator;

    // поиск наибольшего общего кратного
    for (int i = tmp; i > 0; i--)
        if (fract.numerator % i == 0 && fract.denominator % i == 0)
            return i;

    // возвратить один если общех кратных не было найдено
    return 1;
}

float asFloat(const Fraction& fract) 
{ 
    return (float)fract.numerator / (float)fract.denominator;
}

void reverse(Fraction& fract)
{
    std::swap(fract.numerator, fract.denominator);
}

// сократить дробь
void normalize(Fraction& fract)
{
    // найти наибольшее общее кратное
    int gcd = getGreatestCommonDivisor(fract);

    // поделить поля на наибольшее общее кратное
    fract.numerator /= gcd;
    fract.denominator /= gcd;
}

// умножить дробь на определённый фактор
void multiply(Fraction& fract, int factor)
{
    // умножить оба поля на фактор
    fract.numerator *= factor;
    fract.denominator *= factor;
}

// умножить дробь на другую
void multiply(Fraction& that, Fraction& other)
{
    // умножить оба поля
    that.numerator *= other.numerator;
    that.denominator *= other.denominator;

    // сократить дробь
    normalize(that);
}

// сложить дробь с другой
void add(Fraction& that, Fraction& other)
{
    // временная дробь, хранящая изначальное состояние дроби other
    Fraction tmp = other;
    
    // если знаменатели не равны...
    if (that.denominator != other.denominator)
    {
        // умножить обе дроби на знаменатель другой (для уравнения знаменателей)
        multiply(tmp, that.denominator);
        multiply(that, other.denominator);
    }
    
    // прибавить числитель другой дроби к текущей
    that.numerator += tmp.numerator;

    // сократить дробь
    normalize(that);
}


// вычесть другую дробь с этой
void subtract(Fraction& that, Fraction& other)
{
    // временная дробь, хранящая изначальное состояние дроби other
    Fraction tmp = other;
    
    // если знаменатели не равны...
    if (that.denominator != other.denominator)
    {
        // умножить обе дроби на знаменатель другой (для уравнения знаменателей)
        multiply(tmp, that.denominator);
        multiply(that, other.denominator);
    }
 
    // вычесть числитель другой дроби с этой
    that.numerator -= tmp.numerator;
    
    // сократить дробь
    normalize(that);
}
// поделить дробь на определённый фактор
void divide(Fraction& fract, int factor)
{
    // поделить оба поля на фактор
    fract.numerator /= factor;
    fract.denominator /= factor;

    // присвоить знаменателю один, если он равен нулю
    if (fract.denominator == 0)
        fract.denominator++;
}

// поделить дробь на другую
void divide(Fraction& fract, Fraction& other)
{
    // временная дробь, хранящяя изначальное состояние дроби other
    Fraction tmp = other;

    // перевернуть другую дробь
    reverse(tmp);
    // кмножить эту дробь на перевёрнутую
    multiply(fract, tmp);
}

// вывести дробь на экран консоли
void print(const Fraction& fract)
{
    std::cout << fract.numerator << "/" << fract.denominator;
}

int main()
{
	// добавить поддержку кирилиицы
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

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
    a.numerator = input;
	std::cin >> input;
	a.denominator = input;

	std::cout << "Введите второе дробное число: ";
	std::cin >> input;
	b.numerator = input;
	std::cin >> input;
	b.denominator = input;

	std::cout << "\nДробь А: ";
	print(a);
	std::cout << " (" << asFloat(a) << ")";

	std::cout << "\nДробь Б: ";
	print(b);
	std::cout << " (" << asFloat(b) << ")";

	std::cout << "\n\nОбратите внимание - дроби сокращаются автоматически.\n";

	// сложение
	Fraction tmp = a;
	add(tmp, b);
	std::cout << "\n\nА + Б = ";
	print(tmp);
	std::cout << " (" << asFloat(tmp) << ")";

	// вычитание
	tmp = a;
	subtract(tmp, b);
	std::cout << "\nА - Б = ";
	print(tmp);
	std::cout << " (" << asFloat(tmp) << ")";

	// умножение
	tmp = a;
	multiply(tmp, b);
	std::cout << "\nА * Б = ";
	print(tmp);
	std::cout << " (" << asFloat(tmp) << ")";

	// деление
	tmp = a;
	divide(tmp, b);
	std::cout << "\nА / Б = ";
	print(tmp);
	std::cout << " (" << asFloat(tmp) << ")";

	// завершение программы
	_getwch();
	return 0;
}
