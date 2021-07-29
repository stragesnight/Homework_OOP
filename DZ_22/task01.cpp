/*
	Домашняя Работа №22, Задание №1
		Ученик: Шелест Александр

	Добавить в класс двухсвязного списка механизм обработки
	исключений. На своё усмотрение генерировать их при ошибках.
*/

#include <iostream> 	// std::cout; std::cin
#include <string.h> 	// strlen
#include <clocale> 		// setlocale()

// макрос для очистки экрана
#if defined (_WIN32) or defined (_WIN64)
# define clrscr() system("cls")
#else
# define clrscr() system("clear")
#endif

#define templated template <class T>

// Двухсвязный список
templated class DoublyLinkedList
{
private:
	// вложенный класс элемента списка
	struct Node
	{
		T data;  		// данные
		Node* prev; 	// предыдущий элемент
		Node* next; 	// следующий элемент
	};

	Node* head; 		// первый элемент
	Node* tail; 		// последний элемент

	size_t size; 		// размер списка

public:
	// вложенные класс исключения
	class Exception 
	{
	private:
		char* msg; 		// сообщение исключения
	public:
		Exception(const char* msg);
		~Exception();
		const char* what();
	};

	// конструктор по умолчанию
	DoublyLinkedList();
	// деструктор
	~DoublyLinkedList();

	// вставить элемент на указанный индекс
	void insert(T data, size_t index);
	// вставить элемент в конец списка
	void add(T data);
	// удалить элемент с указанного индекса
	T remove(size_t index);
	// удалить элемент в начале списка
	T pop();

	// очистить список
	void clear();

	// отобразить список
	void display();
};

templated DoublyLinkedList<T>::Exception::Exception(const char* msg)
{
	size_t len = strlen(msg);
	this->msg = new char[len + 1];

	for (size_t i = 0; i < len; i++)
		this->msg[i] = msg[i];
	this->msg[len] = '\0';
}

templated DoublyLinkedList<T>::Exception::~Exception()
{
	delete[] msg;
}

templated const char* DoublyLinkedList<T>::Exception::what()
{
	return msg;
}

templated DoublyLinkedList<T>::DoublyLinkedList()
{
	head = tail = nullptr;
	size = 0;
}

templated DoublyLinkedList<T>::~DoublyLinkedList()
{
	clear();
}

templated void DoublyLinkedList<T>::insert(T data, size_t index)
{
	// бросить исключение если индекс элемента недоступен
	if (index > size)
		throw Exception("невозможно добавить элемент - индекс вне досягаемости");

	Node* newNode = new Node {}; 
	newNode->data = data;

	if (size == 0)
	{
		newNode->next = newNode->prev = nullptr;
		head = tail = newNode;
		size++;
		return;
	}

	Node* tmp = nullptr;
	
	if (index < (size / 2))
	{
		tmp = tail;
		for (size_t i = 0; i != index; i++)
			tmp = tmp->next;
	}
	else
	{
		tmp = head;
		for (size_t i = size; i != index; i--)
			tmp = tmp->prev;
	}

	Node* tmpNext = tmp->next;

	tmp->next = newNode;
	if (tmpNext != nullptr)
		tmpNext->prev = newNode;

	newNode->next = tmpNext;
	newNode->prev = tmp;

	size++;

	if (tmp == head)
	{
		head = newNode;
		return;
	}
	if (tmp == tail)
	{
		tail = newNode;
		return;
	}
}

templated void DoublyLinkedList<T>::add(T data)
{
	insert(data, size);
}

templated T DoublyLinkedList<T>::remove(size_t index)
{
	// бросить исключение если индекс элемента недоступен
	if (index >= size)
		throw Exception("невозможно удалить элемент - индекс вне досягаемости");

	if (size == 1)
	{
		T buff = head->data;
		delete head;
		tail = head = nullptr;
		size--;
		return buff;
	}

	Node* tmp = nullptr;
	
	if (index < (size / 2))
	{
		tmp = tail;
		for (size_t i = 0; i != index; i++)
			tmp = tmp->next;
	}
	else
	{
		tmp = head;
		for (size_t i = size; i != index; i--)
			tmp = tmp->prev;
	}

	T buff = tmp->data;

	Node* tmpPrev = tmp->prev;
	Node* tmpNext = tmp->next;

	if (tmpPrev != nullptr)
		tmpPrev->next = tmpNext;
	if (tmpNext != nullptr)
		tmpNext->prev = tmpPrev;

	if (tmp == head)
		head = tmp->prev;
	if (tmp == tail)
		tail = tmp->next;

	delete tmp;
	size--;

	return buff;
}

templated T DoublyLinkedList<T>::pop()
{
	return remove(0);
}

templated void DoublyLinkedList<T>::clear()
{
	while (size > 0)
		pop();
}

templated void DoublyLinkedList<T>::display()
{
# 	define parenode(v) '(' << v->data << ')'

	if (size == 0)
	{
		std::cout << "list is empty\n";
		return;
	}

	std::cout << "<tail> ";
	std::cout << parenode(tail);

	Node* tmp = tail->next;
	while (tmp != nullptr)
	{
		std::cout << " <--> " << parenode(tmp);
		tmp = tmp->next;
	}

	std::cout << " <head>\n";
}

