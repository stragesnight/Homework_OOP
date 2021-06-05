/*
	-= �� �3, ������� �1 =-
		������: ������ ���������
	
	����������� ����� �����. ���������� ������� ��������� � ����������� � �������� ����������-������.
	����������� ������ ��� ����� ������ � ����������-����� � ��� ���������� �������������� ��������.
    ���� ���� �������� ������ � ������� ��� ������������� �������.
*/

#include <iostream>
#include <Windows.h>

// �����
struct Fraction
{
    int numerator;
    int denominator;
};

// �������� ���������� ����� �������
int getGreatestCommonDivisor(const Fraction& fract)
{
    // ������� ������� �� ���� �����
    int tmp = fract.numerator > fract.denominator ? fract.numerator : fract.denominator;

    // ����� ����������� ������ ��������
    for (int i = tmp; i > 0; i--)
        if (fract.numerator % i == 0 && fract.denominator % i == 0)
            return i;

    // ���������� ���� ���� ����� ������� �� ���� �������
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

// ��������� �����
void normalize(Fraction& fract)
{
    // ����� ���������� ����� �������
    int gcd = getGreatestCommonDivisor(fract);

    // �������� ���� �� ���������� ����� �������
    fract.numerator /= gcd;
    fract.denominator /= gcd;
}

// �������� ����� �� ����������� ������
void multiply(Fraction& fract, int factor)
{
    // �������� ��� ���� �� ������
    fract.numerator *= factor;
    fract.denominator *= factor;
}

// �������� ����� �� ������
void multiply(Fraction& that, Fraction& other)
{
    // �������� ��� ����
    that.numerator *= other.numerator;
    that.denominator *= other.denominator;

    // ��������� �����
    normalize(that);
}

// ������� ����� � ������
void add(Fraction& that, Fraction& other)
{
    // ��������� �����, �������� ����������� ��������� ����� other
    Fraction tmp = other;
    
    // ���� ����������� �� �����...
    if (that.denominator != other.denominator)
    {
        // �������� ��� ����� �� ����������� ������ (��� ��������� ������������)
        multiply(tmp, that.denominator);
        multiply(that, other.denominator);
    }
    
    // ��������� ��������� ������ ����� � �������
    that.numerator += tmp.numerator;

    // ��������� �����
    normalize(that);
}


// ������� ������ ����� � ����
void subtract(Fraction& that, Fraction& other)
{
    // ��������� �����, �������� ����������� ��������� ����� other
    Fraction tmp = other;
    
    // ���� ����������� �� �����...
    if (that.denominator != other.denominator)
    {
        // �������� ��� ����� �� ����������� ������ (��� ��������� ������������)
        multiply(tmp, that.denominator);
        multiply(that, other.denominator);
    }
 
    // ������� ��������� ������ ����� � ����
    that.numerator -= tmp.numerator;
    
    // ��������� �����
    normalize(that);
}
// �������� ����� �� ����������� ������
void divide(Fraction& fract, int factor)
{
    // �������� ��� ���� �� ������
    fract.numerator /= factor;
    fract.denominator /= factor;

    // ��������� ����������� ����, ���� �� ����� ����
    if (fract.denominator == 0)
        fract.denominator++;
}

// �������� ����� �� ������
void divide(Fraction& fract, Fraction& other)
{
    // ��������� �����, �������� ����������� ��������� ����� other
    Fraction tmp = other;

    // ����������� ������ �����
    reverse(tmp);
    // �������� ��� ����� �� �����������
    multiply(fract, tmp);
}

// ������� ����� �� ����� �������
void print(const Fraction& fract)
{
    std::cout << fract.numerator << "/" << fract.denominator;
}

int main()
{
	// �������� ��������� ���������
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	// �������� ��� ������� ������ Fraction
	Fraction a;
	Fraction b;

	// ������� ��������� ����� �� �����
	std::cout << "\t-= �� �3, ������� �1 =-\n";
	std::cout << "����������� ����� �����. ���������� ������� ��������� � ����������� � �������� ����������-������.\n";
	std::cout << "����������� ������ ��� ����� ������ � ����������-����� � ��� ���������� �������������� ��������.\n\n";

	// ���� ������ � ���������� � ���������� ����� �����
	int input;
	std::cout << "������� ������ ������� ����� (������: ���� \"5 6\" ������������� ����� 5/6): ";
	std::cin >> input;
    a.numerator = input;
	std::cin >> input;
	a.denominator = input;

	std::cout << "������� ������ ������� �����: ";
	std::cin >> input;
	b.numerator = input;
	std::cin >> input;
	b.denominator = input;

	std::cout << "\n����� �: ";
	print(a);
	std::cout << " (" << asFloat(a) << ")";

	std::cout << "\n����� �: ";
	print(b);
	std::cout << " (" << asFloat(b) << ")";

	std::cout << "\n\n�������� �������� - ����� ����������� �������������.\n";

	// ��������
	Fraction tmp = a;
	add(tmp, b);
	std::cout << "\n\n� + � = ";
	print(tmp);
	std::cout << " (" << asFloat(tmp) << ")";

	// ���������
	tmp = a;
	subtract(tmp, b);
	std::cout << "\n� - � = ";
	print(tmp);
	std::cout << " (" << asFloat(tmp) << ")";

	// ���������
	tmp = a;
	multiply(tmp, b);
	std::cout << "\n� * � = ";
	print(tmp);
	std::cout << " (" << asFloat(tmp) << ")";

	// �������
	tmp = a;
	divide(tmp, b);
	std::cout << "\n� / � = ";
	print(tmp);
	std::cout << " (" << asFloat(tmp) << ")";

	// ���������� ���������
	_getwch();
	return 0;
}
