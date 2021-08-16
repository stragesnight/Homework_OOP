#include "ImageDocumentFactory.h"
#include "ImageDocument.h"
#include "ImageUserInterface.h"


Document* ImageDocumentFactory::createDocument(const char* name)
{
	ImageDocument* toAdd = new ImageDocument(name, {64, 16});
	addDocument(toAdd);
	return toAdd;
}

