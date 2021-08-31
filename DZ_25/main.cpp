/*
	Домашнее Задание №25
		Ученик: Шелест Александр

	Навести примеры использования манипуляторов и флагов потока
	на программах из прошлых домашних работ.
*/

#include <iostream> 	// std::cout; std::cin
#include <iomanip> 		// std::setf; std::ios::...
#include <clocale> 		// setlocale()
#include <time.h> 		// time()

// ввод пользователем данных с проверкой на их корректность
template <class T>
void safeInput(T* value, const char* msg, bool(*predicate)(T) = nullptr)
{
	// пока корректные данные не будут получены
	while (true)
	{
		// запрос и ввод данных
		std::cout << msg;
		std::cin >> *value;

		bool success = std::cin.good();

		if (predicate != nullptr)
			success = success && predicate(*value);

		// очистка потока
		std::cin.clear();
		std::cin.ignore(16, '\n');

		// прекратить цикл если данные корректны
		if (success)
			break;

		std::cout << "Введено некорректное значение.\n";
	}
}

// проверка знака числа
template <class T>
bool isPositive(T value) { return value > 0; }

// ДЗ №6, 4
inline void dz_6_4()
{
	float cost = 0;

	std::cout << "======================================================\n";
	std::cout << "№6.4 - вывести стоимость конфет за 0.1, 0.2, ... 1 кг\n\n";

	safeInput(&cost, "Введите стоимость 1 кг конфет (в грн): ", isPositive);

	// задание фиксированной точности чисел
	std::cout << std::fixed;
	for (float i = 0.1f; i <= 1.001f; i+=0.1f)
	{
		// вывод веса конфет с точностью 1 символ после точки
		std::cout << std::setprecision(1) << "стоимость " << i << " кг конфет";
		// вывод стоимости конфет с точностью 2 символа после точки
		std::cout << std::setprecision(2) << " равна " << cost * i << " грн\n";
	}
}

// ДЗ №6, 6
inline void dz_6_6()
{
	srand(time(0));

	int dMin = 0;
	int dMax = 0;
	int sum = 0;

	std::cout << "\n===============================================================\n";
	std::cout << "№6.6 - вывести сумму пяти случайных чисел в заданном диапазоне\n\n";

	safeInput(&dMin, "Введите целое число - нижнюю границу диапазона: ", isPositive);
	safeInput(&dMax, "Введите целое число - верхнюю границу диапазона: ", isPositive);

	// если нижняя граница выше верхней...
	if (dMin > dMax)
	{
		// поменять значения переменных местами
		dMin ^= dMax;
		dMax ^= dMin;
		dMin ^= dMax;
	}

	// если граница равны...
	if (dMin == dMax)
		// увеличить верхнюю границу на 1
		dMax++;

	for (int i = 0; i < 5; i++)
	{
		// получение нового случайного числа
		int tmp = (rand() % (dMax - dMin)) + dMin;
		
		// вывод числовых значений с правой стороны окна,
		// установив его ширину в 15-16 символов и альтернативный символ заполнения
		// а также вывод знаков [+, =] с левой стороны
		std::cout << std::right << std::setw(16) << std::setfill('.') << sum << '\n';
		std::cout << std::left << '+';
		std::cout << std::right << std::setw(15) << std::setfill('.') << tmp << '\n';
		std::cout << std::left << '=';
		sum += tmp;
		std::cout << std::right << std::setw(15) << std::setfill('.') << sum << '\n';
		std::cout << std::right << std::setw(16) << std::setfill('_') << "";
		std::cout << "\n\n";
	}

	// вывод резульата на экран
	
	// показывать систему исчисления
	std::cout << std::showbase;
	std::cout << "Сумма случайных чисел в диапазоне ["
		<< dMin << " .. " << dMax << "]:\n";

	// десятичная система
	std::cout << "\t- " << std::dec << sum << " (десятичная система)\n"; 
	// восьмеричная система
	std::cout << "\t- " << std::oct << sum << " (восьмеричная система)\n"; 
	// шестнадцатеричная система
	std::cout << "\t- " << std::hex << sum << " (шестнадцатеричная система)\n\n"; 

	// восстановление манипулятора потока
	std::cout << std::noshowbase;
}

int main()
{
	// задание региона консоли
	setlocale(LC_ALL, "");

	// вывод начального текста
	std::cout << "\tДомашнее Задание №25\n"
		"\t\tУченик: Шелест Александр\n\n"
		"Навести примеры использования манипуляторов и флагов потока\n"
		"на программах из прошлых домашних работ.\n\n";

	// запуск примеров на выполнение
	dz_6_4();
	dz_6_6();

	// пауза и выход из программы
	std::cout << "\nНажмите Enter для выхода из программы...\n";
	std::cin.get();
	return 0;
}

