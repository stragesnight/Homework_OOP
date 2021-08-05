/*
	Домашняя работа №24
		Ученик: Шелест Александр
	
	Создать класс "Справочник". Реазлизовать методы взаимодействия с ним.
	Реализовать возможность сохранения и загрузки данных из файла.
*/

#include <iostream>
#include <fstream>
#include <string.h>
#include <vector>
#include <clocale>

#if defined (_WIN32) or defined (_WIN64)
# include <Windows.h>
# define clrscr() system("cls")
#else
# define clrscr() system("clear")
#endif

class Reference
{
private:
	std::string firmName;
	std::string owner;
	std::string phone;
	std::string address;
	std::string activity;

	void setValueOrEmpty(std::string& dst, const std::string& src)
	{
		if (src == "")
			dst = "значение не указано";
		else
			dst = src;
	}

public:
	enum class Field
	{
		ANY = 0,
		FIRM_NAME,
		OWNER,
		PHONE,
		ADDRESS,
		ACTIVITY
	};

	Reference()
	{
		setValueOrEmpty(firmName, "");
		setValueOrEmpty(owner, "");
		setValueOrEmpty(phone, "");
		setValueOrEmpty(address, "");
		setValueOrEmpty(activity, "");
	}

	Reference(const std::string& firmName, const std::string& owner, const std::string& phone, 
			const std::string& address, const std::string& activity)
	{
		setValueOrEmpty(this->firmName, firmName);
		setValueOrEmpty(this->owner, owner);
		setValueOrEmpty(this->phone, phone);
		setValueOrEmpty(this->address, address);
		setValueOrEmpty(this->activity, activity);
	}

	std::string& getFirmName() { return firmName; }
	std::string& getOwner() { return owner; }
	std::string& getPhone() { return phone; }
	std::string& getAddress() { return address; }
	std::string& getActivity() { return activity; }

	void setFirmName(const std::string& firmName)
	{
		setValueOrEmpty(this->firmName, firmName);
	}

	void setOwner(const std::string& owner)
	{
		setValueOrEmpty(this->owner, owner);
	}

	void setPhone(const std::string& phone)
	{
		setValueOrEmpty(this->phone, phone);
	}

	void setAddress(const std::string& address)
	{
		setValueOrEmpty(this->address, address);
	}

	void setActivity(const std::string& activity)
	{
		setValueOrEmpty(this->activity, activity);
	}

	bool isMatchFor(const std::string& query, Field field = Field::ANY)
	{
		if (field == Field::ANY)
		{
			if (query == firmName)
				return true;
			if (query == owner)
				return true;
			if (query == phone)
				return true;
			if (query == address)
				return true;
			if (query == activity)
				return true;

			return false;
		}

		switch (field)
		{
		case Field::FIRM_NAME:
			return query == firmName;
		case Field::OWNER:
			return query == owner;
		case Field::PHONE:
			return query == phone;
		case Field::ADDRESS:
			return query == address;
		case Field::ACTIVITY:
			return query == activity;
		default:
			return false;
		}

		return false;
	}
};

class ReferenceBook
{
private:
	std::vector<Reference>* references;

public:
	ReferenceBook()
	{
		references = new std::vector<Reference>();
	}

	ReferenceBook(const std::vector<Reference>& references)
	{
		this->references = new std::vector<Reference>();
		*this->references = references;
	}

	ReferenceBook(const char* filename)
	{
		references = new std::vector<Reference>();
		loadFromFile(filename);
	}

	~ReferenceBook()
	{
		references->clear();
		delete references;
	}

