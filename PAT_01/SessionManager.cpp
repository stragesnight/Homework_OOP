#include "SessionManager.h"


SessionManager::SessionManager()
{
	if (instance != nullptr)
		return;

	shouldExit = false;

	documentFactory = nullptr;
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

DocumentFactory* SessionManager::getDocumentFactory()
{
	return documentFactory;
}


void SessionManager::selectDocument(const char* name)
{
	selectedDocument = documentFactory->getDocument(name);
	if (selectedDocument == nullptr)
		selectedDocument = documentFactory->createDocument(name);
}

void SessionManager::stopSession()
{
	shouldExit = true;
}

