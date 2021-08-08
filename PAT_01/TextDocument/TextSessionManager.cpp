#include "TextSessionManager.h"

#include "../UserInputManager.h"
#include "../UserInterface.h"


TextSessionManager::TextSessionManager() : SessionManager()
{

}

TextSessionManager::~TextSessionManager()
{
	SessionManager::~SessionManager();
}

int TextSessionManager::update()
{
	int success = 0;
# 	define update_assert(func) \
		success = func; \
		if (!success) return success
	
	UserInputManager::getInstance()->recieveInput();
	char userInput = UserInputManager::getInstance()->lastInput();

	if (processInput(userInput) == 0)
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
	default:
		return 1;
	}

	return 0;
}

int TextSessionManager::startSession()
{
	int exitcode = 0;
	
	while (exitcode == 0)
		exitcode = update();

	return exitcode;
}
