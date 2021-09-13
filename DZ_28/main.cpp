/*
 * 	-= Домашнее Задание №28 =-
 * 		Ученик: Шелест Александр
 *
 * 	Создать пользовательские классы для умных указателей,
 * 	повторив поведение unique_ptr и shared_ptr.
 */

// закомментируйте эту сттроку для использования умных указателей 
// из стандартной библиотеки
#define MY_SMARTPR_IMPL

#include <iostream>
#include <clocale>

#ifndef MY_SMARTPR_IMPL
# 	include <memory>
	using std::shared_ptr;
	using std::unique_ptr;
#else

// класс, содержащий общие поля и методы для все классов умных указателей
template <class T>
class smartptr_common
{
protected:
	T* ptr; 	// указатель на непосредственно данные

public:
	// логические операторы
	explicit operator bool() const { return ptr != nullptr; }
	bool operator==(const void* ptr) const { return this->ptr == ptr; }
	bool operator==(std::nullptr_t) const { return this->ptr == nullptr; }
	bool operator!=(const void* ptr) const { return this->ptr != ptr; }
	bool operator!=(std::nullptr_t) const { return this->ptr != nullptr; }
	// запретить присваивать объектам значения через опертор =
	template <class arg> void operator=(const arg& other) = delete;
	// опертор разыменования
	T& operator*() const { return *ptr; }

	// удалить старый указатель и заменить его новым
	void reset(T* ptr)
	{
		T* old_ptr = this->ptr;
		this->ptr = ptr;

		if (old_ptr != nullptr)
			delete old_ptr;
	}

	// освободить внутреннее поле и возвратить его содержание
	T* release()
	{
		T* tmp = ptr;
		this->ptr = nullptr;

		return tmp;
	}

	// получить внутренний указатель
	T* get() const { return ptr; }
};

// класс умного указателя, для которого может быть только 
// один уникальный объект-владелец, все попытки копирования отсекаются.
template <class T>
class unique_ptr : public smartptr_common<T>
{
public:
	// конструктор с параметром
	explicit unique_ptr(T* ptr = nullptr)
	{
		this->ptr = ptr;
	}
	// запретить копирование через конструктор
	unique_ptr(const unique_ptr& other) = delete;

	// деструктор попросту освобождает указатель
	~unique_ptr()
	{
		delete this->ptr;
	}

	// поменять указатели местами
	void swap(unique_ptr& other)
	{
		T* tmp = this->ptr;
		this->ptr = other.ptr;
		other.ptr = tmp;
	}
};

// класс умного указателя, для которого может быть какое угодно число владельцев.
// при этом хранится количество его владельцев для контроля ситуации.
template <class T>
class shared_ptr : public smartptr_common<T>
{
private:
	size_t* refcount; 	// количество владельцев указателя

public:
	// конструктор
	shared_ptr(T* ptr = nullptr)
	{
		this->ptr = ptr;
		refcount = new size_t(ptr != nullptr);
	}

	// если параметром выступает другой такой же указатель, 
	// количество владельцев инкрементируется
	shared_ptr(shared_ptr& other)
	{
		(*other.refcount)++;
		this->refcount = other.refcount;
		this->ptr = other.ptr;
	}

	// деструктор
	// проверяет количество владельцев указателя
	// освобождает память только если остался только один владелец
	~shared_ptr()
	{
		if (*refcount == 1)
		{
			delete refcount;
			delete this->ptr;
			return;
		}

		(*refcount)--;
	}

	// поменять указатели местами
	void swap(shared_ptr& other)
	{
		T* tmp = this->ptr;
		this->ptr = other.ptr;
		other.ptr = tmp;
	}

	// возвращает истину, если у указателя только один владелец
	bool unique() const { return *refcount == 1; }
	// возвращает количество владельцев указателя
	size_t use_count() const { return *refcount; }
};
#endif


// вывод информации об уникальном указателе на экран
template <class T>
void printptr(const unique_ptr<T>& up)
{
	if (up == nullptr)
		std::cout << "нулевой указатель!\n\n";
	else
	{
		std::cout << "значение указателя на \"" 
			<< up.get() << "\" равно \"" << *up << "\"\n";
	}
}

// вывод информации об общем указателе на экран
template <class T>
void printptr(const shared_ptr<T>& sp)
{
	if (sp == nullptr)
		std::cout << "нулевой указатель!\n\n";
	else
	{
		std::cout << "значение указателя на \"" 
			<< sp.get() << "\" равно \"" << *sp << "\"\n";
		std::cout << "количество владельцев для данного указателя: " 
			<< sp.use_count() << '\n';
		std::cout << "уникален ли указатель? - ";
		if (sp.unique())
			std::cout << "да\n";
		else
			std::cout << "нет\n";
	}
}


int main()
{
# 	define pause_exec() \
	std::cout << "\nнажмите Enter для продолжения..."; \
	std::cin.get();

	setlocale(LC_ALL, "rus");

	std::cout << "\t-= Домашнее Задание №28 =-\n"
 		<< "\t\tУченик: Шелест Александр\n\n"
 		<< "Создать пользовательские классы для умных указателей,\n"
 		<< "повторив поведение unique_ptr и shared_ptr.\n\n";


	// unique_ptr
	
	std::cout << "=== UNIQUE_PTR ===\n\n";
	std::cout << "создание нового объекта unique_ptr с именем up1:\n";
	unique_ptr<int> up1(new int(8));
	printptr(up1);
	pause_exec();
	
	std::cout << "\nсоздание нового объекта unique_ptr с именем up2:\n";
	// unique_ptr<int> up2(up1);  <- ошибка!
	unique_ptr<int> up2(new int(9));
	printptr(up2);
	pause_exec();

	std::cout << "\nуказатели меняются местами...\n";
	// up2 = up1;  <- ошибка!
	up1.swap(up2);
	std::cout << "up1: ";
	printptr(up1);
	std::cout << "up2: ";
	printptr(up2);
	pause_exec();

	std::cout << "\nосвобождение указателя up1...\n";
	up1.reset(nullptr);
	std::cout << "up1: ";
	printptr(up1);
	pause_exec();

	// shared_ptr
	
	std::cout << "\n=== SHARED_PTR ===\n\n";
	std::cout << "создание нового объекта shared_ptr с именем sp1:\n";
	shared_ptr<int> sp1(new int(16));
	printptr(sp1);
	pause_exec();

	{
		std::cout << "\nсоздание нового объекта shared_ptr с именем sp2,\n"
			<< "\tкоторый наследует указатель sp1:\n";
		shared_ptr<int> sp2(sp1);

		printptr(sp2);
		pause_exec();

		std::cout << "\nизменение значения указателя sp1...\n\n";
		*sp1 = 5;

		std::cout << "sp1: ";
		printptr(sp1);
		pause_exec();

		{
			std::cout << "\nсоздание нового объекта shared_ptr с именем sp3,\n"
				<< "\tкоторый наследует указатель sp2:\n";
			shared_ptr<int> sp3 = sp2;
			printptr(sp3);
			pause_exec();

			std::cout << "\nудаление объекта sp3...\n";
		}

		std::cout << "удаление объекта sp2...\n\n";
	}

	std::cout << "sp1: ";
	printptr(sp1);
	pause_exec();

	std::cout << "\nосвобождение указателя sp1...\n";
	sp1.reset(nullptr);
	printptr(sp1);

	std::cout << "\nТест завершён. Нажмите Enter для выхода...";
	std::cin.get();
	return 0;
}

