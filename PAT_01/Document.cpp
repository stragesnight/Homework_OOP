#include "Document.h"

#include <string.h>


Document::Document(const char* name)
{
	unsigned len = strlen(name);
	this->name = new char[len + 1];

	for (unsigned i = 0; i < len; i++)
		this->name[i] = name[i];
	this->name[len] = '\0';

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

DocumentFileSpec* Document::getFileSpec() const
{
	return fileSpec;
}

DocumentRenderer* Document::getRenderer() const
{
	return renderer;
}

DocumentEditor* Document::getEditor() const
{
	return editor;
}
