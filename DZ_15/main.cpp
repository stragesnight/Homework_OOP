/*
	-= Домашнее Задание №15 =-
		Ученик - Шелест Александр

	Реализовать стек при помощи односвязного списка.
	Класс должен иметь соответствующие операции со стеком.
*/

#include <iostream>	// std::cout; std::cin;
#include <clocale>	// setlocale()
#include <ctime>		// time()

// макрос для очистки экрана
#if defined (_WIN32) or defined (_WIN64)
# define clrscr() system("cls")
#elif defined (__linux__)
# define clrscr() system("clear")
#endif

// вывести строку на экран
#define log(msg) std::cout << msg << '\n'
// вывести строку с разделением на экран
#define logln(msg) std::cout << '\n' << msg << '\n'
// сокращение выражения
#define templated template <class T>

// Стек, использующий односвязный список
templated class LinkedStack
{
private:
	// структура, отображающая элемент стека
	struct Element
	{
		T data; 				// данные
		Element* next; 	// указатель на следующий элемент
	};

	Element* head; 		// вершина стека
	Element* tail; 		// начало стека
	unsigned depth; 	// глубина стека

	public:
	// /конструктор по умолчанию
	LinkedStack();
	// деструктор
	~LinkedStack();

	// получить глубину стека (количество хранимых элементов)
	unsigned getDepth() { return depth; }

	// добавить элемент а стек
	void push(T v);
	// удалить элемент из вершины стека и возвратить его значение
	T pop();
	// возвратить значение из вершины стека, не удаляя его
	T glance();

	// проверить пуст ли стек
	bool isEmpty() { return depth == 0 || head == nullptr; }

	// очистить стек
	void clear();
	// вывести \лементы стека на экран
	void display();
};

templated LinkedStack<T>::LinkedStack()
{
	// изначальная глубина - 0
	depth = 0;

	// добавить корневой элемент для корректной работы
	Element* root = new Element;
	root->data = 0;
	root->next = nullptr;
	head = tail = root;
}

templated LinkedStack<T>::~LinkedStack()
{
	// очистить стек
	clear();
}

templated void LinkedStack<T>::push(T v)
{
	// создать новый элемент и наполнить его данными
	Element* tmp = new Element;
	tmp->data = v;
	tmp->next = nullptr;

	// добавить новый элемент в цепочку
	head->next = tmp;
	head = tmp;

	// инкрементировать глубину
	depth++;
}

templated T LinkedStack<T>::pop()
{
	// возвратить 0, если стек пуст
	if (isEmpty())
		return T(0);

	// найти предпоследний элемент
	Element* tmp = tail;
	while (tmp->next != head)
		tmp = tmp->next;

	// сохранить даные вершины
	T tmpData = head->data;
	// удалить вершину
	delete head;

	// сделать предпослений элемент вершиной стека
	tmp->next = nullptr;
	head = tmp;

	// декрементировать глубину
	depth--;
	return tmpData;
}

templated T LinkedStack<T>::glance()
{
	// возвратить значение элемента на вершине стека или 0, если стек пуст
	return head != nullptr ? head->data : T(0);
}

templated void LinkedStack<T>::clear()
{
	// удалять элементы из стека, пока стек не станет пустым
	while (depth > 0)
		pop();

	// удалить корневой элемент
	delete tail;
}

templated void LinkedStack<T>::display()
{
	// начать отображение с первого элемента
	Element* tmp = tail->next;

	logln("глубина стека: "<< depth << " элемент(-а/-ов).");

	for (int i = 0; i < depth; i++)
		std::cout << "---";
	std::cout << "--\n| ";
	
	while (tmp != nullptr)
	{
		std::cout << tmp->data << ' ';
		tmp = tmp->next;
	}
	
	std::cout << "\n--";
	for (int i = 0; i < depth; i++)
		std::cout << "---";
	std::cout << "\n\n";
}


int main()
{
	// инициализировать генератор случайных чисел
	srand(time(0));
	// добавить поддержку кириллицы
	setlocale(LC_ALL, "");

	// вывести начальный текст на экран
	log("\t-= Домашнее Задание №15 =-");
	log("\t\tУченик - Шелест Александр\n");
	log("Реализовать стек при помощи односвязного списка.");
	log("Класс должен иметь соответствующие операции со стеком.\n");

	logln("нажмите Enter для перехода в меню...");
	std::cin.get();

	// инициализировать стек
	LinkedStack<int> lstack;

	unsigned input = -1;

	// основной цикл выполнения
	while (input != 0)
	{
		clrscr();

		log("-=== МЕНЮ ===-");
		log("");
		log("1. Добавить элемент в стек.");
		log("2. Удалить элемент из стека.");
		log("3. Наполнить стек случайными значениями.");
		log("4. Очистить стек.");
		log("5. Проверить, пуст ли стек.");
		log("6. Показать элемент на вершине стека.");
		log("7. Вывести стек на экран.");
		log("");
		log("0. Выйти из программы.");

		std::cout << "\n\nвведите действие по соответствующему номеру меню: ";
		std::cin >> input;

		switch (input)
		{
		case 1:
		{
			int tmp;
			std::cout << "введите значение для добавления в стек: ";
			std::cin >> tmp;
			lstack.push(tmp);
			break;
		}
		
		case 2:
			logln("элемент '" << lstack.pop() << "' был удален из стека.");
			break;

		case 3:
			for (int i = 0; i < 8; i++)
				lstack.push(rand() % 32);

			logln("в стек было добавлено 8 случайных значений.");
			break;

		case 4:
			logln(lstack.getDepth() << " элемент(-а/-ов) было удалено из стека.");
			lstack.clear();
			break;

		case 5:
			if (lstack.isEmpty())
				logln("стек пуст.");
			else
				logln("стек не пуст.");
			break;

		case 6:
			logln("значение элемента на вершине стека равно '" << lstack.glance() << "'.");
			break;

		case 7:
			lstack.display();
			break;

		case 0:
			return 0;

		default:
			logln("некорректный пункт меню '" << input << "'.");
			break;
		}

		// пауза программы
		logln("нажмите Enter для возвращения в меню...");
		std::cin.ignore(1, '\0');
		std::cin.get();
		std::cin.clear();
	}

	// выход из программы
	return 0;
}
