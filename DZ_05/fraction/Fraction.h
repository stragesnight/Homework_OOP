// заголовочный файл, содержащий объявление класса Дробь

#include <iostream>

class Fraction
{
// приватные поля класса, недоступные извне
private:
	int numerator;		// числитель
	int denominator;	// знаменатель

	// получить наибольшее общее кратное
	int getGreatestCommonDivisor();

// публичные поля класса, доступные для вызова извне
public:
	// конструктор
	// если параметров не предоставлено, дробь будет равна 0/1
	Fraction(int numerator = 0, int denominator = 1);

	// деструктор
	~Fraction();

	// геттеры для полей
	int getNumerator(); 
	int getDenominator();

	// сеттеры для полей
	void setNumerator(int numerator);
	void setDenominator(int denominator);

	// возвратить дробь как число с плавающей точкой
	float asFloat(); 

	// перевернуть дробь (5/6 ==> 6/5)
	void reverse();

	// сократить дробь
	void normalize();

	// сложить дробь с другой
	void add(Fraction& other);
	
	// вычесть другую дробь с этой
	void subtract(Fraction& other);

	// умножить дробь на определённый фактор
	void multiply(int factor);

	// умножить дробь на другую
	void multiply(Fraction& other);

	// поделить дробь на определённый фактор
	void divide(int factor);

	// поделить дробь на другую
	void divide(Fraction& other);

	// вывести дробь на экран консоли
	void print();
};

