#pragma once

#include "../DocumentFactory.h"


class TextDocumentFactory : public DocumentFactory
{
public:
	Document* createDocument(const char* name) override;
};
