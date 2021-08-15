#include "UserInputManager.h"
#if defined (_WIN32) or defined (_WIN64)
# include <conio.h>
#else
# include <termio.h>
# include <stdio.h>
#endif


UserInputManager* UserInputManager::instance = nullptr;

UserInputManager::UserInputManager()
{
	if (instance == nullptr)
		instance = this;
	lastRecievedInput = 0;

# 	if !defined (_WIN32) && !defined (_WIN64)
	termios tios;
	tcgetattr(0, &tios);
	tios.c_lflag &= ~ICANON;
	tios.c_lflag &= ~ECHO;
	tcsetattr(0, TCSANOW, &tios);
# 	endif
}

UserInputManager::~UserInputManager()
{
# 	if !defined (_WIN32) && !defined (_WIN64)
	termios tios;
	tcgetattr(0, &tios);
	tios.c_lflag |= ICANON;
	tios.c_lflag |= ECHO;
	tcsetattr(0, TCSANOW, &tios);
# 	endif
}

UserInputManager* UserInputManager::getInstance()
{
	return instance;
}

int UserInputManager::recieveInput()
{

#if defined (_WIN32) or defined (_WIN64)
	lastRecievedInput = _getch();
#else
	lastRecievedInput = getchar();
#endif
	return 0;
}

char UserInputManager::lastInput()
{
	return lastRecievedInput;
}

