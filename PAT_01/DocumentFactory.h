#pragma once

#include "Document.h"


// safe document creation facility
class DocumentFactory
{
private:
	Document* openDocuments;

public:
	DocumentFactory();
	~DocumentFactory();

	Document* createDocument(const char* name);
	Document* getDocument(const char* name);
	
	void closeDocument(const char* name);
};

