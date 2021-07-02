/*
	-= Домашнее Задание №14 =-
		Ученик - Шелест Александр
		
	Написать программу, обрабатывающую введённую пользователем строку.
	- Признаком окончания строки есть ";".
	- В ней могут присутствовать скобки различных видов.
	- Нужно проверить корректность написания выражения:
		- совпадает ли количество открытых скобок с количеством закрытых.
		- в правильном ли порядке расположены скобки относительно друг-друга.
	- Нужно уведомить пользователя о правильности записи.
*/

#include <iostream> 	// std::cout; std::cin
#include <cstring> 		// strlen(); strcmp()
#include <clocale> 		// setlocale()

// макросы для вывода сообщений и ошибок на экран
#if defined (_WIN32) or defined (_WIN64)
# include <conio.h>
# include <Windows.h>
  HANDLE h = GetStdHandle(-11);		// STD_OUTPUT_HANDLE
# define log(msg) SetConsoleTextAttribute(h, 0x08); std::cout << "# " << msg << "\n\n"; SetConsoleTextAttribute(h, 0x0F)
# define logerr(msg) SetConsoleTextAttribute(h, 0x04); std::cout << "# " << msg << "\n\n"; SetConsoleTextAttribute(h, 0x0F)
#elif defined (__linux__)
# define log(msg) std::cout << "\e[3;37m# " << msg << "\e[0m\n"
# define logerr(msg) std::cout << "\e[1;31m# ОШИБКА: " << msg << "\e[0m\n"
#endif

// ключевые значения для различных типов допустимыс символов
enum EXPR_SYMBOL
{
	OPEN_PAREN 		= 0x01000000,
	CLOSED_PAREN 	= 0x02000000,
	CONSTANT 			= 0x03000000,
	OPERATION 		= 0x04000000,
	INVALID 			= 0xFF000000
};

// получить тип символа
#define EXPR_SYM_TYPE(v) EXPR_SYMBOL(v & 0xFF000000)

// получить значение символа

#define EXPR_CHAR_VALUE(v) char(v & 0xFF)
#define EXPR_INT_VALUE(v) int(v & 0xFFFFFF)

// преобразовать значение в символ

#define EXPR_CHAR_TO_SYM(c, t) (int(EXPR_INT_VALUE(c)) | t)
#define EXPR_CONST_TO_SYM(v) (EXPR_INT_VALUE(v) | CONSTANT)

// список допустимых скобок
const char open_parens[] { "({[<" };
const char closed_parens[] { ")}]>" };
// список допустимых операций
const char operations[] { "+-*/" };

int mode = 0;


// Стек
template <class T>
class Stack
{
private:
	T* data; 					// непосредственно данные
	T* stackPointer; 	// указатель на вершину стека
	unsigned size; 		// максимальный размер стека

public:
	// конструктор с параметром
	Stack(unsigned size = 1);
	// деструктор
	~Stack();

	// добавить элемент в стек
	void push(T v);
	// удалить элемент из вершины стека
	T pop();

	// просмотреть значение на вершине стека
	T glance() { return *(stackPointer - 1); }
	// провести эффективную очистку стека
	void clear() { stackPointer = data; }

	// проверить стек на пустоту
	bool isEmpty() { return stackPointer == data; }
	// проверить стек на наполненность
	bool isFull() { return  stackPointer == data + size - 1; }
};

template<class T>
Stack<T>::Stack(unsigned size)
{
	// инициализировать поля
	this->size = size;
	data = new T[size]{};
	stackPointer = data;
}

template<class T>
Stack<T>::~Stack()
{
	// освободить динамическую память
	delete[] data;
	stackPointer = nullptr;
}

template<class T>
void Stack<T>::push(T v)
{
	// проверить стек на наличие места
	// если оно есть:
	// - присвоить текущему указателю новое значение
	// - инкрементировать указатель
	if (!isFull())
		*stackPointer++ = v;
}

template<class T>
T Stack<T>::pop()
{
	// проверить стек на наличие элементов
	// если они есть:
	// - декрементировать указатель вершины стека
	// - возвратить значение на вершине стека
	if (!isEmpty())
		return *--stackPointer;
	return 0;
}


// ---------- ФУНКЦИИ ДЛЯ ОБРАБОТКИ СТРОКИ ----------

// проверить, подходят ли скобки друг другу
bool isMatchingParen(char a, char b)
{
	for (int i = 0, size = strlen(open_parens); i < size; i++)
	{
		if (a == open_parens[i] && b == closed_parens[i])
			return true;
		if (a == closed_parens[i] && b == open_parens[i])
			return true;
	}
	
	return false;
}

