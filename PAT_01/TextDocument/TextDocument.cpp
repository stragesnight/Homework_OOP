#include "TextDocument.h"


TextDocument::TextDocument(const char* name)
	: Document(name)
{
	this->fileSpec = new TextDocumentFileSpec(this);
	this->renderer = new TextDocumentRenderer(this);
	this->editor = new TextDocumentEditor(this);

	this->textBuffer = new char[0xFF]{};
	this->buffSize = 0xFF;
	this->textLen = 0;
}

TextDocument::~TextDocument()
{
	delete[] textBuffer;
	buffSize = 0;
	textLen = 0;
}

const char* TextDocument::getBuffer()
{
	return textBuffer;
}

void TextDocument::setBuffer(const char* textBuffer)
{
	unsigned len = strlen(textBuffer);
	unsigned newSize = ((len + 1) / 0xFF) * 0xFF;
	newSize += 0xFF * (newSize == 0);
	
	if (this->textBuffer != nullptr)
		delete[] this->textBuffer;
	this->textBuffer = new char[newSize];
	this->buffSize = newSize;
	this->textLen = len;

	for (unsigned i = 0; i < len; i++)
		this->textBuffer[i] = textBuffer[i];
	this->textBuffer[len] = '\0';
}

void TextDocument::validateBufferSize(unsigned requiredLength)
{
	if (requiredLength >= buffSize)
	{
		char* newBuffer = new char[buffSize + 0xFF] {};

		for (unsigned i = 0; i < this->textLen; i++)
			newBuffer[i] = this->textBuffer[i];

		delete[] this->textBuffer;
		this->textBuffer = newBuffer;
		this->buffSize = buffSize + 0xFF;
	}
}

void TextDocument::appendToBuffer(const char* text)
{
	unsigned textLen = strlen(text);

	validateBufferSize(this->textLen + textLen);

	for (unsigned i = 0; i < textLen; i++)
		this->textBuffer[this->textLen + i] = text[i];
	this->textBuffer[this->textLen + textLen] = '\0'; 
	this->textLen += textLen;
}

void TextDocument::appendToBuffer(char c)
{
	validateBufferSize(textLen + 1);

	textBuffer[textLen] = c;
	textBuffer[textLen + 1] = '\0';
	textLen++;
}

void TextDocument::eraseFromBuffer(unsigned count)
{
	long newLen = (long)textLen - (long)count;
	newLen = (newLen < 0) ? 0 : newLen; 

	for (unsigned i = textLen; i > newLen; i--)
		textBuffer[i] = '\0';

	textLen = newLen;
}