	void saveToFile(const char* filename, std::ios::openmode om = std::ios::out)
	{
		std::ofstream ofstr(filename, std::ios::out | om);

		for (size_t i = 0, size = references->size(); i < size; i++)
		{
			Reference& curr = references->at(i);
			ofstr << i + 1 << ". " << curr.getFirmName() << '\n';
			ofstr << "Владелец: " << curr.getOwner() << '\n';
			ofstr << "Телефон: " << curr.getPhone() << '\n';
			ofstr << "Адрес: " << curr.getAddress() << '\n';
			ofstr << "Род_деятельности: " << curr.getActivity() << "\n\n";
		}

		ofstr.close();
	}

	bool loadFromFile(const char* filename)
	{
		std::ifstream ifstr(filename);

		if (!ifstr.is_open())
			return false;

		references->clear();

		char buff[512]{};
		char garbage_buff[256]{};

		while (!ifstr.eof())
		{
			Reference toAdd;

# 			define getline_setfield(func) \
				ifstr >> garbage_buff; \
				ifstr.getline(buff, 512); \
				toAdd.func(buff + 1); \
				memset(buff, 0, 512)

			// название фирмы
			getline_setfield(setFirmName);

			if (ifstr.eof())
				break;

			// владелец
			getline_setfield(setOwner);
			// телефон
			getline_setfield(setPhone);
			// адрес
			getline_setfield(setAddress);
			// род деятельности
			getline_setfield(setActivity);

			// пустая линия в конце записи
			ifstr.getline(garbage_buff, 256);

			references->push_back(toAdd);
		}

		ifstr.close();

		return true;
	}

	ReferenceBook searchBy(const std::string& query, Reference::Field field)
	{
		std::vector<Reference> result;

		for (size_t i = 0, size = references->size(); i < size; i++)
		{
			if (references->at(i).isMatchFor(query, field))
				result.push_back(references->at(i));
		}

		return ReferenceBook(result);
	}

	void addReference(const Reference& toAdd)
	{
		references->push_back(toAdd);
	}

	void display()
	{
		if (references->size() == 0)
		{
			std::cout << "Справочник пуст!\n";
			return;
		}

		std::cout << "\t-= Справочник =-\n";

		for (size_t i = 0, size = references->size(); i < size; i++)
		{
			Reference& curr = references->at(i);
			std::cout << i + 1 << ". " << curr.getFirmName() << '\n';
			std::cout << "Владелец: " << curr.getOwner() << '\n';
			std::cout << "Телефон: " << curr.getPhone() << '\n';
			std::cout << "Адрес: " << curr.getAddress() << '\n';
			std::cout << "Род деятельности: " << curr.getActivity() << "\n\n";
		}
	}
};


void addReference(ReferenceBook& rb)
{
	std::cout << "\t*добавление записи в справочник*\n";

	Reference res;
	char buff[512]{};

# 	define cin_setfield(func) \
		std::cin.getline(buff, 512); \
		res.func(buff); \
		memset(buff, 0, 512) 

	std::cout << "Введите название фирмы: ";
	std::cin.ignore(1, '\0');
	cin_setfield(setFirmName);
	std::cout << "Введите владельца: ";
	cin_setfield(setOwner);
	std::cout << "Введите номер телефона: ";
	cin_setfield(setPhone);
	std::cout << "Введите адрес: ";
	cin_setfield(setAddress);
	std::cout << "Введите род деятельности: ";
	cin_setfield(setActivity);

	rb.addReference(res);

	std::cout << "\nЗапись успешно добавлена в справочник.";
}

void searchInBook(ReferenceBook& rb)
{
	std::cout << "\t*поиск записи в справочнике*\n";
	
	char query[512]{};
	unsigned field;

	std::cout << "Возможные параметры для поиска: \n";
	std::cout << "1. Название фирмы\n";
	std::cout << "2. Владелец\n";
	std::cout << "3. Номер телефона\n";
	std::cout << "4. Адрес\n";
	std::cout << "5. Род деятельности\n";
	std::cout << "0. Любой параметр\n\n";

	std::cout << "Введите параметр для поиска по его номеру в списке: ";
	std::cin >> field;

	std::cout << "\nВведите критерий для поиска (строка): ";
	std::cin.ignore(1, '\0');
	std::cin.getline(query, 512);
	
	ReferenceBook result = rb.searchBy(query, (Reference::Field)field);

	std::cout << "\nРезультат поиска: \n\n";
	result.display();
}

