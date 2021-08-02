#include "SessionManager.h"
#include "UserInputManager.h"
#include "UserInterface.h"


SessionManager::SessionManager()
{
	if (instance != nullptr)
		return;

	instance = this;

	documentFactory = new DocumentFactory();
	selectedDocument = nullptr;
}

SessionManager::~SessionManager()
{
	instance = nullptr;
	delete documentFactory;
}

int SessionManager::update()
{
	UserInputManager::getInstance()->recieveInput();
	char userInput = UserInputManager::getInstance()->lastInput();
	selectedDocument->getEditor()->editDocument(userInput);

	UserInterface::getInstance()->draw();
	selectedDocument->getRenderer()->draw();

	return 0;
}

int SessionManager::exitSession()
{
	return 0;
}

SessionManager* SessionManager::getInstance()
{
	return instance;
}

Document* SessionManager::getSelectedDocument()
{
	return selectedDocument;
}

int SessionManager::startSession()
{
	// do initialization stuff...
	
	while (true)
		update();

	return exitSession();
}

