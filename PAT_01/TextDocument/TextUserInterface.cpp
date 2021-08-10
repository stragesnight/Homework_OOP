#include "TextUserInterface.h"

#if defined (_WIN32) or defined (_WIN64)
# include <Windows.h>
#else
# include <sys/ioctl.h>
# include <unistd.h>
#endif

#include <cmath>


unsigned vec2d::length()
{
	return sqrt(x * x + y * y);
}

vec2d vec2d::lerp(const vec2d& other, float t)
{
	float x = (float)this->x + t * (other.x - this->x);
	float y = (float)this->y + t * (other.y - this->y);

	return vec2d{(unsigned)x, (unsigned)y};
}

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
}

int TextUserInterface::draw()
{
	return 0;
}

void TextUserInterface::drawLine(const vec2d& pos, unsigned depth, char body)
{

}

void TextUserInterface::drawBox(const vec2d& pos, unsigned depth, char border, char body)
{

}

void TextUserInterface::drawText(const vec2d& pos, const char* text,
		const vec2d& boundary, unsigned margin)
{

}
