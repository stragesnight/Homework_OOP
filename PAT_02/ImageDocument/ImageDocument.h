#pragma once

#include "../Document.h"
#include "ImageDocumentInterfaces.h"


enum class c_color : unsigned char
{
#if defined (_WIN32) or defined (_WIN64)
	black 		= 0x0,
	red 		= 0x4,
	green 		= 0x2,
	yellow 		= 0x6,
	blue 		= 0x1,
	purple 		= 0x5,
	cyan 		= 0x3,
	white 		= 0x7,
	b_black 	= 0x8,
	b_red 		= 0xC,
	b_green 	= 0xA,
	b_yellow 	= 0xE,
	b_blue 		= 0x9,
	b_purple 	= 0xD,
	b_cyan 		= 0xB,
	b_white 	= 0xF
#else
	black 		= 30,
	red 		= 31,
	green 		= 32,
	yellow 		= 33,
	blue 		= 34,
	purple 		= 35,
	cyan 		= 36,
	white 		= 37,
	b_black 	= 130,
	b_red 		= 131,
	b_green 	= 132,
	b_yellow 	= 133,
	b_blue 		= 134,
	b_purple 	= 135,
	b_cyan 		= 136,
	b_white 	= 137
#endif
};


#ifndef UVEC2D
# define UVEC2D
struct uvec2d
{
	unsigned x;
	unsigned y;
};
#endif

struct rect
{
	uvec2d ul;
	uvec2d lr;
};


class ImageDocument : public Document
{
public:
	struct Cell
	{
		char ch;
		c_color bg;
		c_color fg;
	};

private:
	uvec2d size;
	Cell* cellBuffer;

	void fill(const rect& box, const Cell& cell);

	uvec2d clampToSize(const uvec2d& pos);

public:
	ImageDocument(const char* name, uvec2d size);
	~ImageDocument();

	const uvec2d& getSize();
	const Cell* getCells();
	const Cell& getCell(const uvec2d& pos);
	char getChar(const uvec2d& pos);
	c_color getBGColor(const uvec2d& pos);
	c_color getFGColor(const uvec2d& pos);

	void setSize(const uvec2d& size);
	void setCell(const uvec2d& pos, const Cell& cell);
	void setCells(Cell* cells);
	void setChar(const uvec2d& pos, char ch);
	void setBGColor(const uvec2d& pos, c_color color);
	void setFGColor(const uvec2d& pos, c_color color);
};

