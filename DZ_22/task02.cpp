/*
	Домашняя Работа №22, Задание №2
		Ученик: Шелест Александр
	
	Создать иерархию классов для обработки исключений.
	В ней должны присутствовать классы для различных ситуаций.
*/

#include <iostream> 	// std::cout
#include <stdio.h> 		// sprintf
#include <fstream> 		// std::ifstream; std::ofstream
#include <string.h> 	// memcpy(); strlen()
#include <clocale> 		// setlocale()

// Базовый класс исключения
class Exception
{
protected:
	std::string msg; 	// сообщение исключения
	unsigned code; 		// код ошибки

public:
	// конструктор по умолчанию
	Exception()
	{
		msg = "пустое исключение";
		code = 0;
	}

	// конструктор с параметрами
	Exception(const std::string& msg, unsigned code)
	{
		this->msg = msg;
		this->code = code;
	}

	// виртуальный деструктор
	virtual ~Exception()
	{
		msg.clear();
		code = 0;
	}

	// виртуальный метод для получения текста исключения
	virtual std::string what() const { return msg; }
	// метод для получения кода ошибки
	unsigned what_code() const { return code; }
};


// Арифметическое исключения
class ArithmeticException : public Exception
{
private:
	std::string expr; 	// выражение, в котором произошла ошибка

public:
	// конструтор по умолчанию
	ArithmeticException() 
		: Exception()
	{
		expr = "пустое выражение";
	}

	// конструтор с параметрами
	ArithmeticException(const std::string& msg, const std::string& expr, unsigned code)
		: Exception(msg, code)
	{
		this->expr = expr;
	}

	// перегрузка деструктора
	~ArithmeticException() override
	{
		expr.clear();
	}

	// перегрузка метода получения текста исключения
	std::string what() const override
	{
		return (msg + " в выражении \"" + expr + "\"").c_str();
	}
};


// Исключение памяти
class MemoryException : public Exception
{
private:
	void* loc; 		// укзатель на место в памяти, 
					// где произошла ошибка

public:
	// конструтор по умолчанию
	MemoryException()
		: Exception()
	{
		loc = (void*)0;
	}

	// конструтор с параметрами
	MemoryException(const std::string& msg, void* loc, unsigned code)
		: Exception(msg, code)
	{
		this->loc = loc;
	}

	// перегрузка метода получения текста исключения
	std::string what() const override
	{
		char buff[1024];
// компилятор Visual Studio жалуется на sprintf
# 		if defined (_WIN32) or defined (_WIN64)
			sprintf_s(buff, "%s на адресе памяти %p", msg.c_str(), loc);
# 		else
			sprintf(buff, "%s на адресе памяти %p", msg.c_str(), loc);
# 		endif
		return std::string(buff);
	}
};


// Файловое исключение
class FileException : public Exception
{
private:
	// *ошибка связана с одним из файлов, 
	// хранящихся в этих переменных*

	std::ifstream* ifstr_file;
	std::ofstream* ofstr_file;

public:
	// конструтор по умолчанию
	FileException()
		: Exception()
	{
		ifstr_file = nullptr;
		ofstr_file = nullptr;
	}

	// конструтор с параметрами
	FileException(const std::string& msg, const std::ifstream& ifstr_file, unsigned code)
		: Exception(msg, code)
	{
		this->ifstr_file = new std::ifstream;
		this->ofstr_file = nullptr;

		// прямое копирование памяти не очень надёжно
		memcpy((void*)this->ifstr_file, (void*)&ifstr_file, sizeof(std::ifstream));
	}

	// конструтор с параметрами
	FileException(const std::string& msg, const std::ofstream& ofstr_file, unsigned code)
		: Exception(msg, code)
	{
		this->ifstr_file = nullptr;
		this->ofstr_file = new std::ofstream;

		// прямое копирование памяти не очень надёжно
		memcpy((void*)this->ofstr_file, (void*)&ofstr_file, sizeof(std::ofstream));
	}

	// методы для получения доступа к файлу, с которым произошла ошибка

	const std::ifstream* in_ifstr_file() { return ifstr_file; }
	const std::ofstream* in_ofstr_file() { return ofstr_file; }
};


