#include "ImageUserInterface.h"

#if defined (_WIN32) or defined (_WIN64)
# include <Windows.h>
#else
# include <sys/ioctl.h>
# include <unistd.h>
#endif

#include <string.h>
#include <cmath>
#include <stdio.h>


ImageUserInterface::ImageUserInterface()
{
#if defined (_WIN32) or defined (_WIN64)
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	screenSize.x = csbi.dwSize.X;
	screenSize.y = csbi.dwSize.Y;
#else
	winsize size;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
	screenSize.x = size.ws_col;
	screenSize.y = size.ws_row;
#endif
	queueFlags = 0;
	imageSize = { 0, 0 };

	clearScreen();
}

void ImageUserInterface::moveCursor(const uvec2d& pos)
{
#if defined (_WIN32) or defined (_WIN64)
	COORD coord = { (short)pos.x, (short)pos.y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
#else
	printf("\033[%d;%df", pos.y, pos.x);
#endif
}

void ImageUserInterface::moveDrawingHead(const uvec2d& pos)
{
	uvec2d canvasSize = getCanvasSize();

	drawingHeadPos = cellBufferElement.bounds.ul;
	drawingHeadPos.x += pos.x;
	drawingHeadPos.y += pos.y - 1;

	if (drawingHeadPos.x > canvasSize.x + cellBufferElement.bounds.lr.x)
		drawingHeadPos.x = canvasSize.x + cellBufferElement.bounds.lr.x;
	if (drawingHeadPos.y > canvasSize.y + cellBufferElement.bounds.lr.y)
		drawingHeadPos.y = canvasSize.y + cellBufferElement.bounds.lr.y;
}

int ImageUserInterface::draw()
{
	if (isEnqueued(TUIElement::commandLine))
	{
		drawLine(commandLineElement.bounds.ul, commandLineElement.bounds.lr, ' ');
		drawText(commandLineElement.data, commandLineElement.bounds);
	}

	if (isEnqueued(TUIElement::statusLine))
	{
		drawLine(statusLineElement.bounds.ul, statusLineElement.bounds.lr, ' ');
		drawText(statusLineElement.data, statusLineElement.bounds);
	}

	moveCursor(drawingHeadPos);
	if (isEnqueued(TUIElement::cellBuffer))
		drawCellAtDrawingHead();

	queueFlags = 0;

	return 0;
}

void ImageUserInterface::setImageSize(const uvec2d& size)
{
	imageSize = size;
}

uvec2d ImageUserInterface::getCanvasSize()
{
	rect bounds = cellBufferElement.bounds;
	return uvec2d{ bounds.lr.x - bounds.ul.x, bounds.lr.y - bounds.ul.y };
}

void ImageUserInterface::clearScreen()
{
#if defined (_WIN32) or defined (_WIN64)
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	screenSize.x = csbi.dwSize.X;
	screenSize.y = csbi.dwSize.Y;
	system("cls");
	drawLine({ 0, screenSize.y - 2 }, { screenSize.x, screenSize.y - 2 }, '#');
	drawLine({ 0, screenSize.y - 4 }, { screenSize.x, screenSize.y - 4 }, '#');
	drawLine({ 0, 0 }, { screenSize.x, 0 }, '#');
#else
	winsize size;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
	screenSize.x = size.ws_col;
	screenSize.y = size.ws_row;
	drawBox({ {0, 0}, screenSize }, ' ', '#');
	drawLine({ 1, screenSize.y - 4 }, { screenSize.x, screenSize.y - 4 }, '#');
	drawLine({ 1, screenSize.y - 2 }, { screenSize.x, screenSize.y - 2 }, '#');
#endif

	cellBufferElement.flag = TUIElement::cellBuffer;
	cellBufferElement.bounds.ul = { 5, 3 };
	cellBufferElement.bounds.lr = { screenSize.x - 4, screenSize.y - 8 };
	cellBufferElement.data = nullptr;

	commandLineElement.flag = TUIElement::commandLine;
	commandLineElement.bounds.ul = { 5, screenSize.y - 3 };
	commandLineElement.bounds.lr = { screenSize.x - 4, screenSize.y - 3 };
	commandLineElement.data = nullptr;

	statusLineElement.flag = TUIElement::statusLine;
	statusLineElement.bounds.ul = { 5, screenSize.y - 1 };
	statusLineElement.bounds.lr = { screenSize.x - 4, screenSize.y - 1 };
	statusLineElement.data = nullptr;

	drawingHeadPos = cellBufferElement.bounds.ul;
}

void ImageUserInterface::drawLine(const uvec2d& from, const uvec2d& to, char body)
{
	if (from.y != to.y)
		return;

	moveCursor(from);

	for (unsigned x = from.x; x < to.x; x++)
		putchar(body);
}

void ImageUserInterface::drawPipe(const uvec2d& from, const uvec2d& to, char body)
{
	if (from.x != to.x)
		return;

	for (unsigned y = from.y; y < to.y; y++)
	{
		moveCursor({from.x, y});
		putchar(body);
	}
}

void ImageUserInterface::drawBox(const rect& box, char body, char border)
{
	for (unsigned y = box.ul.y; y < box.lr.y; y++)
		drawLine({box.ul.x, y}, {box.lr.x, y}, body);
	drawLine({box.ul.x, box.lr.y}, box.lr, border);
	drawLine(box.ul, {box.lr.x, box.ul.y}, border);

	drawPipe(box.ul, {box.ul.x, box.lr.y}, border);
	drawPipe({box.lr.x, box.ul.y}, box.lr, border);
}

void ImageUserInterface::drawText(const char* text, const rect& boundary)
{
	uvec2d cursorPos = {boundary.ul.x, boundary.ul.y};
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

void ImageUserInterface::drawCellAtDrawingHead()
{
	moveCursor(drawingHeadPos);
	uvec2d& ul = cellBufferElement.bounds.ul;
	uvec2d imagePos = { drawingHeadPos.x - ul.x, drawingHeadPos.y - ul.y + 1 };
	Cell cell = ((Cell*)cellBufferElement.data)[imagePos.y * imageSize.x + imagePos.x];

#if defined (_WIN32) or defined (_WIN64)
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, (curr.bg << 1) + curr.fg);
	putchar('\b');
	SetConsoleTextAttribute(hConsole, 0F);
#else
	int mod = ((int)cell.fg > 100) ? 1 : 0;
	int fg = (int)cell.fg & 0x7F;
	int bg = ((int)cell.bg & 0x7F) + 10;
	printf("\033[%d;%d;%dm%c\033[1D\033[0m", mod, fg, bg, cell.ch);
#endif
}

void ImageUserInterface::drawCells(const Cell* cells)
{
	uvec2d canvasSize = getCanvasSize();
	rect& bound = cellBufferElement.bounds;
	moveCursor(bound.ul);

#if defined (_WIN32) or defined (_WIN64)
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
#endif

	for (unsigned y = 0; y < imageSize.y && y < canvasSize.y; y++)
	{
		for (unsigned x = 0; x < imageSize.x && x < canvasSize.x; x++)
		{
			Cell curr = cells[y * imageSize.x + x];

#if defined (_WIN32) or defined (_WIN64)
			SetConsoleTextAttribute(hConsole, (curr.bg << 1) + curr.fg);
#else
			int mod = ((int)curr.fg > 100) ? 1 : 0;
			int fg = (int)curr.fg & 0x7F;
			int bg = ((int)curr.bg & 0x7F) + 10;
			printf("\033[%d;%d;%dm%c", mod, fg, bg, curr.ch);
#endif
		}

		moveCursor({bound.ul.x, bound.ul.y + y});
	}

#if defined (_WIN32) or defined (_WIN64)
	SetConsoleTextAttribute(hConsole, 0F);
#else
	printf("\033[0m");
#endif
}

void ImageUserInterface::enqueueData(TUIElement flag, const char* data)
{
	element* uielements[3] = { 
		&cellBufferElement, &commandLineElement, &statusLineElement 
	};

	for (int i = 0; i < 3; i++)
	{
		if (uielements[i]->flag == flag)
		{
			queueFlags |= (unsigned char)flag;
			uielements[i]->data = data;
		}
	}
}

bool ImageUserInterface::isEnqueued(TUIElement flag)
{
	return (queueFlags & (unsigned char)flag) == (unsigned char)flag;
}

void ImageUserInterface::startCommand()
{
	drawLine(commandLineElement.bounds.ul, commandLineElement.bounds.lr, ' ');
	drawText("command -> /", commandLineElement.bounds);
}

