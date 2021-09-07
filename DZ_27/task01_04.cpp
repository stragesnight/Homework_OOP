/*
 * 	-= Домашнее Задание №27, 1-4 =-
 * 		Ученик: Шелест Александр
 * 	
 * 	Написать функции для следующих манипуляций:
 * 		1. добавление столбца двухмерному массиву.
 * 		2. удаление столбца из двухмерного массива.
 * 		3. циклический сдвиг матрицы.
 * 		4. транспонирование матрицы.
 */

#include <iostream> 	// std::cin; std::cout
#include <clocale>  	// setlocale()
#include <ctime> 		// time()

#if defined(_WIN32) or defined(_WIN64)
# define clrscr() system("cls")
#else
# define clrscr() system("clear")
#endif

// структура для двухмерного массива и его размера
struct matrix
{
	int** data = nullptr; 	// данные массива
	unsigned width; 		// количество столбцов
	unsigned height; 		// количество линий

	matrix()
	{
		width = 0;
		height = 0;
		data = nullptr;
	}

	matrix(unsigned width, unsigned height)
	{
		this->width = width;
		this->height = height;

		data = new int*[width]{};
		for (unsigned i = 0; i < width; i++)
			data[i] = new int[height]{};
	}
};

// ввод с проверкой на корректность данных
template <class T>
void safeInput(T* v, const char* msg)
{
	while (true)
	{
		std::cout << msg;
		std::cin >> *v;

		bool good = std::cin.good();

		std::cin.clear();
		std::cin.ignore(16, '\n');

		if (good)
			return;

		std::cout << "Введено некорректное значение.\n";
	}
}

// заполнение массива случайными значениями [0 .. 9]
void fill(int* arr, unsigned n)
{
	for (unsigned i = 0; i < n; i++)
		arr[i] = rand() % 10;
}

// заполнение матрицы случайными знакчениями [0 .. 9]
void fill(matrix* const mat)
{
	for (unsigned w = 0; w < mat->width; w++)
		fill(mat->data[w], mat->height);
}

// вывод матрицы на экран
void display(const matrix* const mat)
{
	for (unsigned h = 0; h < mat->height; h++)
	{
		std::cout << '\t';
		for (unsigned w = 0; w < mat->width; w++)
			std::cout << mat->data[w][h] << ' ';
		std::cout << '\n';
	}
}

// добавление нового столбца в матрицу
void addCollumn(matrix*& mat, unsigned pos, int* data)
{
	pos = (pos <= 0) ? 1 : pos;
	pos = (pos > mat->width) ? mat->width : pos;
	pos--;
	matrix* res = new matrix(mat->width + 1, mat->height);

	for (unsigned w = 0; w < pos; w++)
		res->data[w] = mat->data[w];

	res->data[pos] = new int[mat->height] {};
	for (unsigned h = 0; h < mat->height; h++)
		res->data[pos][h] = data[h];

	for (unsigned w = pos + 1; w < res->width; w++)
		res->data[w] = mat->data[w - 1];

	delete mat;
	mat = res;
}

// удаление столбца из матрицы
void removeCollumn(matrix*& mat, unsigned pos)
{
	pos = (pos <= 0) ? 1 : pos;
	pos = (pos > mat->width) ? mat->width : pos;
	matrix* res = new matrix(mat->width - 1, mat->height);

	for (unsigned w = 0; w < pos; w++)
		res->data[w] = mat->data[w];

	for (unsigned w = pos; w < mat->width; w++)
		res->data[w - 1] = mat->data[w];

	delete mat;
	mat = res;
}

// сдвиг матрицы в заданном направлении
void shiftMatrix(matrix*& mat, int delta_w, int delta_h)
{
	matrix* res = new matrix(mat->width, mat->height);

	for (unsigned w = 0; w < res->width; w++)
	{
		// новая горизонтальная позиция элемента
		int nw = (delta_w >= 0) 
			? w + delta_w
			: res->width + delta_w + w;
		nw %= res->width;

		for (unsigned h = 0; h < res->height; h++)
		{
			// новая вертикальная позиция элемента
			int nh = (delta_h >= 0) 
				? h + delta_h
				: res->height + delta_h + h;
			nh %= res->height;

			res->data[nw][nh] = mat->data[w][h];
		}
	}

	delete mat;
	mat = res;
}

