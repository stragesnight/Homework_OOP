#include "TextDocument.h"


TextDocument::TextDocument(const char* name)
	: Document(name)
{
	this->fileSpec = new TextDocumentFileSpec(this);
	this->renderer = new TextDocumentRenderer(this);
	this->editor = new TextDocumentEditor(this);
}

TextDocument::~TextDocument()
{
	delete[] textBuffer;
}

const char* TextDocument::getBuffer()
{
	return textBuffer;
}

void TextDocument::setBuffer(const char* textBuffer)
{
	unsigned len = strlen(textBuffer);

	delete[] this->textBuffer;
	this->textBuffer = new char[len + 1];

	for (unsigned i = 0; i < len; i++)
		this->textBuffer[i] = textBuffer[i];
	this->textBuffer[len] = '\0';
}

