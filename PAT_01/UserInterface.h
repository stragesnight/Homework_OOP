#pragma once

#include "Document.h"


// class responsible for visual representation of the program
class UserInterface
{
private:
	static UserInterface* instance;

public:
	UserInterface();

	static UserInterface* getInstance();

	int draw();
};

