#include <iostream>
#include <Windows.h>

class Fraction
{
private:
	int denominator;
	int divider;

public:
	Fraction(int denominator = 0, int divider = 0)
	{
		this->denominator = denominator;
		this->divider = divider;
	}

	~Fraction()
	{
		this->denominator = 0;
		this->divider = 0;
	}

	int getDenominator() { return denominator; }
	int getDivider() { return divider; }

	void setDenominator(int denominator) { this->denominator = denominator; }
	void setDivider(int divider) { this->divider = divider; }

	float asFloat() { return (float)denominator / (float)divider; }

	void add(Fraction& other)
	{
		denominator += other.getDenominator();
		divider += other.getDivider();
	}
	
	void subtract(Fraction& other)
	{
		denominator -= other.getDenominator();
		divider -= other.getDivider();
	}

	void multiply(Fraction& other)
	{
		denominator *= other.getDenominator();
		divider *= other.getDivider();
	}

	void divide(Fraction& other)
	{
		denominator /= other.getDenominator();
		divider /= other.getDivider();
	}

	void print()
	{
		std::cout << denominator << " / " << divider << '\n';
	}
};

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	Fraction a(75, 23);
	Fraction b(3, 5);
	Fraction tmp;

	std::cout << "Fraction a:\n\t";
	a.print();
	std::cout << "\tfloat representation: " << a.asFloat() << '\n';

	std::cout << "\nFraction b:\n\t";
	b.print();
	std::cout << "\tfloat representation: " << b.asFloat() << '\n';

	tmp = a;
	tmp.add(b);
	std::cout << "\n\na + b = ";
	tmp.print();

	tmp = a;
	tmp.subtract(b);
	std::cout << "\na - b = ";
	tmp.print();

	tmp = a;
	tmp.multiply(b);
	std::cout << "\na * b = ";
	tmp.print();

	tmp = a;
	tmp.divide(b);
	std::cout << "\na / b = ";
	tmp.print();

	_getwch();
	return 0;
}
