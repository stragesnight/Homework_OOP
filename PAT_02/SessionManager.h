#pragma once

#include "Document.h"
#include "DocumentFactory.h"


// document editor sesion manager
// responsible for tying together program modules
// and managing logic
class SessionManager
{
protected:
	static SessionManager* instance;
	DocumentFactory* documentFactory;
	Document* selectedDocument;

	bool shouldExit;

	virtual int update() = 0;
	virtual int processInput(char input) = 0;
	virtual int processCommand() = 0;

public:
	SessionManager();
	virtual ~SessionManager();

	static SessionManager* getInstance();
	Document* getSelectedDocument();
	DocumentFactory* getDocumentFactory();

	virtual void selectDocument(const char* name);
	virtual void selectDocumentByIndex(unsigned index);

	virtual int startSession() = 0;
	virtual void stopSession();
};

