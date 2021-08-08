#include "SessionManager.h"


SessionManager* SessionManager::instance = nullptr;

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
	delete documentFactory;
	instance = nullptr;
}

SessionManager* SessionManager::getInstance()
{
	return instance;
}

Document* SessionManager::getSelectedDocument()
{
	return selectedDocument;
}

