/*
	Паттерны Проектирования, Домашнее Задание №1
		Ученик: Шелест Александр
	
	Спроектировать универсальный каркас многодокументного редактора.
	Предложенный объектно-ориентированный дизайн каркаса должен без изменений 
	использоваться для разработки редакторов для различных видов документов.

	*Диаграмма Классов для этого проекта вложена в архив*
*/

#include "Document.h"
#include "SessionManager.h"
#include "DocumentIO.h"
#include "UserInterface.h"
#include "UserInputManager.h"

#include <stdio.h>

int main()
{
	// create singleton instances
	
	SessionManager sm;
	DiskIOManager diom;
	PrinterIOManager piom;
	//UserInterface ui;
	UserInputManager uim;

	printf("getchar: %c", getchar());
	printf("getc(stdin): %c", getc(stdin));
	
	// start editor session
	return SessionManager::getInstance()->startSession();
}

