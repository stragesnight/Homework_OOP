#include "DocumentFactory.h"

DocumentFactory::DocumentFactory()
{
	openDocuments = new Document*[1] {
		new Document("new")
	};
}

DocumentFactory::~DocumentFactory()
{
	delete[] openDocuments;
}

Document* DocumentFactory::createDocument(const char* name)
{
	return nullptr;
}

Document* DocumentFactory::openDocument(const char* name)
{
	return nullptr;
}

Document* DocumentFactory::getDocument(const char* name)
{
	return nullptr;
}

int DocumentFactory::closeDocument(const char* name)
{
	return 0;
}