// пропустить пробелы и табуляции в строке
void skipWs(char*& str)
{
	while (*str == ' ' || *str == '\t')
		str++;
}

// найти тип символа
EXPR_SYMBOL findSymbolType(char c)
{
	for (int i = 0, size = strlen(open_parens); i < size; i++)
		if (c == open_parens[i])
			return OPEN_PAREN;

	for (int i = 0, size = strlen(open_parens); i < size; i++)
		if (c == closed_parens[i])
			return CLOSED_PAREN;

	for (int i = 0, size = strlen(open_parens); i < size; i++)
		if (c == operations[i])
			return OPERATION;
			
	if (c >= '0' && c <= '9')
		return CONSTANT;

	return INVALID;
}

// ---------- ДЕЙСТВИЯ НАД СИМВОЛАМИ ----------

// открытая скобка:
// - добавить в стек
bool handleOpenParen(Stack<int>& stack, char c)
{
	stack.push(EXPR_CHAR_TO_SYM(c, OPEN_PAREN));
	return true;
}

// закрытая скобка:
// - удалить элемент с вершины стека
// - действовать в зависимости от типа символа удалённого элемента:
// - число:
//   - удалить ещё один элемент стека
//   - возвратить число в стек
//   - проверить удалённый символ на корректность
// - открытая скобка:
//   - проверить, подходит ли открытая скобка закрытой
bool handleClosedParen(Stack<int>& stack, char*& expr)
{
	char thisPar = *expr;
	int sym = stack.pop();
	EXPR_SYMBOL sym_type = EXPR_SYM_TYPE(sym);

	if (sym_type == CONSTANT)
	{
		int buff_const = sym;

		skipWs(expr);
		
		sym = stack.pop();

		if (isMatchingParen(EXPR_CHAR_VALUE(sym), thisPar))
		{
			stack.push(buff_const);
			return true;
		}
		logerr("закрытая скобка '" << thisPar
			<< "' не подходит к предыдущей открытой '" << EXPR_CHAR_VALUE(sym) << "'.");

		return false;
	}
	else if (sym_type == OPEN_PAREN)
	{
		if (isMatchingParen(EXPR_CHAR_VALUE(sym), thisPar))
			return true;

		logerr("закрытая скобка '" << thisPar
			<< "' не подходит к предыдущей открытой '" << EXPR_CHAR_VALUE(sym) << "'.");

		return false;
	}
	else
	{
		logerr("символ '" << EXPR_CHAR_VALUE(sym)
			<< "' несовместим с закрытой скобкой '" << thisPar << "'.");
	}
	return false;
}

// число:
// - пока следующий символ является цифрой:
//   - найти соответствующее цифровое значение символа
//   - умножить результат на 10 (так как используется десятичная система)
//   - прибавить найденное число к результату
// - добавить результат в стек
bool handleConstant(Stack<int>& stack, char*& str)
{
	int result = 0;

	while (*str >= '0' && *str <= '9')
	{
		int tmp = int(*str - '0');
		result *= 10;
		result += tmp;
		str++;
	}

	stack.push(EXPR_CONST_TO_SYM(result));

	return true;
}

// операция:
// - удалить два элемента со стека и сохранить их в переменные
// - проверить \ти два элемента на корректность
// - извлечь числовые значения из полученных символов
// - провести указанную арифметическую операцию над операндами
// - добавить результат в стек
bool handleOperation(Stack<int>& stack, char*& expr)
{
	char op = *expr;

	int b_raw = stack.pop();
	int a_raw = stack.pop();

	if (EXPR_SYM_TYPE(b_raw) != CONSTANT || EXPR_SYM_TYPE(a_raw) != CONSTANT)
	{
		logerr("некорректный тип символа для операции '" << op << "', ожидалось два числа.");
		return false;
	}

	int b = EXPR_INT_VALUE(b_raw);
	int a = EXPR_INT_VALUE(a_raw);

	switch (op)
	{
		case '+':
			stack.push(EXPR_CONST_TO_SYM(a + b));
			break;
		case '-':
			stack.push(EXPR_CONST_TO_SYM(a - b));
			break;
		case '*':
			stack.push(EXPR_CONST_TO_SYM(a * b));
			break;
		case '/':
			stack.push(EXPR_CONST_TO_SYM(a / b));
			break;
		default:
			logerr("неизвестный символ операции '" << op << "'.");
			return false;
	}

	return true;
}

