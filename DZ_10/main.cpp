/*
	Домашнее Задание №10
		Ученик - Шелест Александр
	
	Создать класс для комплексного числа. Создать перегруженные
	операторы для реализации арифметических операций (+, -, *, /).
*/

#include <iostream> 	// std::cout, std::cin
#include <clocale> 		// setlocale()
#include <cmath> 		// fabs()
#include <iomanip> 		// std::setprecision()

// Комплексное число
class Complex
{
private:
	/* 	комплексное число имеет форму a + bi, 
		i фактически можно упустить до момента вывода на экран
		поэтому для выражения комплексного числа достаточно a и b. */
	float a;
	float b;
	bool sign; 		// для "декорации" вывода на экран

public:
	// конструктор, по умолчанию комплексное число будет иметь вид 1 + 1i
	Complex(float a = 1, float b = 1) : a(a), b(b)
	{
		// проверка на знак второго числа
		sign = b < 0;
	}

	// геттеры для полей

	float getA() { return a; }
	float getB() { return b; }
	char getSign() { return sign ? '-' : '+'; }

	// сеттеры для полей

	void setA(float a) { this->a = a; }
	void setB(float b) { this->b = b; }

	// операторы

	Complex operator+(const Complex& other);
	Complex operator-(const Complex& other);
	Complex operator*(const Complex& other);
	Complex operator/(const Complex& other);
};

// реализации операторов

/* 	
	источник формул - https://ru.wikipedia.org/wiki/Комплексное_число
	формулы легко интерпретируются как операция над двумя объектами.
		a == this->a;
		b == this->b;
		c == other.a;
		d == other.b;
*/

Complex Complex::operator+(const Complex& other)
{
	// (a + bi) + (c + di) = (a + c) + (b + d)i;
	float a = this->a + other.a;	// a + c
	float b = this->b + other.b;	// b + d
	return Complex(a, b);
}

Complex Complex::operator-(const Complex& other)
{
	// (a + bi) - (c + di) = (a - c) + (b - d)i;
	float a = this->a - other.a;	// a - c
	float b = this->b - other.b;	// b - d
	return Complex(a, b);
}

Complex Complex::operator*(const Complex& other)
{
	// (a + bi) * (c + di) = (ac - bd) + (bc - ad)i;
	float a = (this->a * other.a) - (this->b * other.b);			// ac - bd
	float b = (this->b * other.a) + (this->a * other.b);			// bc - ad
	return Complex(a, b);
}

Complex Complex::operator/(const Complex& other)
{
	// (a + bi) / (c + di) = ((ac + bd) / c^2 + d^2)) + ((bc - ad) / (c^2 + d^2))i
	float tmp = ((other.a * other.a) + (other.b * other.b));		// c^2 + d^2
	float a = ((this->a * other.a) + (this->b * other.b)) / tmp;	// (ac + bd) / c^2 + d^2)
	float b = ((this->b * other.a) - (this->a * other.b)) / tmp;	// (bc - ad) / (c^2 + d^2)
	return Complex(a, b);
}

// оператор для вывода в поток, 
// это позволит выводить объект на экран напрямую через std::cout << ...
std::ostream& operator<<(std::ostream& ostr, Complex c)
{
	ostr << std::setprecision(3) << c.getA() << ' ' << c.getSign() << ' ' << fabs(c.getB()) << 'i';
	return ostr;
}

// оператор для ввода в поток,
// это позволит вводить данные в объект напрямую через std::cin >> ...
std::istream& operator>>(std::istream& istr, Complex& c)
{
	float tmp;

	istr >> tmp;
	c.setA(tmp);
	istr >> tmp;
	c.setB(tmp);

	return istr;
}

int main()
{
	// добавление поддержки кириллицы
	setlocale(LC_ALL, "");

	// вывод начального текста на экран
	std::cout << "\tДомашнее Задание №10\n"
			<< "\t\tУченик - Шелест Александр\n\n"
			<< "Создать класс для комплексного числа. Создать перегруженные\n"
			<< "операторы для реализации арифметических операций (+, -, *, /).\n\n";

	// объявление двух объектов комплексных чисел
	Complex first;
	Complex second;

	// ввод данных с клавиатуры
	std::cout << "Вам будет предложено ввести два комплексных числа,\n"
		<< "которые будут выступать операндами для арифметических операций.\n\n";

	std::cout << "Если вы желаете просмотреть результаты контрольных примеров,\n"
		"введите \"0 0\" как один из операндов.\n\n";

	std::cout << "Комплексное число имеет форму \"a + bi\"\n\n";

	std::cout << "Введите 'a' и 'b' для первого операнда: ";
	std::cin >> first;
	std::cout << "Введите 'a' и 'b' для второго операнда: ";
	std::cin >> second;
	std::cout << '\n';

	// проверка на контрольные примеры
	bool isTestSequence = int(first.getA() + first.getB()) == 0 || int(second.getA() + second.getB() == 0);

// макросы для упрощения жизни

// изменение объектов на контрольные при потребности
#define testseq(a, b, c, d) if (isTestSequence) { first = Complex(a, b); second = Complex(c, d); }

// вывод результата операции над объектами на экран
#define printsequ(op) std::cout << '(' << first << ") " << #op << " (" << second << ") = "; \
					std::cout << first op second << '\n'

	// выполнение операций над объектами

	if (isTestSequence)
		std::cout << "Вами было выбрано отображение контрольных примеров.\n\n";

	testseq(-3, 5, 4, -8);
	printsequ(+);

	testseq(-5, 2, 6, -5);
	printsequ(-);
	
	testseq(1, -2, 3, 2);
	printsequ(*);

	testseq(7, -4, 3, 2);
	printsequ(/);

	std::cin.ignore(1, '\0');
	std::cin.get();
	return 0;
}

