#include "UserInputManager.h"
#include <stdio.h>

UserInputManager* UserInputManager::instance = nullptr;

UserInputManager::UserInputManager()
{
	if (instance == nullptr)
		instance = this;
	lastObtainedInput = 0;
}

UserInputManager* UserInputManager::getInstance()
{
	return instance;
}

int UserInputManager::recieveInput()
{
	lastObtainedInput = getchar();
	getc(stdin);
	return 0;
}

char UserInputManager::lastInput()
{
	return lastObtainedInput;
}