void insert(DoublyLinkedList<int>& dll)
{
	int data;
	size_t index;

	std::cout << "Введите значение нового элементв: ";
	std::cin >> data;
	std::cout << "Введите индекс, на котором будет расположен новый элемент: ";
	std::cin >> index;

	dll.insert(data, index);
	std::cout << "\nЭлемент \"" << data 
		<< "\" успешно добавлен на индекс \"" << index << "\"\n";
}

void add(DoublyLinkedList<int>& dll)
{
	int data;

	std::cout << "Введите значение нового элементв: ";
	std::cin >> data;

	dll.add(data);
	std::cout << "\nЭлемент \"" << data 
		<< "\" успешно добавлен в конец списка\n";
}

void remove(DoublyLinkedList<int>& dll)
{
	size_t index;

	std::cout << "Введите индекс элемента, который нужно удалить: ";
	std::cin >> index;

	int data = dll.remove(index);
	std::cout << "Значение удалённого элемента: " << data << '\n';
	std::cout << "Элемент с индексом \"" 
		<< index << "\" успешно удалён\n";
}

void pop(DoublyLinkedList<int>& dll)
{
	int data = dll.pop();
	std::cout << "Значение удалённого элемента: " << data << '\n';
	std::cout <<  "Элемент в начале списка успешно удалён";
}

void display(DoublyLinkedList<int>& dll)
{
	dll.display();
}

void clear(DoublyLinkedList<int>& dll)
{
	dll.clear();
	std::cout << "Список успешно очищен.\n";
}

void test_seq(DoublyLinkedList<int>& dll)
{
// макрос, использующий блок try-catch
# 	define try_action(action, msg) \
		std::cout << '\n' << msg; \
		try \
		{ \
			action; \
			std::cout << " успешно!\n"; \
		} \
		catch (DoublyLinkedList<int>::Exception& ex) \
		{ \
			std::cout << "\nПОЙМАНО ИСКЛЮЧЕНИЕ: " << ex.what() << '\n'; \
		} \
		std::cout << "нажмите Enter для продолжения...\n"; \
		std::cin.get(); \

	// тестовая поседовательность
	try_action(dll.add(1), 
			"попытка добавить элемент \"1\" в конец списка...");
	try_action(dll.add(2), 
			"попытка добавить элемент \"2\" в конец списка...");
	try_action(dll.add(3), 
			"попытка добавить элемент \"3\" в конец списка...");
	try_action(dll.add(4), 
			"попытка добавить элемент \"4\" в конец списка...");
	try_action(dll.display(), 
			"попытка отобразить список...\n");
	try_action(dll.remove(2), 
			"попытка удалить элемент с индекса 2...");
	try_action(dll.remove(15), 
			"попытка удалить элемент с индекса 15...");
	try_action(dll.display(), 
			"попытка отобразить список...\n");
	try_action(dll.insert(128, 1),
			"попытка добавить элемент \"128\" на индекс 1...");
	try_action(dll.insert(67, 41234),
			"попытка добавить элемент \"67\" на индекс 41234...");
	try_action(dll.display(), 
			"попытка отобразить список...\n");
	std::cout << "Тест завершён, работа со списком может быть продолжена вручную.\n";
}

int main()
{
	setlocale(LC_ALL, "rus");

	std::cout << "\tДомашняя Работа №22, Задание №1\n"
		<< "\t\tУченик: Шелест Александр\n\n"
		<< "Добавить в класс двухсвязного списка механизм обработки\n"
		<< "исключений. На своё усмотрение генерировать их при ошибках.\n\n";

	std::cout << "Нажмите Enter для выхода в меню...";
	std::cin.get();
	
	DoublyLinkedList<int> dll;

	int input = -1;

	// основной цикл выполнения
	while (input != 0)
	{
		clrscr();

		std::cout << "============\n";
		std::cout << "||  МЕНЮ  ||\n";
		std::cout << "============\n\n";

		std::cout << "1. Добавить элемент в список\n";
		std::cout << "2. Добавить элемент в конец списка\n";
		std::cout << "3. Удалить элемент из списка\n";
		std::cout << "4. Удалить элемент из начала списка\n";
		std::cout << "5. Отобразить список\n";
		std::cout << "6. Очистить список\n";
		std::cout << "7. Запуск тестовой последовательности выполнения\n"
			<< "\t(рекомендуется)\n\n";
		std::cout << "0. Выход из программы\n\n\n";

		std::cout << "выберите действие по его номеру в списке: ";
		std::cin >> input;

		// блок try-catch
		try
		{
			switch (input)
			{
			case 1:
				insert(dll);
				break;
			case 2:
				add(dll);
				break;
			case 3:
				remove(dll);
				break;
			case 4:
				pop(dll);
				break;
			case 5:
				display(dll);
				break;
			case 6:
				clear(dll);
				break;
			case 7:
				test_seq(dll);
				break;
			case 0:
				return 0;
			default:
				std::cout << "Выбран неверный пункт меню.\n";
			}
		}
		// блок обработки исключений
		catch (DoublyLinkedList<int>::Exception& ex)
		{
			std::cout << "#ПОЙМАНО ИСКЛЮЧЕНИЕ: " << ex.what() << "\n";
		}

		std::cout << "Нажмите Enter для выхода в меню...";
		std::cin.ignore(1, '\0');
		std::cin.get();
	}

	return 0;
}

