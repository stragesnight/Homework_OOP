/*
	Домащнее Задание №20
		Ученик: Шелест Александр

	Написать пример программы с использованием
	абстрактного класса и виртуального деструктора
	
	Эта программа вычисляет результат введённого выражения,
	описываемого вызовом функции с параметрами.
*/

#include <iostream>  // std::cout; std::cin;
#include <clocale>   // setlocale()
#include <cstring>   // std::string
#include <vector>    // std::vector
#include <map>       // std::map

// макросы для логов
#define log(msg) std::cout << "# " << msg << '\n'
#define logerr(msg) std::cout << "# ERROR: " << msg << '\n'

// объявление базового класса
class Node;

// инструкции, доступные программе
std::map<std::string, Node*> expressions;
// директивы, доступные программе
std::map<std::string, void(*)(const char*)> directives;

// реализация базового абстрактного класса
class Node
{
protected:
	char* name;     // имя выражения
	size_t nArgs;   // количество требуемых аргкментов

public:
	// конструктор с параметрами
	Node(const char* name, size_t nArgs = 0)
	{
		this->nArgs = nArgs;

		size_t len = strlen(name);
		this->name = new char[len + 1];

		for (size_t i = 0; i < len; i++)
			this->name[i] = name[i];
		this->name[len] = '\0';
	}

	// виртуальный деструктор, освобождает динамическую память
	virtual ~Node()
	{
		delete[] name;
	}

	// геттеры для полей
	
	size_t getNArgs() { return nArgs; }
	const char* getName() { return name; }

	// получить результат выражения,
	// чистая виртуальная функция
	virtual long evaluate(std::vector<Node*>* args) = 0;
};


// Числовое выражение
class NumericNode : public Node
{
private:
	long value;   // значение, хранимое выражением

public:
	// конструктор с параметрами, дополняющий базовый
	NumericNode(const char* name, long value)
		: Node(name, 0)
	{
		this->value = value;
	}

	// перегрузка деструктора
	~NumericNode() override
	{
		value = 0;
	}

	// перегрузка вычисления
	long evaluate(std::vector<Node*>*) override
	{
		return value;
	}
};


// Функциональное выражение
class ExpressionNode : public Node
{
private:
	// указатель на функцию, связанную с этим выражением
	long (*func)(std::vector<Node*>*);

public:
	// конструктор с параметрами, дополняющий базовый
	ExpressionNode(const char* name, size_t nArgs, long(*func)(std::vector<Node*>*))
		: Node(name, nArgs)
	{
		this->func = func;
	}

	// перегрузка деструктора
	~ExpressionNode() override
	{
		func = nullptr;
	}

	// перегрузка вычисления
	long evaluate(std::vector<Node*>* args) override
	{
		// вызов связанной функции с параметрами
		return func(args);
	}
};

/////////////////////////////////////////////////////////////////////////////////////
// РАБОЧИЕ ФУНКЦИИ

// обработать строку и получить числовое значение
long parseNumber(const char* buff)
{
	long result = 0;
	short mul = 1;
	size_t len = strlen(buff);
	
	for (size_t i = 0; i < len; i++)
	{
		if (buff[i] == '-')
		{
			mul *= -1;
			continue;
		}
	
		result *= 10;
		result += buff[i] - '0';
	}

	return result * mul;
}

// пропустить пустое место в выражении
void skipWS(const char* str, size_t& i)
{
	while (str[i] == ' ' || str[i] == '\t')
		i++;
}

// прочитать слово в строке
int readWord(const char* src, char* buff, size_t& i)
{
	size_t len = 0;

	skipWS(src, i);

	if (src[i] == '!')
	{
		buff[len] = src[i];
		len++;
		i++;
		return len;
	}

	while ((src[i] >= 'a' && src[i] <= 'z')
		|| (src[i] >= 'A' && src[i] <= 'Z')
		|| (src[i] >= '0' && src[i] <= '9')
		|| (src[i] == '-'))
	{
		buff[len] = src[i];
		len++;
		i++;
	}

	return len;
}

/////////////////////////////////////////////////////////////////////////////////////

// Макро-выражение
class MacroNode : public Node
{
private:
	// тип слова
	enum class WORD_TYPE
	{
		SYMBOL,
		NUMERIC,
		DIRECTIVE,
		UNRECOGNIZED
	};

	// строка выражения
	char* expr;

	// рабочие методы

