#pragma once

#include "Document.h"


// class responsible for getting and classifying user input
class UserInputManager
{
private:
	static UserInputManager* instance;
	char lastRecievedInput;

public:
	UserInputManager();
	~UserInputManager();

	static UserInputManager* getInstance();

	// handle user input
	int recieveInput();

	// get last recieved user input
	char lastInput();
};