// транспозиция матрицы
void transposeMatrix(matrix*& mat)
{
	matrix* res = new matrix(mat->height, mat->width);

	for (unsigned w = 0; w < mat->width; w++)
	{
		for (unsigned h = 0; h < mat->height; h++)
			res->data[mat->height - h - 1][w] = mat->data[w][h];
	}

	for (unsigned w = 0; w < mat->width; w++)
		delete[] mat->data[w];
	delete mat;
	mat = res;
}

int main()
{
	srand(time(0));
	setlocale(LC_ALL, "rus");

	std::cout << "\t-= Домашнее Задание №27, 1-4 =-\n"
 		<< "\t\tУченик: Шелест Александр\n\n"
 		<< "Написать функции для следующих манипуляций:\n"
 		<< "\t1. добавление столбца двухмерному массиву.\n"
 		<< "\t2. удаление столбца из двухмерного массива.\n"
 		<< "\t3. циклический сдвиг матрицы.\n"
 		<< "\t4. транспонирование матрицы.\n\n";

	matrix* mat = nullptr;

	{
		unsigned width = 0;
		unsigned height = 0;

		safeInput(&width, "Введите начальную ширину матрицы (количество столбцов): ");
		safeInput(&height, "Введите начальную высоту матрицы (количество линий): ");

		mat = new matrix(width, height);
		fill(mat);

		std::cout << "начальная матрицa:\n";
		display(mat);
	}

	std::cout << "Нажмите любую клавишу для перехода в меню...\n";
	std::cin.get();

	unsigned input = -1;
	while (input != 0)
	{
		clrscr();

		std::cout << "\t+==========+\n";
		std::cout << "\t||  МЕНЮ  ||\n";
		std::cout << "\t+==========+\n\n";
		std::cout << "1. добавить столбец в матрицу (задание №1)\n";
		std::cout << "2. удалить столбец из матрицы (задание №2)\n";
		std::cout << "3. циклический сдвиг матрицы (задание №3)\n";
		std::cout << "4. транспонировать матрицу (задание №4)\n";
		std::cout << "\n0. выйти из программы\n\n";

		safeInput(&input, "Введите действие по его номеру в меню: ");

		switch (input)
		{
			case 1:
			{
				unsigned pos = 0;
				int* data = new int[mat->height] {};
				fill(data, mat->height);

				safeInput(&pos, "Введите позицию, в которую нужно добавить столбец: ");

				std::cout << "текущая матрица:\n";
				display(mat);

				addCollumn(mat, pos, data);

				std::cout << "результат операции:\n";
				display(mat);
				std::cout << '\t';
				for (unsigned i = 0; i < pos - 1; i++)
					std::cout << "  ";
				std::cout << "^\n";

				delete[] data;
				break;
			}
			case 2:
			{
				unsigned pos = 0;

				safeInput(&pos, "Введите номер столбца, который нужно удалить: ");

				std::cout << "текущая матрица:\n";
				display(mat);

				removeCollumn(mat, pos);

				std::cout << "результат операции:\n";
				display(mat);
				std::cout << '\t';
				for (unsigned i = 0; i < pos - 1; i++)
					std::cout << "  ";
				std::cout << "\b^\n";	

				break;
			}
			case 3:
			{
				int delta_w = 0;
				int delta_h = 0;

				std::cout << "Введение положительного числа соответствует:\n"
						<< "\tсдвигу вправо (горизонталь)\n"
						<< "\tсдвигу вниз (вертикаль)\n\n";

				std::cout << "Введение отрицательного числа соответствует:\n"
						<< "\tсдвигу влево (горизонталь)\n"
						<< "\tсдвигу вверх (вертикаль)\n\n";

				safeInput(&delta_w, "Введите горизонтальный сдвиг матрицы: ");
				safeInput(&delta_h, "Введите вертикальный сдвиг матрицы: ");

				std::cout << "текущая матрица:\n";
				display(mat);

				shiftMatrix(mat, delta_w, delta_h);

				std::cout << "результат операции:\n";
				display(mat);

				break;
			}
			case 4:
			{
				std::cout << "текущая матрица:\n";
				display(mat);

				transposeMatrix(mat);

				std::cout << "результат операции:\n";
				display(mat);

				break;
			}
			case 0:
				return 0;
			default:
				std::cout << "\n\nВведён некорректный пункт меню\n\n";
				break;
		}

		std::cout << "\n\nНажмите любую клавишу для возвращения в меню...\n";
		std::cin.get();
	}

	return 0;
}

