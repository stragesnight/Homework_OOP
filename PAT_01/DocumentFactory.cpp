#include "DocumentFactory.h"
#include "DocumentIO.h"
#include <string.h>

DocumentFactory::DocumentFactory()
{
	openDocuments = nullptr;
	nDocs = 0;
}

DocumentFactory::~DocumentFactory()
{
	for (unsigned i = 0; i < nDocs; i++)
		delete openDocuments[i];
	delete[] openDocuments;
}

void DocumentFactory::addDocument(Document* toAdd)
{
	nDocs++;
	Document** newArr = new Document*[nDocs]{};

	for (unsigned i = 0; i < nDocs - 1; i++)
		newArr[i] = openDocuments[i];
	newArr[nDocs] = toAdd;

	if (openDocuments != nullptr)
		delete[] openDocuments;

	openDocuments = newArr;
}

template <class T> T* DocumentFactory::createDocument(const char* name)
{
	try
	{
		T* res = new T(name);
		addDocument(res);
		return res;
	}
	catch (...)
	{
		return nullptr;
	}
}

template <class T> T* DocumentFactory::getDocument(const char* name)
{
	for (unsigned i = 0; i < nDocs; i++)
	{
		if (strcmp(openDocuments[i]->getName(), name) == 0)
			return openDocuments[i];
	}

	return nullptr;
}

int DocumentFactory::closeDocument(const char* name)
{
	for (unsigned i = 0; i < nDocs; i++)
	{
		if (strcmp(openDocuments[i]->getName(), name) == 0)
		{
			delete openDocuments[i];
			nDocs--;
			return 0;
		}
	}
	return 1;
}

