#include "ImageDocumentInterfaces.h"

#include "ImageUserInterface.h"
#include "../UserInputManager.h"
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
	for (; len > 0; len--, dst++, src++)
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

	ImageDocument* pParent = ((ImageDocument*)parent);
	unsigned bufflen = 0;

	const char magic[] = "<IMAGEDOCUMENT>\n";
	bufflen = appendToBuffer(buffer, 0, magic, strlen(magic));

	const uvec2d& imageSize = pParent->getSize();
	bufflen = appendToBuffer(buffer, bufflen, (const char*)&imageSize, sizeof(uvec2d));

	const char* cellBuffer = (const char*)pParent->getCells();
	unsigned cellBufferLength = sizeof(ImageDocument::Cell) * imageSize.x * imageSize.y;
	bufflen = appendToBuffer(buffer, bufflen, cellBuffer, cellBufferLength);

	return bufflen;
}

Document* ImageDocumentFileSpec::parseData(const char* buffer)
{
	if (!isValid(buffer))
	{
		printf("INVALID FILE TYPE!\n");
		return nullptr;
	}

	buffer++;

	ImageDocument* pParent = ((ImageDocument*)parent);

	uvec2d size = { 0, 0 };
	char* pSize = (char*)&size;
	copyBuffer(pSize, buffer, sizeof(size));
	pParent->setSize(size);

	buffer++;

	ImageDocument::Cell* cellBuffer = new ImageDocument::Cell[size.x * size.y + 1];
	char* pCellBuffer = (char*)cellBuffer;
	copyBuffer(pCellBuffer, buffer, sizeof(ImageDocument::Cell) * size.x * size.y);
	pParent->setCells(cellBuffer);

	return parent;
}


int ImageDocumentRenderer::draw()
{
	const char* buff = (const char*)((ImageDocument*)parent)->getCells();
	ImageUserInterface* tui = ((ImageUserInterface*)ImageUserInterface::getInstance());

	//tui->enqueueData(TUIElement::cellBuffer, buff);

	return 0;
}

void changeBGColor(ImageDocument* pParent, const uvec2d& drawingHeadPos, char input)
{
	switch (input)
	{
	case '1': pParent->setBGColor(drawingHeadPos, c_color::black);
		break;
	case '2': pParent->setBGColor(drawingHeadPos, c_color::red);
		break;
	case '3': pParent->setBGColor(drawingHeadPos, c_color::green);
		break;
	case '4': pParent->setBGColor(drawingHeadPos, c_color::yellow);
		break;
	case '5': pParent->setBGColor(drawingHeadPos, c_color::blue);
		break;
	case '6': pParent->setBGColor(drawingHeadPos, c_color::purple);
		break;
	case '7': pParent->setBGColor(drawingHeadPos, c_color::cyan);
		break;
	case '8': pParent->setBGColor(drawingHeadPos, c_color::white);
		break;
	case '!': pParent->setBGColor(drawingHeadPos, c_color::b_black);
		break;
	case '@': pParent->setBGColor(drawingHeadPos, c_color::b_red);
		break;
	case '#': pParent->setBGColor(drawingHeadPos, c_color::b_green);
		break;
	case '$': pParent->setBGColor(drawingHeadPos, c_color::b_yellow);
		break;
	case '%': pParent->setBGColor(drawingHeadPos, c_color::b_blue);
		break;
	case '^': pParent->setBGColor(drawingHeadPos, c_color::b_purple);
		break;
	case '&': pParent->setBGColor(drawingHeadPos, c_color::b_cyan);
		break;
	case '*': pParent->setBGColor(drawingHeadPos, c_color::b_white);
		break;
	default:
		break;
	}
}

void changeFGColor(ImageDocument* pParent, const uvec2d& drawingHeadPos, char input)
{
	switch (input)
	{
	case '1': pParent->setFGColor(drawingHeadPos, c_color::black);
		break;
	case '2': pParent->setFGColor(drawingHeadPos, c_color::red);
		break;
	case '3': pParent->setFGColor(drawingHeadPos, c_color::green);
		break;
	case '4': pParent->setFGColor(drawingHeadPos, c_color::yellow);
		break;
	case '5': pParent->setFGColor(drawingHeadPos, c_color::blue);
		break;
	case '6': pParent->setFGColor(drawingHeadPos, c_color::purple);
		break;
	case '7': pParent->setFGColor(drawingHeadPos, c_color::cyan);
		break;
	case '8': pParent->setFGColor(drawingHeadPos, c_color::white);
		break;
	case '!': pParent->setFGColor(drawingHeadPos, c_color::b_black);
		break;
	case '@': pParent->setFGColor(drawingHeadPos, c_color::b_red);
		break;
	case '#': pParent->setFGColor(drawingHeadPos, c_color::b_green);
		break;
	case '$': pParent->setFGColor(drawingHeadPos, c_color::b_yellow);
		break;
	case '%': pParent->setFGColor(drawingHeadPos, c_color::b_blue);
		break;
	case '^': pParent->setFGColor(drawingHeadPos, c_color::b_purple);
		break;
	case '&': pParent->setFGColor(drawingHeadPos, c_color::b_cyan);
		break;
	case '*': pParent->setFGColor(drawingHeadPos, c_color::b_white);
		break;
	default:
		break;
	}
}

int ImageDocumentEditor::editDocument(char input)
{
	ImageUserInterface* iui = (ImageUserInterface*)ImageUserInterface::getInstance();
	UserInputManager* uim = UserInputManager::getInstance();
	ImageDocument* pParent = (ImageDocument*)parent;
	const uvec2d imageSize = pParent->getSize();

	switch (input)
	{
	// navigation
	case 's': case 'j':
		if (drawingHeadPos.y < imageSize.y - 1)
			drawingHeadPos.y++;
		break;
	case 'w': case 'k':
		if (drawingHeadPos.y > 1)
			drawingHeadPos.y--;
		break;
	case 'd': case 'l':
		if (drawingHeadPos.x < imageSize.x - 1)
			drawingHeadPos.x++;
		break;
	case 'a': case 'h':
		if (drawingHeadPos.x > 0)
			drawingHeadPos.x--;
		break;
	// change character
	case 'c':
	{
		uim->recieveInput();
		pParent->setChar(drawingHeadPos, uim->lastInput()); 
		iui->enqueueData(TUIElement::cellBuffer, (const char*)pParent->getCells());
		break;
	}
	// change background color
	case 'b':
		uim->recieveInput();
		changeBGColor(pParent, drawingHeadPos, uim->lastInput());
		iui->enqueueData(TUIElement::cellBuffer, (const char*)pParent->getCells());
		break;
	// change foreground color
	case 'f':
		uim->recieveInput();
		changeFGColor(pParent, drawingHeadPos, uim->lastInput());
		iui->enqueueData(TUIElement::cellBuffer, (const char*)pParent->getCells());
		break;
	default:
		char buff[256]{};
		snprintf(buff, 256, "unhandled input \'%c\'", input);
		iui->enqueueData(TUIElement::statusLine, buff);
		break;
	}

	iui->moveDrawingHead(drawingHeadPos);

	return 0;
}

