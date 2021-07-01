/*
	 -= Домашнее Задание №13 =-
		Ученик - Шелест Александр

	Создать класс Date. В классе должен быть метод,
	увеличивающий день на один.
	Реализовать соответствующие конструкторы и методы.
*/

#include <iostream> 	// std::cout; std::cin
#include <ctime>			// time()
#include <stdio.h> 		// getchar()
#include <clocale>		// setlocale()

// код, зависимый от платформы, вынесен в макросы.
#if defined (_WIN32) or defined (_WIN64)
# define clrscr() system("cls")
#elif defined (__linux__)
# define clrscr() system("clear")
#endif

// перечисление месяцев для улучшенной визуальной отдачи кода
enum Month { 	January = 1, February, March, April,
							May, June, July, August,
							September, October, November, December };

// количетсво дней в каждом месяце
unsigned daysInMonths[] { 0, 31, 28, 31, 30,
													31, 30, 31, 31,
													30, 31, 30, 31	};

// Дата
class Date
{
private:
	unsigned day; 		// день
	unsigned month; 	// месяц
	unsigned year; 		// год
	bool isLeapYear; 	// високосный лы год

	// проверить високосность текущего года
	void updateLeap()
	{
		// проверить на високосность
		// - записть равноценна year % 4 == 0
		isLeapYear = ((year & 0b100) == 0b100);
		// обновить количество дней в феврале
		daysInMonths[February] = isLeapYear ? 29 : 28;
	}

	// проверить дату на корректность
	void validate()
	{
		if (day > daysInMonths[month])
		{
			day %= daysInMonths[month];
			month++;
		}

		if (month > 12)
		{
			month %= 12;
			year++;
		}

		updateLeap();
	}

public:
	// конструктор по умолчанию
	// присваивает дате текущий день в реальном мире.
	Date()
	{
		// получить количество дней, прошедшее с 1 января 1970
		unsigned days = time(0) / 86400;
		// добавить количество дней, прошедших в этой эре до 1 января 1970
		// результатом будет общее количество дней, прошедшее в этой эре
		days += 719544;

		// вычислить текущий год с учётом високосности
		year = (float)days / 365.25;

		// проверить високосность
		updateLeap();
		// вычислить количество дней, пройденное в этом году
		unsigned daysIntoYear = days - (year * 365.25);

		// вычислить текущий месяц и день
		month = 1;
		day = daysIntoYear + 1;
		while (true)
		{
			if (daysInMonths[month] > day)
				break;

			day -= daysInMonths[month];
			month++;
		}
	}

	// конструктор с параметрами
	// присваивает дате значения, соответствующие параметрам
	// и проверяет на корректность
	Date(unsigned day, unsigned month, unsigned year)
	{
		this->year = year;
		this->month = month % 12;
		this->day = day;

		updateLeap();

		validate();
	}

	// геттеры для полей
	
	unsigned getDay() { return day; }
	unsigned getMonth() { return month; }
	unsigned getYear() { return year; }
	bool getIsLeapYear() { return isLeapYear; }

	// сеттеры для полей с проверкой корректности
	
	void setDay(unsigned day)
	{
		this->day = day;
		validate();
	}
	void setMonth(unsigned month)
	{
		this->month = month;
		validate();
	}
	void setYear(unsigned year)
	{
		this->year = year;
		validate();
	}

	// дружественные функции

	// вывести дату на экран
	friend std::ostream& operator<<(std::ostream&, const Date&);
	// ввест идату с клавиатуры
	friend std::istream& operator>>(std::istream&, Date&);
	// увеличить день в дате на один
	friend void incrementDay(Date&);
};

// вывести дату на экран
std::ostream& operator<<(std::ostream& ostr, const Date& date)
{
	if (date.day < 10)
		ostr << '0';
	ostr << date.day << '.';

	if (date.month < 10)
		ostr << '0';
	ostr << date.month << '.';

	ostr << date.year;

	return ostr;
}

// ввести дату с клавиатуры
std::istream& operator>>(std::istream& istr, Date& date)
{
	std::cout << "Вам будет предложено ввести дату в формате { день.месяц.год }.\n";
	std::cout << "\tЧто бы использовать реальную текущую дату, "
						<< "введите '0' в любое поле.\n\n";

# define checkZero(v) if ((v) == 0) { date = Date(); \
							std::cout << "\nВыбрано использование текущей даты.\n\n";\
							return istr; }
	
	std::cout << "Введите день - ";
	std::cin >> date.day;
	checkZero(date.day);
	std::cout << "Введите месяц - ";
	std::cin >> date.month;
	checkZero(date.month);
	std::cout << "Введите год - ";
	std::cin >> date.year;
	checkZero(date.year);
	
	date.validate();

	std::cout << "Введённая вами дата - " << date << '\n';

	return istr;
}

// увеличить день в дате на один
void incrementDay(Date& date)
{
	date.day++;
	date.validate();
}

int main()
{
	// добавить поддержку кириллицы
	setlocale(LC_ALL, "");

	std::cout << "\t-= Домашнее Задание №13 =-\n"
			<< "\t\tУченик - Шелест Александр\n\n"
			<< "Создать класс Date. В классе должен быть метод,\n"
			<< "увеличивающий день на один.\n"
			<< "Реализовать соответствующие конструкторы и методы.\n\n\n";

	// объявить дату и ввести данные с клавиатуры
	Date date;
	std::cin >> date;

	std::cout << "Нажимайте Enter для перехода на следующий день в дате.\n";
	std::cout << "Для выхода из программы, в любой момент введите '0'.\n";
	getchar();

	// основной цикл выполнения
	
	char input;
	// продолжать инкремент даты, пока пользователь не введёт 0
	while ((input = getchar()) != '0')
	{
		clrscr();
		std::cout << "Нажимайте Enter для перехода на следующий день в дате.\n";
		std::cout << "Для выхода из программы, в любой момент введите '0'.\n\n";

		incrementDay(date);
		std::cout << "Новая дата - " << date << '\n';
	}

	// завершить выполнение программы
	return 0;
}

