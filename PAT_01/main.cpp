/*
	Паттерны Проектирования, Домашнее Задание №1
		Ученик: Шелест Александр
	
	Спроектировать универсальный каркас многодокументного редактора.
	Предложенный объектно-ориентированный дизайн каркаса должен без изменений 
	использоваться для разработки редакторов для различных видов документов.

	*Диаграмма Классов для этого проекта вложена в архив*
*/

#include "Document.h"
#include "DocumentIO.h"
#include "UserInputManager.h"

#include "TextDocument/TextUserInterface.h"
#include "TextDocument/TextSessionManager.h"

int main()
{
	// create singleton instances
	
	TextSessionManager tsm;
	DiskIOManager diom;
	PrinterIOManager piom;
	TextUserInterface tui;
	UserInputManager uim;

	// start editor session
	return SessionManager::getInstance()->startSession();
}

