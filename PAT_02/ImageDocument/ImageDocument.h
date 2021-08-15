#pragma once

#include "../Document.h"
#include "ImageDocumentInterfaces.h"


enum class c_color : unsigned char
{
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
};


struct uvec2d
{
	unsigned x;
	unsigned y;
};

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
		c_color color;
	};

private:
	uvec2d size;
	Cell* cellBuffer;

	void fill(const rect& rect, const Cell& cell);
	void resize(const uvec2d& size);

public:
	ImageDocument(const char* name, const uvec2d& size);
	~ImageDocument();

	const uvec2d& getSize();
	const Cell& getCell(const uvec2d& pos);
	char getChar(const uvec2d& pos);
	c_color getColor(const uvec2d& pos);

	void setSize(const uvec2d& size);
	void setCell(const uvec2d& pos, const Cell& cell);
	void setChar(const uvec2d& pos, char ch);
	void setColor(const uvec2d& pos, c_color color);
};
