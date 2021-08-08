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

	// update loop, called every frame
	virtual int update() = 0;
	virtual int processInput(char input) = 0;

public:
	SessionManager();
	virtual ~SessionManager();

	static SessionManager* getInstance();
	Document* getSelectedDocument();

	// start session update loop
	virtual int startSession() = 0;
};

