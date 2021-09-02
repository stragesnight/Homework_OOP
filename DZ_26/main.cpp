/*
 * 	-= Домашнее Задание №26 =-
 * 		Ученик: Шелест Александр
 *
 * 	Создать класс "Справочник" с соответствующими полями,
 * 	реализовать возможность просмотра, добавления, удаления и поиска контактов.
 * 	Также добавить возможность загружать и сохранять данные в файл.
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

class Handbook
{
public:
	class Entry
	{
	private:
		std::string name;
		std::string owner;
		std::string phone;
		std::string address;
		std::string activity;

		void setFieldOrEmpty(std::string& dst, const std::string& src = "")
		{
			dst = (src == "") ? "*not specified*" : src;
		}

	public:
		enum class Field
		{
			ANY 		= 0,
			NAME 		= 1,
			OWNER 		= 3,
			PHONE 		= 4,
			ADDRESS 	= 5,
			ACTIVITY 	= 6
		};

		Entry()
		{
			setFieldOrEmpty(name);
			setFieldOrEmpty(owner);
			setFieldOrEmpty(phone);
			setFieldOrEmpty(address);
			setFieldOrEmpty(activity);
		}

		Entry(const std::string& name, const std::string& owner, const std::string& phone,
				const std::string& address, const std::string& activity)
		{
			setFieldOrEmpty(this->name, name);
			setFieldOrEmpty(this->owner, owner);
			setFieldOrEmpty(this->phone, phone);
			setFieldOrEmpty(this->address, address);
			setFieldOrEmpty(this->activity, activity);
		}

		Entry(const Entry& other)
		{
			setFieldOrEmpty(this->name, other.name);
			setFieldOrEmpty(this->owner, other.owner);
			setFieldOrEmpty(this->phone, other.phone);
			setFieldOrEmpty(this->address, other.address);
			setFieldOrEmpty(this->activity, other.activity);
		}

		std::string& getName() { return name; }
		std::string& getOwner() { return owner; }
		std::string& getPhone() { return phone; }
		std::string& getAddress() { return address; }
		std::string& getActivity() { return activity; }

		void setName(const std::string& name)
		{
			setFieldOrEmpty(this->name, name);
		}

		void setOwner(const std::string& owner)
		{
			setFieldOrEmpty(this->owner, owner);
		}

		void setPhone(const std::string& phone)
		{
			setFieldOrEmpty(this->phone, phone);
		}

		void setAddress(const std::string& address)
		{
			setFieldOrEmpty(this->address, address);
		}

		void setActivity(const std::string& activity)
		{
			setFieldOrEmpty(this->activity, activity);
		}


		bool isMatchFor(const std::string& query, Field field = Field::ANY)
		{
			if (field == Field::ANY)
			{
				if (query == name)
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
			case Field::NAME:
				return query == name;
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

private:
	std::vector<Entry*>* entries;

public:
	Handbook(const std::vector<Entry*>* entries = nullptr)
	{
		this->entries = new std::vector<Entry*>();

		if (entries != nullptr)
			*this->entries = *entries;
	}

	Handbook(const char* filepath)
	{
		entries = new std::vector<Entry*>();
		loadFromFile(filepath);
	}

	~Handbook()
	{
		for (unsigned i = 0, size = entries->size(); i < size; i++)
			delete entries->at(i);

		entries->clear();
		delete entries;
	}

	void saveToFile(const char* filepath, std::ios::openmode om = std::ios::out)
	{
		std::ofstream ofstr(filepath, std::ios::out | om);

		for (size_t i = 0, size = entries->size(); i < size; i++)
		{
			Entry* curr = entries->at(i);
			ofstr << i + 1 << ". " << curr->getName() << '\n';
			ofstr << "Владелец: " << curr->getOwner() << '\n';
			ofstr << "Телефон: " << curr->getPhone() << '\n';
			ofstr << "Адрес: " << curr->getAddress() << '\n';
			ofstr << "Род_деятельности: " << curr->getActivity() << "\n\n";
		}

		ofstr.close();
	}

	bool loadFromFile(const char* filepath)
	{
		std::ifstream ifstr(filepath);

		if (!ifstr.is_open())
			return false;

		entries->clear();

		char buff[512]{};
		char garbage_buff[256]{};

		while (!ifstr.eof())
		{
			Entry* toAdd = new Entry();

# 			define getline_setfield(func) 		\
				ifstr >> garbage_buff;  		\
				ifstr.getline(buff, 512);  		\
				toAdd->func(buff + 1);  		\
				memset(buff, 0, 512)

			// название фирмы
			getline_setfield(setName);

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

			entries->push_back(toAdd);
		}

		ifstr.close();

		return true;
	}

	Handbook searchEntry(const std::string& query, Handbook::Entry::Field field)
	{
		std::vector<Entry*> result;

		for (size_t i = 0, size = entries->size(); i < size; i++)
		{
			if (entries->at(i)->isMatchFor(query, field))
				result.push_back(new Entry(*entries->at(i)));
		}

		return Handbook(&result);
	}

	void addEntry(const Entry* const entry)
	{
		entries->push_back(new Entry(*entry));
	}

	void display()
	{
		if (entries->size() == 0)
		{
			std::cout << "Справочник пуст!\n";
			return;
		}

		std::cout << "\t-= Справочник =-\n";

		for (size_t i = 0, size = entries->size(); i < size; i++)
		{
			Entry* curr = entries->at(i);
			std::cout << i + 1 << ". " << curr->getName() << '\n';
			std::cout << "Владелец: " << curr->getOwner() << '\n';
			std::cout << "Телефон: " << curr->getPhone() << '\n';
			std::cout << "Адрес: " << curr->getAddress() << '\n';
			std::cout << "Род деятельности: " << curr->getActivity() << "\n\n";
		}
	}
};

void addEntryToHandbook(Handbook* const hb)
{
	std::cout << "\t*добавление записи в справочник*\n";

	Handbook::Entry res;
	char buff[512]{};

# 	define cin_setfield(func) \
		std::cin.getline(buff, 512); \
		res.func(buff); \
		memset(buff, 0, 512) 

	std::cout << "Введите название фирмы: ";
	std::cin.ignore(1, '\0');
	cin_setfield(setName);
	std::cout << "Введите владельца: ";
	cin_setfield(setOwner);
	std::cout << "Введите номер телефона: ";
	cin_setfield(setPhone);
	std::cout << "Введите адрес: ";
	cin_setfield(setAddress);
	std::cout << "Введите род деятельности: ";
	cin_setfield(setActivity);

	hb->addEntry(&res);

	std::cout << "\nЗапись успешно добавлена в справочник.";
}

void searchEntryInHandbook(Handbook* const hb)
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
	
	Handbook result = hb->searchEntry(query, (Handbook::Entry::Field)field);

	std::cout << "\nРезультат поиска: \n\n";
	result.display();
}

void loadHandbook(Handbook* const hb)
{
	std::cout << "\t*загрузка справочника из файла*\n";

	char filepath[512]{};
	std::cout << "введите имя файла, с которого будет загружен справочник: ";
	std::cin.ignore(1, '\0');
	std::cin.getline(filepath, 512);

	if (hb->loadFromFile(filepath))
		std::cout << "\nСправочник успешно загружен.\n";
	else
		std::cout << "\nФайл не найден. Повторите попытку с другим файлом.\n";
}

void saveHandbook(Handbook* const hb)
{
	std::cout << "\t*сохранение справочника в файл*\n";

	char filepath[512]{};
	unsigned openmode;

	std::cout << "введите имя файла, в который будет сохранён справочник: ";
	std::cin.ignore(1, '\0');
	std::cin.getline(filepath, 512);

	std::cout << "\nВарианты сохранения: \n";
	std::cout << "1. Перезаписать файл.\n";
	std::cout << "2. Дописать данные в конец файла.\n\n";

	std::cout << "Введите вариант сохранения по его номеру в списке: ";
	std::cin >> openmode;

	if (openmode == 1)
		hb->saveToFile(filepath);
	else
		hb->saveToFile(filepath, std::ios::app);

	std::cout << "\nДанные успешно записаны в файл.\n";
}

int main()
{
	setlocale(LC_ALL, "rus");

# 	if defined (_WIN32) or defined (_WIN64)
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
# 	endif

	std::cout << "\t-= Домашнее Задание №26 =-\n"
 		"\t\tУченик: Шелест Александр\n\n"
 		"Создать класс \"Справочник\" с соответствующими полями,\n"
 		"реализовать возможность просмотра, добавления, удаления и поиска контактов.\n"
 		"Также добавить возможность загружать и сохранять данные в файл.\n\n";

	{
		std::ifstream test("example_hb_shelest.txt");

		if (!test.is_open())
		{
			std::cout << "!! В АРХИВЕ ВЛОЖЕН УЖЕ ГОТОВЫЙ ДЛЯ РАБОТЫ ФАЙЛ !!\n";
			std::cout << "\tпоместите его в папку с порграммой для начала работы с ним.\n\n";
		}

		test.close();
	}

	std::cout << "\nНажмите Enter для выхода в меню...\n";
	std::cin.get();

	Handbook hb("example_hb_shelest.txt");
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
			hb.display();
			std::cin.ignore(1, '\0');
			break;
		case 2:
			addEntryToHandbook(&hb);
			break;
		case 3:
			searchEntryInHandbook(&hb);
			break;
		case 4:
			loadHandbook(&hb);
			break;
		case 5:
			saveHandbook(&hb);
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