int main()
{
	setlocale(LC_ALL, "rus");

	std::cout << "\tДомашняя Работа №22, Задание №2\n"
		<< "\t\tУченик: Шелест Александр\n\n"
		<< "Создать иерархию классов для обработки исключений.\n"
		<< "В ней должны присутствовать классы для различных ситуаций.\n\n";

# 	define pause_exec() std::cout << "\nНажмите Enter для продолжения...\n"; std::cin.get()

	////////////////////////////////////////////////////////////////////////////////
	//// 	БАЗОВОЕ ИСКЛЮЧЕНИЕ
	
	pause_exec();
	try
	{
		std::cout << "1. Бросок исключения:\n";
		throw Exception("простое тестовое исключение", 0);
	}
	catch (const Exception& ex)
	{
		std::cout << "ПОЙМАНО ИСКЛЮЧЕНИЕ: "<< ex.what()
			<< "\n\tкод ошибки: "<< ex.what_code() << "\n\n";
	}

	////////////////////////////////////////////////////////////////////////////////
	//// 	АРИФМЕТИЧЕСКОЕ ИСКЛЮЧЕНИЕ
	
	pause_exec();
	try
	{
		std::cout << "2. Попытка деления на ноль (арифметическое исключение):\n";

		int a = 64;
		int b = 0;

		if (b == 0)
			throw ArithmeticException("невозможно поделить на 0", "64 / 0", 1);

		int res = a / b;
		std::cout << "64 / 0 = " << res;
	}
	// так как ArithmeticException наследуется от Expression,
	// сработает первый блок catch.
	// Но в силу того, что метод what() - виртуальный,
	// результат не изменится.
	catch (const Exception& ex)
	{
		std::cout << "ПОЙМАНО ИСКЛЮЧЕНИЕ: "<< ex.what()
			<< "\n\tкод ошибки: "<< ex.what_code() << "\n\n";
	}
	catch (const ArithmeticException& ex)
	{
		std::cout << "ПОЙМАНО АРИФМЕТИЧЕСКОЕ ИСКЛЮЧЕНИЕ: "<< ex.what()
			<< "\n\tкод ошибки: "<< ex.what_code() << "\n\n";
	}

	////////////////////////////////////////////////////////////////////////////////
	//// 	ИСКЛЮЧЕНИЕ ПАМЯТИ
	
	pause_exec();
	try
	{
		std::cout << "3. Попытка записать значение в недоступный адрес памяти:\n";
		int* arr = new int[16] {};

		size_t index = 0;
		if (index >= 16)
			throw MemoryException("невозможно записать значение", arr + index, 2);
		arr[index] = rand();

		std::cout << "Значение успешно записано в начало массива (доступный адрес).\n";

		index = 18;
		if (index >= 16)
			throw MemoryException("невозможно записать значение", arr + index, 2);
		arr[index] = rand();

		std::cout << "Значение успешно записано недоступный адрес.\n";
	}
	catch (const MemoryException& ex)
	{
		std::cout << "ПОЙМАНО ИСКЛЮЧЕНИЕ ПАМЯТИ: "<< ex.what()
			<< "\n\tкод ошибки: "<< ex.what_code() << "\n\n";
	}

	////////////////////////////////////////////////////////////////////////////////
	//// 	ФАЙЛОВОЕ ИСКЛЮЧЕНИЕ
	
	pause_exec();
	try
	{
		std::cout << "4. Попытка открыть файл (который вряд ли существует):\n";

		std::ifstream some_file("test_file1_with_unlikely_to_find_name");

		if (!some_file.is_open())
			throw FileException("невозможно открыть файл", some_file, 3);
		
		std::cout << "Файл открыт успешно (хоть и не должен был).\n";
	}
	catch (const FileException& ex)
	{
		std::cout << "ПОЙМАНО ФАЙЛОВОЕ ИСКЛЮЧЕНИЕ: "<< ex.what()
			<< "\n\tкод ошибки: "<< ex.what_code() << "\n\n";
	}


	std::cout << "Тест завершён. Теперь вы можете выйти из программы.\n";

	std::cin.get();
	return 0;
}

