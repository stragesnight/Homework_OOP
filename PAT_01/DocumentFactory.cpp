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
	newArr[nDocs - 1] = toAdd;

	delete[] openDocuments;

	openDocuments = newArr;
}

Document* DocumentFactory::openDocument(const char* filename, DocumentFileSpec* spec)
{
	Document* opened = DiskIOManager::getInstance()->openDocument(filename, spec);
	if (opened == nullptr)
		return createDocument(filename);
	
	addDocument(opened);

	return opened;
}

Document* DocumentFactory::getDocument(const char* name)
{
	for (unsigned i = 0; i < nDocs; i++)
	{
		if (strcmp(openDocuments[i]->getName(), name) == 0)
			return openDocuments[i];
	}

	return nullptr;
}

Document* DocumentFactory::getDocumentByIndex(unsigned index)
{
	if (index >= nDocs)
		return nullptr;

	return openDocuments[index];
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