// ключевое слово:
// - выполнить действие в зависимости от вводимой строки
bool handleKeywords(char* expr)
{
	if (strcmp(expr, "help") == 0)
	{
		log("Домашнее Задание №14");
		log("\tУченик - Шелест Александр\n");
		log("Программа для обработки введённой пользователем строки.");
		log("Программа проверяет порядок и количество скобок,");
		log("а также умеет выполнять простые арифметические операции (+, -, *, /)\n");
		log("Синтаксис написания выражения:");
		log("\t(операнд1 операнд2 операция);\n");
		log("Примеры:");
		log("(2 1 +);                // = 2 + 1 = 3");
		log("{(16 8 -) 6 *};         // = (16 - 8) * 6 = 8 * 6 = 48");
		log("((((100 1 -) 2 -) 3 -); // = 100 - 1 - 2 - 3 = 94");
		log("({3 2 *} <7 2 -> *);    // = (3 * 2) * (7 - 2) = 6 * 5 = 30\n\n");

		log("Доступные команды:");
		log("\thelp - это сообщение");
		log("\texit - выход из программы");
		log("\tmode0 - включение обработки арифметики (по умолчанию)");
		log("\tmode1 - выключение обработки арифметики. "
				<<	"в этом режиме программа будет проверять только написание скобок.");
		
		return true;
	}
	else if (strcmp(expr, "mode0") == 0)
	{
		mode = 0;
		log("режим обработки арифметики включён.");
		return true;
	}
	else if (strcmp(expr, "mode1") == 0)
	{
		mode = 1;
		log ("режим обработки арифметики отключён");
		return true;
	}
	else if (strcmp(expr, "exit") == 0)
	{
		exit(0);
	}

	return false;
}

// обработать выражение в строке
// - выполнить проверку на ключевые слова
// - инициализировать стек для хранения данных
// - пока указатель строки не дошёл к разрыву:
//   - пропустить пустое место
//   - получить новый элемент строки для обработки
//   - получить тип нового элемента
//   - выполнить действие в зависимости от вида символа
// - возвратить результат выражения
bool evalExpression(char* expr, int* result = 0)
{
// проверить, успешно ли прошла обработка символа
# define assert_expr(b) if (!(b)) { *expr = '\0'; return false; }

	// прекратить выполнение цикла, если было найдено ключевое слово
	if (handleKeywords(expr))
		return true;

	bool encountered_operation = false;
	
	Stack<int> expr_stack(64);

	while (*expr != '\0' && *expr != ';')
	{
		skipWs(expr);
		char c = *expr;

		EXPR_SYMBOL symbol_type = findSymbolType(c);

		switch (symbol_type)
		{
			case OPEN_PAREN:
				assert_expr(handleOpenParen(expr_stack, c))
				break;
			case CLOSED_PAREN:
				assert_expr(handleClosedParen(expr_stack, expr))
				break;
			case CONSTANT:
				encountered_operation = true;
				if (mode == 0)
					assert_expr(handleConstant(expr_stack, expr))
				break;
			case OPERATION:
				encountered_operation = true;
				if (mode == 0)
					assert_expr(handleOperation(expr_stack, expr))
				break;
			case INVALID:
			default:
				if (mode == 0)
					logerr("неизвестный символ '" << c << "'.");
				break;
		}

		expr++;
	}

	// проверить символ на корректность в зависимости от режима работы программы
	*result = expr_stack.pop();

	if (EXPR_SYM_TYPE(*result) != CONSTANT && encountered_operation)
	{
		logerr("нечётное количество открывающихся и закрывающихся скобок.");
		return false;
	}
	
	*result = EXPR_INT_VALUE(*result);
	return true;
}

int main()
{
	// добавить поддержку кириллицы
	setlocale(LC_ALL, "");

	// вывести информацию о программе на экран
	handleKeywords((char*)"help");

	std::cout << "\n\nВведите выражение или команду:";

	// основной цикл выполнения
	while (true)
	{
		// получить строку от пользователя
 		char buff[512]{};
		std::cout << "\n> ";
		std::cin.getline(buff, 512);
		std::cout << '\n';

		// вызвать обработку выражения в строке
		int result = 0;
		bool valid = evalExpression(buff, &result); 

		// вывести результат на экран
		if (valid)
		{
			if (mode == 1)
				log("Выражение синтаксически правильно.");
			else
				log("результат выражения - " << result);
		}
		else
			logerr(buff << " <- ошибка возникла в этой части выражения.");
	}

	// завершение программы
	return 0;
}
