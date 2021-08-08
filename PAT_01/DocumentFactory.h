#pragma once

#include "Document.h"


// safe document creation facility
class DocumentFactory
{
private:
	Document** openDocuments;
	unsigned nDocs;

	void addDocument(Document* toAdd);
public:
	DocumentFactory();
	~DocumentFactory();

	template <class T> T* createDocument(const char* name);
	template <class T> T* getDocument(const char* name);
	int closeDocument(const char* name);
};

