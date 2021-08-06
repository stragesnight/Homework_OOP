#include "SessionManager.h"
#include "UserInputManager.h"
#include "UserInterface.h"


SessionManager* SessionManager::instance = nullptr;

SessionManager::SessionManager()
{
	if (instance != nullptr)
		return;

	instance = this;

	documentFactory = new DocumentFactory();
	selectedDocument = documentFactory->getDocument("new");
}

SessionManager::~SessionManager()
{
	delete documentFactory;
	instance = nullptr;
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
	int exitcode = 0;
	
	while (true)
		update();

	return exitcode;
}

