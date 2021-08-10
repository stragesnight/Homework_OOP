#pragma once

#include "../Document.h"
#include "TextDocumentInterfaces.h"
#include <string.h>


class TextDocument : public Document
{
private:
	char* textBuffer;
	unsigned buffSize;
	unsigned textLen;

	void validateBufferSize(unsigned requiredLength);

public:
	TextDocument(const char* name);
	~TextDocument();
	
	const char* getBuffer();
	void setBuffer(const char* textBuffer);
	
	void appendToBuffer(const char* text);
	void appendToBuffer(char c);
	void eraseFromBuffer(unsigned count);
};
