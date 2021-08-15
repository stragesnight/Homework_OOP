#include "ImageDocument.h"


ImageDocument::ImageDocument(const char* name, const uvec2d& size)
	: Document(name)
{
	this->fileSpec = new ImageDocumentFileSpec(this);
	this->renderer = new ImageDocumentRenderer(this);
	this->editor = new ImageDocumentEditor(this);

	this->size = size;
	this->cellBuffer = new Cell[size.x * size.y + 1];

	fill(rect{{0, 0}, size}, Cell{' ', c_color::black});
}

ImageDocument::~ImageDocument()
{
	delete[] cellBuffer;
	size = { 0, 0 };
}

uvec2d ImageDocument::clampToSize(const uvec2d& pos)
{
	return uvec2d{
		(pos.x >= size.x) ? size.x : pos.x,
		(pos.y >= size.y) ? size.y : pos.y
	};
}

const uvec2d& ImageDocument::getSize()
{
	return size;
}

const ImageDocument::Cell& ImageDocument::getCell(const uvec2d& pos)
{
	uvec2d clamped = clampToSize(pos);
	return cellBuffer[clamped.y * size.x + clamped.x];
}

const ImageDocument::Cell* ImageDocument::getCells()
{
	return cellBuffer;
}

char ImageDocument::getChar(const uvec2d& pos)
{
	return getCell(pos).ch;
}

c_color ImageDocument::getColor(const uvec2d& pos)
{
	return getCell(pos).color;
}

void ImageDocument::setSize(const uvec2d& size)
{
	this->size = size;

	if (cellBuffer != nullptr)
		delete[] cellBuffer;

	cellBuffer = new Cell[size.x * size.y + 1];
	fill(rect{{0, 0}, size}, Cell{' ', c_color::black});
}

void ImageDocument::setCell(const uvec2d& pos, const Cell& cell)
{
	uvec2d clamped = clampToSize(pos);
	cellBuffer[clamped.y * size.x + clamped.x] = cell;
}

void ImageDocument::setCells(ImageDocument::Cell* cells)
{
	this->cellBuffer = cells;
}

void ImageDocument::setChar(const uvec2d& pos, char ch)
{
	uvec2d clamped = clampToSize(pos);
	cellBuffer[clamped.y * size.x + clamped.x].ch = ch;
}

void ImageDocument::setColor(const uvec2d& pos, c_color color)
{
	uvec2d clamped = clampToSize(pos);
	cellBuffer[clamped.y * size.x + clamped.x].color = color;
}

