#include "TextDocumentInterfaces.h"


void TextDocumentFileSpec::appendToBuffer(char*& dst, const char* src)
{
	unsigned dstlen = strlen(dst);
	unsigned srclen = strlen(src);
	char* res = new char[dstlen + srclen + 1]{};

	for (unsigned i = 0; i < dstlen; i++)
		res[i] = dst[i];

	for (unsigned i = 0; i < srclen; i++)
		res[dstlen + i] = src[i];

	res[dstlen + srclen] = '\0';

	delete[] dst;
	dst = res;
}

bool TextDocumentFileSpec::isValid(const char*& buffer)
{
	const char* magic = "<TEXTDOCUMENT>\n";

	while (*magic != '\0')
	{
		if (*buffer != *magic)
			return false;
		buffer++;
		magic++;
	}

	return true;
}

unsigned TextDocumentFileSpec::getSaveData(char*& buffer)
{
	if (buffer != nullptr)
		delete[] buffer;
	
	const char* input_buff = ((TextDocument*)parent)->getBuffer();
	appendToBuffer(buffer, "<TEXTDOCUMENT>\n");
	appendToBuffer(buffer, input_buff);

	return strlen(buffer);
}

Document* TextDocumentFileSpec::parseData(const char* buffer)
{
	if (!isValid(buffer))
	{
		std::cout << "INVALID FLIE TYPE!\n";
		return nullptr;
	}

	((TextDocument*)parent)->setBuffer(buffer);

	return parent;
}


int TextDocumentRenderer::draw()
{
	std::cout << ((TextDocument*)parent)->getBuffer();
	return 0;
}


int TextDocumentEditor::editDocument(char input)
{
	switch (input)
	{
	default:
		std::cout << "unimplemented input callback \"" << input << "\"\n";
	}

	return 0;
}

