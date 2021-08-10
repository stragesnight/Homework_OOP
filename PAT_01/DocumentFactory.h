#pragma once

#include "Document.h"


// safe document creation facility
class DocumentFactory
{
protected:
	Document** openDocuments;
	unsigned nDocs;

	void addDocument(Document* toAdd);
public:
	DocumentFactory();
	virtual ~DocumentFactory();

	virtual Document* createDocument(const char* name) = 0;
	Document* openDocument(const char* filename, DocumentFileSpec* spec);
	Document* getDocument(const char* name);
	Document* getDocumentByIndex(unsigned index);
	int closeDocument(const char* name);
};

