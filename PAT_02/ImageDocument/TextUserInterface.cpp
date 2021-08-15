#include "TextUserInterface.h"

#if defined (_WIN32) or defined (_WIN64)
# include <Windows.h>
#else
# include <sys/ioctl.h>
# include <unistd.h>
#endif

#include <string.h>
#include <cmath>
#include <stdio.h>


TextUserInterface::TextUserInterface()
{
#if defined (_WIN32) or defined (_WIN64)
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	screenWidth = csbi.dwSize.X;
	screenHeight = csbi.dwSize.Y;
#else
	winsize size;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
	screenWidth = size.ws_col;
	screenHeight = size.ws_row;
#endif

	queueFlags = 0;
	
	/*
		-----------------------------
		| 							|
		|  		  textBuffer		|
		| 			 				|
		|---------------------------|
		|  		  commandLine  		|
		|---------------------------|
		|  		  statusLine    	|
		-----------------------------
	*/

	textBufferElement.flag = TUIElement::textBuffer;
	textBufferElement.bounds.ul = { 5, 3 };
	textBufferElement.bounds.lr = { screenWidth - 5, screenHeight - 8 };
	textBufferElement.data = nullptr;
	UIElements[0] = &textBufferElement;

	commandLineElement.flag = TUIElement::commandLine;
	commandLineElement.bounds.ul = { 5, screenHeight - 3 };
	commandLineElement.bounds.lr = { screenWidth - 5, screenHeight - 3 };
	commandLineElement.data = nullptr;
	UIElements[1] = &commandLineElement;

	statusLineElement.flag = TUIElement::statusLine;
	statusLineElement.bounds.ul = { 5, screenHeight - 1 };
	statusLineElement.bounds.lr = { screenWidth - 5, screenHeight - 1 };
	statusLineElement.data = nullptr;
	UIElements[2] = &statusLineElement;

	clearScreen();
}

void TextUserInterface::moveCursor(const vec2d& pos)
{
#if defined (_WIN32) or defined (_WIN64)
	COORD coord = {(short)pos.x, (short)pos.y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
#else
	printf("\033[%d;%df", pos.y, pos.x);
#endif
}

int TextUserInterface::draw()
{
	for (int i = 0; i < 3; i++)
	{
		element* curr = UIElements[i];

		if (isEnqueued(curr->flag))
		{
#if defined (_WIN32) or defined (_WIN64)
			if (curr->flag != TUIElement::textBuffer)
#endif
			drawBox(curr->bounds, ' ', ' ');
			drawText(curr->data, curr->bounds);
		}
	}

	queueFlags = 0;

	return 0;
}

void TextUserInterface::clearScreen()
{
#if defined (_WIN32) or defined (_WIN64)
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	screenWidth = csbi.dwSize.X;
	screenHeight = csbi.dwSize.Y;
	system("cls");
	drawLine({ 0, screenHeight - 2 }, { screenWidth, screenHeight - 2 }, '#');
	drawLine({ 0, screenHeight - 4 }, { screenWidth, screenHeight - 4 }, '#');
	drawLine({ 0, 0 }, { screenWidth, 0 }, '#');
#else
	winsize size;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
	screenWidth = size.ws_col;
	screenHeight = size.ws_row;
	printf("\033[2J");
	drawBox({ {0, 0}, {screenWidth, screenHeight} }, ' ', '#');
	drawLine({ 1, screenHeight - 4 }, { screenWidth, screenHeight - 4 }, '#');
	drawLine({ 1, screenHeight - 2 }, { screenWidth, screenHeight - 2 }, '#');
#endif
}

void TextUserInterface::drawLine(const vec2d& from, const vec2d& to, char body)
{
	if (from.y != to.y)
		return;

	moveCursor(from);

	for (unsigned x = from.x; x < to.x; x++)
		putchar(body);
}

void TextUserInterface::drawPipe(const vec2d& from, const vec2d& to, char body)
{
	if (from.x != to.x)
		return;

	for (unsigned y = from.y; y < to.y; y++)
	{
		moveCursor({from.x, y});
		putchar(body);
	}
}

void TextUserInterface::drawBox(const rect& box, char body, char border)
{
	for (unsigned y = box.ul.y; y < box.lr.y; y++)
		drawLine({box.ul.x, y}, {box.lr.x, y}, body);
	drawLine({box.ul.x, box.lr.y}, box.lr, border);
	drawLine(box.ul, {box.lr.x, box.ul.y}, border);

	drawPipe(box.ul, {box.ul.x, box.lr.y}, border);
	drawPipe({box.lr.x, box.ul.y}, box.lr, border);
}

void TextUserInterface::drawText(const char* text, const rect& boundary)
{
	vec2d cursorPos = {boundary.ul.x, boundary.ul.y};
	moveCursor(cursorPos);

	unsigned textLen = strlen(text);

	for (unsigned i = 0; i < textLen; i++)
	{
		if (text[i] == 13 || text[i] == '\n' || cursorPos.x >= boundary.lr.x)
		{
			cursorPos.x = boundary.ul.x;
			cursorPos.y++;

			if (cursorPos.y >= boundary.lr.y)
				return;

			moveCursor(cursorPos);
			continue;
		}

		putchar(text[i]);

		cursorPos.x++;
	}
}

void TextUserInterface::enqueueData(TUIElement flag, const char* data)
{
	for (int i = 0; i < 3; i++)
	{
		if (UIElements[i]->flag == flag)
		{
			queueFlags |= (unsigned char)flag;
			UIElements[i]->data = data;
		}
	}
}

bool TextUserInterface::isEnqueued(TUIElement flag)
{
	return (queueFlags & (unsigned char)flag) == (unsigned char)flag;
}

void TextUserInterface::startCommand()
{
	drawBox(commandLineElement.bounds, ' ', ' ');
	drawText("command -> /", commandLineElement.bounds);
}

