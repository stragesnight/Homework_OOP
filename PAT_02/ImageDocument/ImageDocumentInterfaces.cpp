#include "ImageDocumentInterfaces.h"

#include "ImageUserInterface.h"
#include <string.h>
#include <stdio.h>


unsigned ImageDocumentFileSpec::appendToBuffer(char*& dst, unsigned dstlen,
										   const char* src, unsigned srclen)
{
	char* res = new char[dstlen + srclen + 1]{};

	for (unsigned i = 0; i < dstlen; i++)
		res[i] = dst[i];

	for (unsigned i = 0; i < srclen; i++)
		res[dstlen + i] = src[i];

	res[dstlen + srclen] = '\0';

	delete[] dst;
	dst = res;

	return dstlen + srclen + 1;
}

void ImageDocumentFileSpec::copyBuffer(char*& dst, const char*& src, unsigned len)
{
	for (; len >= 0; len--, dst++, src++)
		*dst = *src;
}

bool ImageDocumentFileSpec::isValid(const char*& buffer)
{
	const char* magic = "<IMAGEDOCUMENT>\n";

	while (*buffer != '<' && *buffer != '\0')
		buffer++;

	while (*magic != '\0')
	{
		if (*buffer != *magic)
			return false;
		buffer++;
		magic++;
	}

	return true;
}

unsigned ImageDocumentFileSpec::getSaveData(char*& buffer)
{
	if (buffer != nullptr)
		delete[] buffer;

	ImageDocument* parent = ((ImageDocument*)parent);
	unsigned bufflen = 0;

	const char magic[] = "<IMAGEDOCUMENT>\n";
	bufflen = appendToBuffer(buffer, 0, magic, strlen(magic));

	const uvec2d& imageSize = parent->getSize();
	bufflen = appendToBuffer(buffer, bufflen, (const char*)&imageSize, sizeof(uvec2d));

	const char* cellBuffer = (const char*)parent->getCells();
	if (cellBuffer == nullptr)
		return bufflen;
	unsigned cellBufferLength = sizeof(ImageDocument::Cell) * imageSize.x * imageSize.y;
	appendToBuffer(buffer, bufflen, cellBuffer, cellBufferLength);

	return bufflen;
}

Document* ImageDocumentFileSpec::parseData(const char* buffer)
{
	if (!isValid(buffer))
	{
		printf("INVALID FILE TYPE!\n");
		return nullptr;
	}

	ImageDocument* parent = ((ImageDocument*)parent);

	uvec2d size = {};
	char* pSize = (char*)&size;
	copyBuffer(pSize, buffer, sizeof(uvec2d));
	parent->setSize(size);

	ImageDocument::Cell* cellBuffer = new ImageDocument::Cell[size.x * size.y + 1];
	char* pCellBuffer = (char*)cellBuffer;
	copyBuffer(pCellBuffer, buffer, size.x * size.y);
	parent->setCells(cellBuffer);

	return parent;
}


int ImageDocumentRenderer::draw()
{
	const char* buff = (const char*)((ImageDocument*)parent)->getCells();
	ImageUserInterface* tui = ((ImageUserInterface*)ImageUserInterface::getInstance());

	tui->enqueueData(TUIElement::cellBuffer, buff);

	return 0;
}


int ImageDocumentEditor::editDocument(char input)
{
	switch (input)
	{
	default:
		char buff[128]{};
		snprintf(buff, 128, "unhandled input \'%c\'", input);
		((ImageUserInterface*)ImageUserInterface::getInstance())
			->enqueueData(TUIElement::statusLine, buff);
		break;
	}

	return 0;
}

