#pragma once

#include "../Document.h"
#include "TextDocumentInterfaces.h"
#include <string.h>


class TextDocument : public Document
{
private:
	char* textBuffer;
public:
	TextDocument(const char* name);
	~TextDocument();
	const char* getBuffer();
	void setBuffer(const char* textBuffer);
};
