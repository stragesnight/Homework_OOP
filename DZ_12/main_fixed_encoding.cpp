/*
  -= Домашнее Задание №12 =-
    Ученик - Шелест Александр

  Создать класс Employee, содержащий имя и номер служащего.
  Реализовать классы для ввода пользователем данных в объект,
  а также для их вывода на экран.
  Использовать класс в функции main().
*/

// ---------------------------------------------------------------------

/*
		-= Заметка =-
	- Извиняюсь за проблемы с кодировкой!
	
		Кириллицу Visual Studio показывает только при использовании utf8bom,
	а по умолчанию все документы, созданные вне VS, имеют кодировку utf8, 
	поэтому приходится каждый раз менять вручную. 
		В этот раз забыл это сделать, поэтому и были проблемы. Извиняюсь!
	
	- функция clrscr() объявлена на 33 строке как макрос. Очищает экран.
*/

// ---------------------------------------------------------------------

#include <iostream>    // std::cout; std::cin
#include <cstring>     // std::string

// макросы для облегчения жизни
#if defined (_WIN32) or defined (_WIN64)
# include <Windows.h>
# define clrscr() system("cls")
# define handle_locale() SetConsoleCP(1251); SetConsoleOutputCP(1251)
#elif defined (__linux__)
# define clrscr() system("clear")
# define handle_locale() setlocale(LC_ALL, "")
#endif

#define pause_exec() std::cin.ignore(1, '\0'); std::cin.get()

// максимальное количество служащих
#define N_EMPLOYEES 100

// слущащий
class Employee
{
private:
  std::string name;  // имя
  long ID;           // номер

  // проверить номер на колизии с отсальными служащими
  bool isValidID(long ID, const Employee* employees, int nEmployees)
  {
    for (int i = 0; i < nEmployees; i++)
      if (employees[i].ID == this->ID)
	{
	  std::cout << "Введён номер, совпадающий с другим служащим.\n";
	  return false;
	}
	
    return true;
  }
  
public:
  // конструктор с параметрами
  Employee(const std::string& _name = "", long _ID = 0) : name(_name), ID(_ID)
  {}

  // деструктор
  ~Employee()
  {
    name.clear();
  }

  // геттеры для полей
  
  const std::string& getName() { return name; }
  long getID() { return ID; }

  // "сеттер" для полей
  bool getData(const Employee* employees, int nEmployees)
  {
    char buff[64];

    do
    {
      std::cout << "\tВведите номер служащего: ";
      std::cin >> ID;
    } while (!isValidID(ID, employees, nEmployees));

    if (ID == 0)
      return false;

    std::cout << "\tВведите имя служащего: ";
    
    std::cin.ignore(1, '\0');
    std::cin.getline(buff, 64);
    name = buff;

    if (buff[0] == '0')
      return false;

    return true;
  }

  // вывести информацию о служащем на экран
  void putData()
  {
    std::cout << "\tНомер: " << ID << "\n\tИмя: " << name << "\n\n";
  }
};

int main()
{
  // добавить поддержку кириллицы
  handle_locale();

  // рабочие переменные
  Employee employees[100]{};
  int nEmployees = -1;    // начало с -1 для компенсации последнего служащего

  // вывести начальный текст на экран
  std::cout << "\t-= Домашнее Задание №12 =-\n"
	    << "\t\tУченик - Шелест Александр\n\n"
	    << "Создать класс Employee, содержащий имя и номер служащего.\n"
	    << "Реализовать классы для ввода пользователем данных в объект,\n"
	    << "а также для их вывода на экран.\n"
	    << "Использовать класс в функции main().\n\n";

  std::cout << "Вам будет предложено ввести данные для служащих.\n"
	    << "Вы можете ввести '0' в любой момент для завершения ввода.\n";

  // цикл ввода пользователем данных
  do
  {
    nEmployees++;
    std::cout << "\nСлужащий №" << nEmployees + 1 << ".\n";
  } while (employees[nEmployees].getData(employees, nEmployees) && nEmployees < N_EMPLOYEES);

  // вывод данных о служащих
  
  clrscr();

  std::cout << "\n\nКоличество служащих - " << nEmployees << '\n';
  std::cout << "Нажмите Enter для вывода введённой вами информации на экран...\n";
  pause_exec();

  for (int i = 0; i < nEmployees; i++)
  {
    std::cout << "Служащий №" << i + 1 << ":\n";
    employees[i].putData();
  }

  // пауза и завершение работы программы
  pause_exec();
  return 0;
}
