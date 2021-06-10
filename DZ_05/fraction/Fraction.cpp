// файл, содержащий реализации методов класса Дробь

#include "Fraction.h"

int Fraction::getGreatestCommonDivisor()
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

Fraction::Fraction(int numerator, int denominator)
{
    // вызвать сеттеры для полей (в сеттерах есть дополнительные проверки)
    setNumerator(numerator);
    setDenominator(denominator);

    // сократить дробь
    normalize();
}

Fraction::~Fraction()
{
    // присвоить полям значения ноля
    this->numerator = 0;
    this->denominator = 0;
}

int Fraction::getNumerator() { return numerator; }
int Fraction::getDenominator() { return denominator; }

void Fraction::setNumerator(int numerator)
{ 
    this->numerator = numerator;
}
void Fraction::setDenominator(int denominator)
{
    // проверка на ноль (на ноль делить невоможно) 
    if (denominator != 0)
        this->denominator = denominator;
    else
        std::cout << "\nERROR: denominator of a fraction number cannot be zero.\n";
}

float Fraction::asFloat() { return (float)numerator / (float)denominator; }

void Fraction::reverse()
{
    std::swap(numerator, denominator);
}

void Fraction::normalize()
{
    // найти наибольшее общее кратное
    int gcd = getGreatestCommonDivisor();

    // поделить поля на наибольшее общее кратное
    numerator /= gcd;
    denominator /= gcd;
}

void Fraction::add(Fraction &other)
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

void Fraction::subtract(Fraction& other)
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

void Fraction::multiply(int factor)
{
    // умножить оба поля на фактор
    numerator *= factor;
    denominator *= factor;
}

void Fraction::multiply(Fraction& other)
{
    // умножить оба поля
    numerator *= other.getNumerator();
    denominator *= other.getDenominator();

    // сократить дробь
    normalize();
}

void Fraction::divide(int factor)
{
    // поделить оба поля на фактор
    numerator /= factor;
    denominator /= factor;

    // присвоить знаменателю один, если он равен нулю
    if (denominator == 0)
        denominator++;
}

void Fraction::divide(Fraction& other)
{
    // временная дробь, хранящяя изначальное состояние дроби other
    Fraction tmp = other;

    // перевернуть другую дробь
    tmp.reverse();
    // кмножить эту дробь на перевёрнутую
    multiply(tmp);
}

void Fraction::print()
{
    std::cout << numerator << "/" << denominator;
}