void loadBook(ReferenceBook& rb)
{
	std::cout << "\t*загрузка справочника из файла*\n";

	char filename[512]{};
	std::cout << "введите имя файла, с которого будет загружен справочник: ";
	std::cin.ignore(1, '\0');
	std::cin.getline(filename, 512);

	if (rb.loadFromFile(filename))
		std::cout << "\nСправочник успешно загружен.\n";
	else
		std::cout << "\nВозникла ошибка при загрузке из файла.\n";
}

void saveBook(ReferenceBook& rb)
{
	std::cout << "\t*сохранение справочника в файл*\n";

	char filename[512]{};
	unsigned openmode;

	std::cout << "введите имя файла, в который будет сохранён справочник: ";
	std::cin.ignore(1, '\0');
	std::cin.getline(filename, 512);

	std::cout << "\nВарианты сохранения: \n";
	std::cout << "1. Перезаписать файл.\n";
	std::cout << "2. Дописать данные в конец файла.\n\n";

	std::cout << "Введите вариант сохранения по его номеру в списке: ";
	std::cin >> openmode;

	if (openmode == 1)
		rb.saveToFile(filename);
	else
		rb.saveToFile(filename, std::ios::app);

	std::cout << "\nДанные успешно записаны в файл.\n";
}

int main()
{
	setlocale(LC_ALL, "rus");
# 	if defined (_WIN32) or defined (_WIN64)
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
# 	endif

	std::cout << "\tДомашняя работа №24\n"
		<< "\t\tУченик: Шелест Александр\n\n"
		<< "Создать класс \"Справочник\". Реазлизовать методы взаимодействия с ним.\n"
		<< "Реализовать возможность сохранения и загрузки данных из файла.\n\n";

	{
		std::ifstream test("example_rb_shelest.txt");

		if (!test.is_open())
		{
			std::cout << "!! В АРХИВЕ ВЛОЖЕН УЖЕ ГОТОВЫЙ ДЛЯ РАБОТЫ ФАЙЛ !!\n";
			std::cout << "\tпоместите его в папку с порграммой для начала работы с ним.\n\n";
		}

		test.close();
	}

	std::cout << "\nНажмите Enter для выхода в меню...\n";
	std::cin.get();

	ReferenceBook rb("example_rb_shelest.txt");
	int input = -1;

	while (input != 0)
	{
		clrscr();

		std::cout << "\t+==========+\n";
		std::cout << "\t||  МЕНЮ  ||\n";
		std::cout << "\t+==========+\n\n";
		std::cout << "1. Вывод справочника на экран.\n";
		std::cout << "2. Добавление нового элемента в справочник.\n";
		std::cout << "3. Поиск записей в справочнике по значению.\n";
		std::cout << "4. Загрузка справочника из файла.\n";
		std::cout << "5. Сохранение справочника в файл.\n\n";
		std::cout << "0. Выход из программы.\n\n";

		std::cout << "выберите действие по его значению в списке: ";
		std::cin >> input;

		clrscr();

		switch (input)
		{
		case 1:
			rb.display();
			std::cin.ignore(1, '\0');
			break;
		case 2:
			addReference(rb);
			break;
		case 3:
			searchInBook(rb);
			break;
		case 4:
			loadBook(rb);
			break;
		case 5:
			saveBook(rb);
			std::cin.ignore(1, '\0');
			break;
		case 0:
			return 0;
		default:
			std::cout << "\nВыбран неправильный пункт меню.\n";
			break;
		}

		std::cout << "\nНажмите Enter для выхода в меню...\n";
		std::cin.get();
	}

	return 0;
}

