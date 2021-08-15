#include "ImageDocumentFactory.h"
#include "ImageDocument.h"
#include "ImageUserInterface.h"


Document* ImageDocumentFactory::createDocument(const char* name)
{
	ImageUserInterface* iui = (ImageUserInterface*)ImageUserInterface::getInstance();
	ImageDocument* toAdd = new ImageDocument(name, iui->getCanvasSize());

	addDocument(toAdd);

	return toAdd;
}

