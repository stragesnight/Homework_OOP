#include "TextDocumentFactory.h"
#include "TextDocument.h"


Document* TextDocumentFactory::createDocument(const char* name)
{
	TextDocument* toAdd = new TextDocument(name);
	addDocument(toAdd);
	return toAdd;
}

