/* 
 * 	-= Домашнее Задание №27, Задача № 5 =-
 * 		Ученик: Шелест Александр
 *
 * 	Создать динамический массив, хранящий в себе последовательность
 * 	из имён и номеров телефонов. 
 * 	Реализовать возможность поиска, добавления и изменения данных.
 */

#include <iostream>
#include <string.h>
#include <clocale>
#include <ctime>

#if defined (_WIN32) or defined (_WIN64)
# include <Windows.h>
#endif

static const char* names[] = { 	
	"имя1", "имя2", "имя3", "имя4", "имя5",
	"имя6", "имя7", "имя8", "имя9", "имя10"
};
static const unsigned n_names = 10;

static const char* phones[] = { 
	"телефон1", "телефон2", "телефон3", "телефон4", "телефон5",
	"телефон6", "телефон7", "телефон8", "телефон9", "телефон10" 
};
static const unsigned n_phones = 10;


// безопасный ввод значения с проверкой на корректность
template <class T>
void safe_input(T& v, const char* msg, bool(*predicate)(const T&) = nullptr)
{
	while (true)
	{
		std::cout << msg;
		std::cin >> v;

		bool success = std::cin.good();

		if (predicate)
			success = success || predicate(v);

		std::cin.clear();
		std::cin.ignore(16, '\n');

		if (success)
			return;

		std::cout << "Введено некорректное значение\n";
	}
}

// безопасный ввод строки с проверкой на корректность
char* safe_getline(const char* msg)
{
	char* buff = new char[256]{};

	while (true)
	{
		std::cout << msg;
		std::cin.getline(buff, 256);

		if (std::cin.good())
			return buff;

		std::cout << "Введено некорректное значение\n";
		memset(buff, 0, 256);
	}

	return nullptr;
}

// контакт телефонной книги
struct entry
{
	char* name = nullptr;
	char* phone = nullptr;

	entry() {}
	// конструктор структуры, копирует параметры себе в поля
	entry(const char* const name, const char* const phone)
	{
		unsigned namelen = strlen(name) + 1;
		unsigned phonelen = strlen(phone) + 1;

		this->name = new char[namelen]{};
		this->phone = new char[phonelen]{};

		memcpy(this->name, name, namelen);
		memcpy(this->phone, phone, phonelen);
	}

	// освободить динамическую память объекта
	void free()
	{
		if (name != nullptr)
			delete[] name;
		if (phone != nullptr)
			delete[] phone;
	}

	// присвоить объекту новое значение
	entry& operator=(const entry& other)
	{
		this->free();

		unsigned namelen = strlen(other.name) + 1;
		unsigned phonelen = strlen(other.phone) + 1;

		this->name = new char[namelen]{};
		this->phone = new char[phonelen]{};

		memcpy(this->name, other.name, namelen);
		memcpy(this->phone, other.phone, phonelen);

		return *this;
	}

	// сравнить два объекта
	bool operator==(const entry& other)
	{
		return (strcmp(name, other.name) == 0) 
			|| (strcmp(phone, other.phone) == 0);
	}

	// сравнить контакт со строкой
	bool operator==(const char* const str)
	{
		return (strcmp(name, str) == 0) 
			|| (strcmp(phone, str) == 0);
	}
};

// телефонная книга
struct phonebook
{
	entry* entries = nullptr;
	size_t size = 0;

	// освободить динамическую память объекта
	void free()
	{
		if (entries == nullptr)
			return;

		for (size_t i = 0; i < size; i++)
			entries[i].free();
	}

	// оператор индексации контактов
	entry& operator[](size_t index) const
	{
		index = (index >= size) ? size - 1 : index;
		return entries[index];
	}

	// добавить новый контакт в книгу
	phonebook& operator+=(const entry& e)
	{
		entry* res = new entry[size + 1]{};

		for (size_t i = 0; i < size; i++)
			res[i] = entries[i];

		res[size] = e;

		size++;
		if (entries != nullptr)
			delete[] entries;
		entries = res;

		return *this;
	}

	// найти контакты в книге, которые подходят по критерию
	phonebook operator&(const entry& e)
	{
		phonebook res;

		for (unsigned i = 0; i < size; i++)
		{
			if (entries[i] == e)
				res += entries[i];
		}

		return res;
	}

