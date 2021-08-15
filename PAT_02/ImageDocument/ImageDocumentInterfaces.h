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


class ImageDocumentEditor : public DocumentEditor
{
public:
	ImageDocumentEditor(Document* parent)
		: DocumentEditor(parent)
	{}
	int editDocument(char input) override;
};

