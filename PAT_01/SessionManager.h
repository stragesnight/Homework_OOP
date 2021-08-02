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
	virtual int update();
	// close all documents and stop program
	int exitSession();

public:
	SessionManager();
	~SessionManager();

	static SessionManager* getInstance();
	Document* getSelectedDocument();

	// start session update loop
	virtual int startSession();
};

