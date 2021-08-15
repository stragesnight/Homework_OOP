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

#include "ImageDocument/ImageUserInterface.h"
#include "ImageDocument/ImageSessionManager.h"

int main()
{
	// create singleton instances
	
	ImageUserInterface iui;
	DiskIOManager diom;
	PrinterIOManager piom;
	UserInputManager uim;
	ImageSessionManager tsm;

	// start editor session
	return SessionManager::getInstance()->startSession();
}

