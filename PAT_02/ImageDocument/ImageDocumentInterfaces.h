#pragma once

#include "ImageDocument.h"


class ImageDocumentFileSpec : public DocumentFileSpec
{
private:
	unsigned appendToBuffer(char*& dst, unsigned dstlen, 
						const char* src, unsigned srclen);
	void copyBuffer(char*& dst, const char*& src, unsigned len);
	bool isValid(const char*& buffer);
public:
	ImageDocumentFileSpec(Document* parent)
		: DocumentFileSpec(parent)
	{}
	unsigned getSaveData(char*& buffer) override;
	Document* parseData(const char* buffer) override;
};


class ImageDocumentRenderer : public DocumentRenderer
{
public:
	ImageDocumentRenderer(Document* parent)
		: DocumentRenderer(parent)
	{}
	int draw() override;
};

#ifndef UVEC2D
# define UVEC2D
struct uvec2d
{
	unsigned x;
	unsigned y;
};
#endif

class ImageDocumentEditor : public DocumentEditor
{
private:
	uvec2d drawingHeadPos;

public:
	ImageDocumentEditor(Document* parent)
		: DocumentEditor(parent), drawingHeadPos({0, 0})
	{}
	int editDocument(char input) override;
};

