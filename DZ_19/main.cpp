/*
	Домашнее Задание №19
		Ученик: Шелест Александр

	Создать иерархию классов используя механизм шаблонного наследования.
	В каждом классе реализовать соответствующие методы для работы с ним.
*/

#include <iostream> 	// std::cout;

// Базовый класс
template <class T1, class T2>
class Base
{
protected:
	// поля, которые будут доступны дочерним классам

	T1 value1;
	T2 value2;

public:
	// конструктор
	Base(T1 value1 = T1(0), T2 value2 = T2(0))
	{
		this->value1 = value1;
		this->value2 = value2;
	}

	// деструктор
	~Base()
	{
		value1 = T1(0);
		value2 = T2(0);
	}

	// геттеры для полей

	T1 getValue1() { return value1; }
	T2 getValue2() { return value2; }

	// сеттеры для полей
	
	void setValue1(T1 value1) { this->value1 = value1; }
	void setValue2(T2 value2) { this->value2 = value2; }

	// вывести информацию на экран
	virtual void display()
	{
		std::cout << "value1 = " << value1 << '\n';
		std::cout << "value2 = " << value2 << '\n';
	}
};


// Дочерний класс №1
template <class T1, class T2, class T3, class T4>
class Child1 : public Base<T1, T2>
{
private:
	T3 value3;
	T4 value4;

public:
	// конструктор, дополняющий конструктор базового класса
	Child1(T1 value1 = T1(0), T2 value2 = T2(0), T3 value3 = T3(0), T4 value4 = T4(0))
		: Base<T1, T2>(value1, value2)
	{
		this->value3 = value3;
		this->value4 = value4;
	}

	// деструктор
	~Child1()
	{
		this->value3 = T3(0);
		this->value4 = T4(0);
	}

	// геттеры для полей

	T1 getValue3() { return value3; }
	T2 getValue4() { return value4; }

	// сеттеры для полей
	
	void setValue3(T1 value3) { this->value3 = value3; }
	void setValue4(T2 value4) { this->value4 = value4; }

	// перегрузка метода базового класса
	void display() override
	{
		Base<T1, T2>::display();
		std::cout << "value3 = " << value3 << '\n';
		std::cout << "value4 = " << value4 << '\n';
	}
};


// Дочерний класс №2
template <class T1, class T2, class T5, class T6>
class Child2 : public Base<T1, T2>
{
private:
	T5 value5;
	T6 value6;
	
public:
	// конструктор, дополняющий конструктор базового класса
	Child2(T1 value1 = T1(0), T2 value2 = T2(0), T5 value5 = T5(0), T6 value6 = T6(0))
		: Base<T1, T2>(value1, value2)
	{
		this->value5 = value5;
		this->value6 = value6;
	}

	// деструктор
	~Child2()
	{
		this->value5 = T5(0);
		this->value6 = T6(0);
	}

	// геттеры для полей

	T1 getValue5() { return value5; }
	T2 getValue6() { return value6; }

	// сеттеры для полей

	void setValue5(T1 value6) { this->value5 = value5; }
	void setValue6(T2 value6) { this->value6 = value6; }

	// перегрузка метода базового класса
	void display() override
	{
		Base<T1, T2>::display();
		std::cout << "value5 = " << value5 << '\n';
		std::cout << "value6 = " << value6 << '\n';
	}
};


int main()
{
	// добавление поддержки кириллицы
	setlocale(LC_ALL, "rus");

	std::cout << "\tДомашнее Задание №19\n"
			<< "\t\tУченик: Шелест Александр\n\n"
			<< "Создать иерархию классов используя механизм шаблонного наследования.\n"
			<< "В каждом классе реализовать соответствующие методы для работы с ним.\n\n";

	// начало тестирования работы классов
	// дальнейшие действия выводятся на экран
			
	std::cout << "\nCоздаем объект класса Child1...\n";
	Child1<int, float, char, bool> child1(16, 3.1459, 'A', false);

	std::cout << "\nИнформация о Child1:\n";
	child1.display();
	std::cout << "\nМеняем значение третьего поля...\n";
	child1.setValue3('B');
	std::cout << "\nИнформация о Child1:\n";
	child1.display();

	std::cout << "\nСоздаем указатель на Base,\n"
			<< "значением будет адресс предыдущего объекта...\n";
	Base<int, float>* base_from_child1 = &child1;
	std::cout << "\nИнформация о Base:\n";
	base_from_child1->display();
	std::cout << "\nРезультат работы метода одинаков с Child1,\n"
			<< "\tтак так этот метод является виртуальным.\n";

	std::cout << "\nСоздаем объект класса Child2...\n";
	Child2<char, char, char, char> child2('C', '+', '+', '!');
	std::cout << "\nИнформация о Child2:\n";
	child2.display();

	// пауза и завершение работы программы
	std::cout << "\n\nтест завершён, нажмите Enter для завершения работы программы...\n";
	std::cin.get();
	return 0;
}

