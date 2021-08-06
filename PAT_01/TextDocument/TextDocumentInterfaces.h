#pragma once

#include "TextDocument.h"
#include <iostream>
#include <string.h>


class TextDocumentFileSpec : public DocumentFileSpec
{
private:
	void appendToBuffer(char*& dst, const char* src);
	bool isValid(const char*& buffer);
public:
	TextDocumentFileSpec(Document* parent)
		: DocumentFileSpec(parent)
	{}
	unsigned getSaveData(char*& buffer) override;
	Document* parseData(const char* buffer) override;
};


class TextDocumentRenderer : public DocumentRenderer
{
public:
	TextDocumentRenderer(Document* parent)
		: DocumentRenderer(parent)
	{}
	int draw() override;
};


class TextDocumentEditor : public DocumentEditor
{
public:
	TextDocumentEditor(Document* parent)
		: DocumentEditor(parent)
	{}
	int editDocument(char input) override;
};

