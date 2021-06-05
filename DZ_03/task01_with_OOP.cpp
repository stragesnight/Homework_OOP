/*
	-= �� �3, ������� �1 =-
		������: ������ ���������
	
	����������� ����� �����. ���������� ������� ��������� � ����������� � �������� ����������-������.
	����������� ������ ��� ����� ������ � ����������-����� � ��� ���������� �������������� ��������.
*/

#include <iostream>
#include <Windows.h>

// �����
class Fraction
{
// ��������� ���� ������, ����������� �����
private:
	int numerator;		// ���������
	int denominator;	// �����������

	// �������� ���������� ����� �������
	int getGreatestCommonDivisor()
	{
		// ������� ������� �� ���� �����
		int tmp = numerator > denominator ? numerator : denominator;

		// ����� ����������� ������ ��������
		for (int i = tmp; i > 0; i--)
			if (numerator % i == 0 && denominator % i == 0)
				return i;

		// ���������� ���� ���� ����� ������� �� ���� �������
		return 1;
	}

// ��������� ���� ������, ��������� ��� ������ �����
public:
	// �����������
	// ���� ���������� �� �������������, ����� ����� ����� 0/1
	Fraction(int numerator = 0, int denominator = 1)
	{
		// ������� ������� ��� ����� (� �������� ���� �������������� ��������)
		setNumerator(numerator);
		setDenominator(denominator);

		// ��������� �����
		normalize();
	}

	// ����������
	~Fraction()
	{
		// ��������� ����� �������� ����
		this->numerator = 0;
		this->denominator = 0;
	}

	// ������� ��� �����

	// �������� ��������� 
	int getNumerator() { return numerator; }
	// �������� �����������
	int getDenominator() { return denominator; }

	// ������� ��� �����

	// ��������� ���������
	void setNumerator(int numerator) 
	{ 
		this->numerator = numerator;
	}
	// ��������� �����������
	void setDenominator(int denominator) 
	{
		// �������� �� ���� (�� ���� ������ ���������) 
		if (denominator != 0)
			this->denominator = denominator;
		else
			std::cout << "\nERROR: denominator of a fraction number cannot be zero.\n";
	}

	// ���������� ����� ��� ����� � ��������� ������
	float asFloat() { return (float)numerator / (float)denominator; }

	// ����������� ����� (5/6 ==> 6/5)
	void reverse()
	{
		std::swap(numerator, denominator);
	}

	// ��������� �����
	void normalize()
	{
		// ����� ���������� ����� �������
		int gcd = getGreatestCommonDivisor();

		// �������� ���� �� ���������� ����� �������
		numerator /= gcd;
		denominator /= gcd;
	}

	// ������� ����� � ������
	void add(Fraction& other)
	{
		// ��������� �����, �������� ����������� ��������� ����� other
		Fraction tmp = other;
		
		// ���� ����������� �� �����...
		if (denominator != other.getDenominator())
		{
			// �������� ��� ����� �� ����������� ������ (��� ��������� ������������)
			tmp.multiply(this->getDenominator());
			this->multiply(other.getDenominator());
		}
		
		// ��������� ��������� ������ ����� � �������
		numerator += tmp.getNumerator();

		// ��������� �����
		normalize();
	}
	
	// ������� ������ ����� � ����
	void subtract(Fraction& other)
	{
		// ��������� �����, �������� ����������� ��������� ����� other
		Fraction tmp = other;
		
		// ���� ����������� �� �����...
		if (denominator != other.getDenominator())
		{
			// �������� ��� ����� �� ����������� ������ (��� ��������� ������������)
			tmp.multiply(this->getDenominator());
			this->multiply(other.getDenominator());
		}
	
		// ������� ��������� ������ ����� � ����
		numerator -= tmp.getNumerator();
		
		// ��������� �����
		normalize();
	}

	// �������� ����� �� ����������� ������
	void multiply(int factor)
	{
		// �������� ��� ���� �� ������
		numerator *= factor;
		denominator *= factor;
	}

	// �������� ����� �� ������
	void multiply(Fraction& other)
	{
		// �������� ��� ����
		numerator *= other.getNumerator();
		denominator *= other.getDenominator();

		// ��������� �����
		normalize();
	}

	// �������� ����� �� ����������� ������
	void divide(int factor)
	{
		// �������� ��� ���� �� ������
		numerator /= factor;
		denominator /= factor;

		// ��������� ����������� ����, ���� �� ����� ����
		if (denominator == 0)
			denominator++;
	}

	// �������� ����� �� ������
	void divide(Fraction& other)
	{
		// ��������� �����, �������� ����������� ��������� ����� other
		Fraction tmp = other;

		// ����������� ������ �����
		tmp.reverse();
		// �������� ��� ����� �� �����������
		multiply(tmp);
	}

	void print()
	{
		std::cout << numerator << "/" << denominator;
	}
};

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	Fraction a;
	Fraction b;

	std::cout << "\t-= �� �3, ������� �1 =-\n";
	std::cout << "����������� ����� �����. ���������� ������� ��������� � ����������� � �������� ����������-������.\n";
	std::cout << "����������� ������ ��� ����� ������ � ����������-����� � ��� ���������� �������������� ��������.\n\n";

	int input;
	std::cout << "������� ������ ������� ����� (������: ���� \"5 6\" ������������� ����� 5/6): ";
	std::cin >> input;
	a.setNumerator(input);
	std::cin >> input;
	a.setDenominator(input);

	std::cout << "������� ������ ������� �����: ";
	std::cin >> input;
	b.setNumerator(input);
	std::cin >> input;
	b.setDenominator(input);

	std::cout << "\n����� �: ";
	a.print();
	std::cout << " (" << a.asFloat() << ")";

	std::cout << "\n����� �: ";
	b.print();
	std::cout << " (" << b.asFloat() << ")";

	std::cout << "\n\n�������� �������� - ����� ����������� �������������.\n";

	Fraction tmp = a;
	tmp.add(b);
	std::cout << "\n\n� + � = ";
	tmp.print();
	std::cout << " (" << tmp.asFloat() << ")";

	tmp = a;
	tmp.subtract(b);
	std::cout << "\n� - � = ";
	tmp.print();
	std::cout << " (" << tmp.asFloat() << ")";

	tmp = a;
	tmp.multiply(b);
	std::cout << "\n� * � = ";
	tmp.print();
	std::cout << " (" << tmp.asFloat() << ")";

	tmp = a;
	tmp.divide(b);
	std::cout << "\n� / � = ";
	tmp.print();
	std::cout << " (" << tmp.asFloat() << ")\n\n";

	_getwch();
	return 0;
}