	// найти контакты в книге, которые подходят по критерию
	phonebook operator&(const char* const str)
	{
		phonebook res;

		for (unsigned i = 0; i < size; i++)
		{
			if (entries[i] == str)
				res += entries[i];
		}

		return res;
	}
};


// вывод контакта на экран
std::ostream& operator<<(std::ostream& ostr, const entry& e)
{
	ostr << e.name << ", " << e.phone;
	return ostr;
}

// вывод телефонной книги на экран
std::ostream& operator<<(std::ostream& ostr, const phonebook& pb)
{
	if (pb.size == 0)
	{
		ostr << "пусто!\n";
		return ostr;
	}

	for (size_t i = 0; i < pb.size; i++)
		ostr << i + 1 << ". " << pb[i] << '\n';
	return ostr;
}


// заполнить книгу случайными значениями
void phonebook_fill(phonebook& pb, size_t amount)
{
	for (size_t i = 0; i < amount; i++)
	{
		const char* name = names[rand() % n_names];
		const char* phone = phones[rand() % n_phones];
		pb += entry(name, phone);
	}
}

// добавить новый контакт в книгу
void phonebook_addentry(phonebook& pb)
{
	char* name = safe_getline("имя нового контакта: ");
	char* phone = safe_getline("номер телефона нового контакта: ");

	pb += entry(name, phone);

	std::cout << "\nконтакт успешно добавлен в книгу\n";
}

// искать контакты в книге по заданному критерию
void phonebook_searchentry(phonebook& pb)
{
	char* query = safe_getline("введите критерий для поиска (имя или телефон контакта): ");

	std::cout << "результаты поиска:\n";
	std::cout << (pb & query) << '\n';
}

// изменить контакт в книге
void phonebook_editentry(phonebook& pb)
{
	size_t index = 0;
	safe_input(index, "введите номер контакта, который нужно изменить: ");

	char* name = safe_getline("новое имя контакта: ");
	char* phone = safe_getline("новый номер телефона контакта: ");

	pb[index] = entry(name, phone);

	std::cout << "\nданные контакта успешно изменены\n";
}


int main()
{
	srand(time(0));
	setlocale(LC_ALL, "rus");
#if defined (_WIN32) or defined (_WIN64)
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
#endif

	std::cout << "\t-= Домашнее Задание №27, Задача № 5 =-\n"
 		<< "\t\tУченик: Шелест Александр\n\n"
 		<< "Создать динамический массив, хранящий в себе последовательность\n"
 		<< "из имён и номеров телефонов.\n"
 		<< "Реализовать возможность поиска, добавления и изменения данных.\n\n";

	std::cout << "нажмите Enter для выхода в меню...\n";
	std::cin.get();

	phonebook pb;
	phonebook_fill(pb, 8);

	int input = -1;
	while (input != 0)
	{
		std::cout << "\t+============+\n";
		std::cout << "\t||   МЕНЮ   ||\n";
		std::cout << "\t+============+\n\n";
		std::cout << "1. вывести телефонную книгу на экран\n";
		std::cout << "2. добавить новый контакт\n";
		std::cout << "3. искать контакт в книге\n";
		std::cout << "4. редактировать контакт в книге\n";
		std::cout << "\n0. выход из программы\n\n";

		safe_input(input, "выберите действие по его номеру в меню: ");

		switch (input)
		{
		case 1:
			std::cout << "*ТЕЛЕФОННАЯ КНИГА*\n\n";
			std::cout << pb << '\n';
			break;
		case 2:
			std::cout << "*ДОБАВЛЕНИЕ НОВОГО КОНТАКТА*\n\n";
			phonebook_addentry(pb);
			break;
		case 3:
			std::cout << "*ПОИСК КОНТАКТА*\n\n";
			phonebook_searchentry(pb);
			break;
		case 4:
			std::cout << "*РЕДАКТИРОВАНИЕ КОНТАКТА*\n\n";
			phonebook_editentry(pb);
			break;
		case 0:
			exit(0);
		default:
			std::cout << "\nвведен неверный пункт меню\n";
			break;
		}

		std::cout << "\nнажмите Enter для продолжения...\n";
		std::cin.get();
	}
 
	pb.free();

	std::cin.get();
	return 0;
}