	// получить тип слова со строки
	WORD_TYPE getWordType(const char* str)
	{
		if (*str == '!')
			return WORD_TYPE::DIRECTIVE;

		if ((*str >= 'a' && *str <= 'z')
			|| (*str >= 'A' && *str <= 'Z'))
			return WORD_TYPE::SYMBOL;

		if ((*str >= '0' && *str <= '9')
			|| (*str == '-'))
			return WORD_TYPE::NUMERIC;

		return WORD_TYPE::UNRECOGNIZED;
	}

	// вычислить результат функции
	long evalNode(Node* node, const char* rest, size_t& i)
	{
		size_t nArgs = node->getNArgs();

		char buff[64]{};
		std::vector<Node*> args;

		// попытаться прочитать nArgs количество аргументов для вызова
		for (size_t n = 0; n < nArgs; n++)
		{
			if (!readWord(rest, buff, i))
			{
				logerr("not enough arguments for symbol \"" << node->getName() << "\"");
				return -1;
			}

			WORD_TYPE word_type = getWordType(buff);

			switch (word_type)
			{
			case WORD_TYPE::NUMERIC:
			{
				args.push_back(new NumericNode("arg", parseNumber(buff)));
				break;
			}
			case WORD_TYPE::SYMBOL:
			{
				Node* next_node = expressions[buff];

				if (next_node == nullptr)
				{
					logerr("unable to find symbol \"" << buff << "\" in list");
					return -1;
				}

				args.push_back(new NumericNode("arg", evalNode(next_node, rest, i)));
				break;
			}
			case WORD_TYPE::UNRECOGNIZED:
			default:
				logerr("unexpected symbol \"" << buff << '\"');
				return -1;
			}

			memset(buff, 0, 64);
		}

		return node->evaluate(&args);
	}

public:
	// конструктор с параметрами, дополняющий базовый
	MacroNode(const char* name, const char* expr)
		: Node(name, 0)
	{
		size_t len = strlen(expr);
		this->expr = new char[len + 1];

		for (size_t i = 0; i < len; i++)
			this->expr[i] = expr[i];
		this->expr[len] = '\0';
	}

	// перегрузка деструктора
	~MacroNode() override
	{
		delete expr;
	}

	// перегрузка вычисления
	long evaluate(std::vector<Node*>* args) override
	{
		long result = -1;

		if (strlen(expr) == 0)
			return 0;

		size_t i = 0;
		char buff[64]{};

		readWord(expr, buff, i);
		WORD_TYPE word_type = getWordType(buff);

		switch (word_type)
		{
		case WORD_TYPE::NUMERIC:
		{
			result = parseNumber(buff);
			break;
		}
		case WORD_TYPE::SYMBOL:
		{
			Node* node = expressions[buff];

			if (node == nullptr)
			{
				logerr("symbol \"" << buff << "\" is undefined");
				return -1;
			}

			result = evalNode(node, expr, i);
			break;
		}
		case WORD_TYPE::DIRECTIVE:
		{
			memset(buff, 0, 64);
			readWord(expr, buff, i);

			void(*directive)(const char*) = directives[buff];

			if (directive == nullptr)
			{
				logerr("directive \"" << buff << "\" is undefined");
				return -1;
			}

			directive(expr + i);

			return 1;
		}
		case WORD_TYPE::UNRECOGNIZED:
		default:
		{
			logerr("unexpected symbol \"" << buff << "\"");
			return -1;
		}
		}

		memset(buff, 0, 64);
		if (readWord(expr, buff, i))
		{
			logerr("unexpected symbol \"" << buff << "\" after finished expression");
			logerr("unexpected tail symbol would be ignored");
		}

		return result;
	}
};

/////////////////////////////////////////////////////////////////////////////////////
// ВСТРОЕННЫЕ ДИРЕКТИВЫ

// связать слово с выражением
void d_def(const char* str)
{
	char buff[64] {};
	size_t i = 0;

	readWord(str, buff, i);
	MacroNode* to_add = new MacroNode(buff, str + i);

	expressions[buff] = to_add;

	log("defined \"" << str + i + 1 << "\" as \"" << buff << '\"');
}

// выйти из программы
void d_exit(const char*)
{
	exit(0);
}

