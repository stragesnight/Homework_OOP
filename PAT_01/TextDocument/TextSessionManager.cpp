#include "TextSessionManager.h"

#include "TextDocument.h"
#include "../UserInputManager.h"
#include "../UserInterface.h"

#include <stdio.h>


TextSessionManager::TextSessionManager() : SessionManager()
{}

TextSessionManager::~TextSessionManager()
{}

int TextSessionManager::update()
{
	int success = 0;
# 	define update_assert(func) \
		success = func; \
		if (!success) return success
	
	UserInputManager::getInstance()->recieveInput();
	char userInput = UserInputManager::getInstance()->lastInput();

	success = processInput(userInput);

	if (success == 0xFFFF)
		return 0xFFFF;

	if (success != 0)
	{
		if (selectedDocument != nullptr)
			update_assert(selectedDocument->getEditor()->editDocument(userInput));
	}
	
	update_assert(UserInterface::getInstance()->draw());

	if (selectedDocument != nullptr)
		update_assert(selectedDocument->getRenderer()->draw());

	return 0;
}

int TextSessionManager::processInput(char input)
{
	switch (input)
	{
	case '|':
		return 0xFFFF;
	default:
		printf("unhandled session input \"%c\"\n", input);
		return 0;
	}

	return 1;
}

int TextSessionManager::startSession()
{
	int exitcode = 0;

	selectedDocument = new TextDocument("new");
	
	while (exitcode == 0)
		exitcode = update();

	return exitcode;
}
