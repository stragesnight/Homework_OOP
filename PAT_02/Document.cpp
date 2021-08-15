#include "Document.h"

#include <string.h>


Document::Document(const char* name)
{
	this->name = nullptr;

	setName(name);
	
	this->fileSpec = nullptr;
	this->renderer = nullptr;
	this->editor = nullptr;
}

Document::~Document()
{
	delete[] name;
	delete fileSpec;
	delete renderer;
	delete editor;
}

const char* Document::getName()
{
	return name;
}

DocumentFileSpec* Document::getFileSpec() 
{
	return fileSpec;
}

DocumentRenderer* Document::getRenderer() 
{
	return renderer;
}

DocumentEditor* Document::getEditor() 
{
	return editor;
}

void Document::setName(const char* name)
{
	if (this->name != nullptr)
		delete[] this->name;

	unsigned len = strlen(name);
	this->name = new char[len + 1];

	for (unsigned i = 0; i < len; i++)
		this->name[i] = name[i];
	this->name[len] = '\0';
}

