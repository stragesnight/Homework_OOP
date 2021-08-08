#pragma once

#include "Document.h"


// class responsible for visual representation of the program
class UserInterface
{
protected:
	static UserInterface* instance;

public:
	UserInterface();
	virtual ~UserInterface();

	static UserInterface* getInstance();

	virtual int draw() = 0;
};

