/*
 * 	-= Паттерны Проектирования, ДЗ №4 =-
 * 		Ученик: Шелест Александр
 *
 * 	Программа, реализующая модель, которая использует
 * 	один или больше структурный паттерн. 
 * 	(в данном случае это Декоратор (Decorator) и мост (Bridge))
 * 	Данная модель описывает пошаговую ролевую игру, в которой игрок
 * 	собирает предметы, улучшающие его характеристики (декораторы).
 * 	Игра имеет кросс-платформенный интерфейс (мост).
 */

// 	Entity.h
// 	Items.h
// 	GameManager.h
// 	UserInterface.h
//
// 	main.cpp


#include "GameManager.h"


int main()
{
	std::cout << "Wellcome to the arena!\n";
	std::cout << "Are you ready to face your enemy? (1 - yes, 0 - no): ";

	if (getchar() == '1')
	{
		std::cout << "Good luck!!\n";
		GameManager::get_instance()->start_battle();
	}
	else
	{
		std::cout << "Come back later than!\n";
	}

	return 0;
}
