/*
	.=: Домашнее Задание №9 :=.
		Ученик: Шелест Александр
	
	Создать класс Дробь. При помощи перегрузки операторов
	реализовать для него арифметические операции (+, -, *, /).
*/

#include <iostream> 	// std::cout, std::cin
#include <clocale> 		// setlocale

// Дробь
class Fraction
{
private:
	int numerator; 		// числитель
	int denominator; 	// знаменатель

	// сократить дробь
	void normalize()
	{
		// найти наибольшее общее краное
		int gcd = getGreatestCommonDivisor();

		// поделить поля на нибольшее общее кратное
		numerator /= gcd;
		denominator /= gcd;
	}

	// получить наибольшее общее кратное у дроби
	int getGreatestCommonDivisor()
	{
		// найти большее из двух полей
		int tmp = numerator > denominator ? numerator : denominator;

		// поиск наибольшего общего кратного
		for (int i = tmp; i > 0; i--)
			if (numerator % i == 0 && denominator % i == 0)
				return i;

		return 1;
	}

public:
	// конструктор
	Fraction(int numerator = 0, int denominator = 1)
	{
		// присвоить полям значения через метаторы
		setNumerator(numerator);
		setDenominator(denominator);

		// сократить дробь
		normalize();
	}

	// геттеры для полей

	int getNumerator() { return numerator; }
	int getDenominator() { return denominator; }

	// сеттеры для полей

	void setNumerator(int numerator) { this->numerator = numerator; }
	void setDenominator(int denominator)
	{
		this->denominator = denominator + (1 * denominator == 0);
	}

	// перевернуть дробь
	void reverse() { std::swap(numerator, denominator); }

	// операторы
	
	explicit operator float() { return (float)numerator / (float)denominator; }
	Fraction operator+(Fraction other);
	Fraction operator-(Fraction other);
	Fraction operator*(int factor);
	Fraction operator*(Fraction other);
	Fraction operator/(int factor);
	Fraction operator/(Fraction other);
};

////////////////////////////////
// 	реализации методов класса
////////////////////////////////

// оператор вывода в поток
// позволяет использовать std::cout к объектам дроби напрямую
std::ostream& operator<<(std::ostream& ostr, Fraction f)
{
	ostr << f.getNumerator() << '/' << f.getDenominator();
	return ostr;
}

Fraction Fraction::operator+(Fraction other)
{
	// объявить новый объект, хранящий результат операции
	Fraction result(*this);

	// свести операнды к общему знасенателю при протребности
	if (result.denominator != other.denominator)
	{
		result = result * other.denominator;
		other = other * this->denominator;
	}

	// прибавить числитель
	result.numerator += other.numerator;

	// сократить дробь
	result.normalize();
	return result;
}

Fraction Fraction::operator-(Fraction other)
{
	// объявить новый объект, хранящий результат операции
	Fraction result(*this);

	// свести операнды к общему знасенателю при протребности
	if (result.denominator != other.denominator)
	{
		result = result * other.denominator;
		other = other * this->denominator;
	}

	// вычесть числитель
	result.numerator -= other.numerator;

	// сократить дробь
	result.normalize();
	return result;
}

Fraction Fraction::operator*(int factor)
{
	// создать новый объект, 
	// присвоить его полям результат операции над операндами
	
	Fraction result;
	result.numerator = this->numerator * factor;
	result.denominator = this->denominator * factor;
	
	return result;
}

Fraction Fraction::operator*(Fraction other)
{
	// создать новый объект, 
	// присвоить его полям результат операции над операндами

	Fraction result(*this);
	result.numerator *= other.numerator;
	result.denominator *= other.denominator;

	// сократить дробь
	result.normalize();
	return result;
}

Fraction Fraction::operator/(int factor)
{
	return Fraction(this->numerator / factor, this->denominator / factor);
}

Fraction Fraction::operator/(Fraction other)
{
	// создать новый объект, 
	// присвоить его полям результат операции над операндами
	
	Fraction result(*this);
	other.reverse();
	result = result * other;

	return result;
}



int main()
{
	// добавить поддержку кириллицы
	setlocale(LC_ALL, "rus");

	// вывести начальный текст на экран
	std::cout << "\t.=: Домашнее Задание №9 :=.\n"
			<< "\t\tУченик: Шелест Александр\n\n"
			<< "Создать класс Дробь. При помощи перегрузки операторов\n"
			<< "реализовать для него арифметические операции (+, -, *, /).\n\n";

	// создать три объекта класса Дробь
	Fraction a, b, result;

	// ввод пользоватеем данных
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

	std::cout << "\nДробь А: " << a << " (" << (float)a << ")";
	std::cout << "\nДробь Б: " << b << " (" << (float)b << ")";

	std::cout << "\n\nОбратите внимание - дроби сокращаются автоматически.\n\n";

	// выполнение операций над объектами
	
	result = a + b;
	std::cout << "А + Б = " << result << " (" << float(result) << ")\n";
	result = a - b;
	std::cout << "А - Б = " << result << " (" << float(result) << ")\n";
	result = a * b;
	std::cout << "А * Б = " << result << " (" << float(result) << ")\n";
	result = a / b;
	std::cout << "А / Б = " << result << " (" << float(result) << ")\n";

	// пауза и завершение программы
	std::cin.ignore(1, '\0');
	std::cin.get();
	return 0;
}