// помощь
void d_help(const char* str)
{
#define pause() \
		std::cout << "Нажмите Enter для продолжения...\n";	\
		std::cin.get(); 
	log("\tДомашнее Задание № 20");
	log("\t\tУченик: Шелест Алексадр");
	log("");
	log("Написать пример программы с использованием");
	log("Абстрактного класса и виртуального деструктора.");
	pause();
	log("----------------------------------------------");
	log("!!!Диаграмма классов для этой программы находится в архиве!!!");
	log("----------------------------------------------");
	log("Эта программа вычисляет результат введённого выражения");
	log("описываемого вызовом функции с её параметрами.");
	log("* Пример - \"add 3 2\" приводит к результату 5");
	log("----------------------------------------------");
	log("* Синтаксис записи - { имяФункции парам1 парам2 парам3 ... }");
	log("Параметром функции может выступать результат другой функции:");
	log("* Пример:");
 	log("\"mul 4 add 3 3\" соответствует записи \"mul(4, add(3, 3))\" в С/С++");
	log("Результат вышеуказанного выражения - 24.");
	log("");
	pause();
	log("Список доступных функций: ");
	log("* add  - сложение,  кол. аргументов - 2");
	log("* sub  - вычитание, кол. аргументов - 2");
	log("* mul  - умножение, кол. аргументов - 2");
	log("* div  - деление,   кол. аргументов - 2");
	log("* even - проверка числа на чётность,   кол. аргументов - 1");
	log("* odd  - проверка числа на нечётность, кол. аргументов - 1");
	pause();
	log("----------------------------------------------");
	log("В арсенале программы присутствуют директивы - ");
	log("аналог препроцессора в С/С++.");
	log("Список доступных директив: ");
	log("* !def - привязать какое-либо значение к слову (примеры ниже)");
	log("* !exit - выход из программы");
	log("* !help - это сообщение");
	pause();
	log("----------------------------------------------");
	log("Примеры выражений:");
	log("Пример 1 - простой вызов функции");
	log("> div 12 3");
	log("Пример 2 - вызов функции с вложенными вызовами");
	log("> mul 5 sub mul odd 2 2 1");
	log("Пример 3 - объявление переменной");
	log("> !def a 3");
	log("> !def b 5");
	log("> a");
	log("> b");
	log("> sub a b");
	log("Пример 4 - объявление функции и её вложенный вызов");
	log("> !def square mul x x");
	log("> !def x 2");
	log("> square");
	log("> !def x 3");
	log("> sub square 1");
	log("> !def cube mul mul x x x");
	log("> cube");
	log("> !def x 5");
	log("> cube");
}

/////////////////////////////////////////////////////////////////////////////////////
// ВСТРОЕННЫЕ ФУНКЦИИ

// сложение
long e_add(std::vector<Node*>* args)
{
	return args->at(0)->evaluate(nullptr) + args->at(1)->evaluate(nullptr);
}

// вычитание
long e_sub(std::vector<Node*>* args)
{
	return args->at(0)->evaluate(nullptr) - args->at(1)->evaluate(nullptr);
}

// умножение
long e_mul(std::vector<Node*>* args)
{
	return args->at(0)->evaluate(nullptr) * args->at(1)->evaluate(nullptr);
}

// деление
long e_div(std::vector<Node*>* args)
{
	return args->at(0)->evaluate(nullptr) / args->at(1)->evaluate(nullptr);
}

// проверка на чётность
long e_even(std::vector<Node*>* args)
{
	return (args->at(0)->evaluate(nullptr) & 1) == 0;
}

// проверка на нечётность
long e_odd(std::vector<Node*>* args)
{
	return (args->at(0)->evaluate(nullptr) & 1) == 1;
}

/////////////////////////////////////////////////////////////////////////////////////
// MAIN

int main()
{
	setlocale(LC_ALL, "rus");

	// бавить встроенные функции в список выражений
	expressions["add"] = new ExpressionNode("add", 2, e_add);
	expressions["sub"] = new ExpressionNode("sub", 2, e_sub);
	expressions["mul"] = new ExpressionNode("mul", 2, e_mul);
	expressions["div"] = new ExpressionNode("div", 2, e_div);
	expressions["even"] = new ExpressionNode("even", 1, e_even);
	expressions["odd"] = new ExpressionNode("odd", 1, e_odd);

	// добавить директивы в список
	directives["def"] = d_def;
	directives["exit"] = d_exit;
	directives["help"] = d_help;

	// вывод начального текста на экран
	{
		MacroNode helpNode("helpNode", "!help");
		helpNode.evaluate(nullptr);
	}
	
	// основной цикл выполнения
	while (true)
	{
		char input[512] {};
		std::cout << "\n> ";
		std::cin.getline(input, 512);

		MacroNode expression("expr", input);
		long result = expression.evaluate(nullptr);
		log("result: " << result);
	}

	// завершение программы
	expressions.clear();
	directives.clear();
	return 0;
}

