#pragma once

#include "Document.h"


// class responsible for getting and classifying user input
class UserInputManager
{
private:
	static UserInputManager* instance;

public:
	UserInputManager();

	static UserInputManager* getInstance();

	// handle user input
	int onInput();
};

