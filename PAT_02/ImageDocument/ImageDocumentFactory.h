#pragma once

#include "../DocumentFactory.h"


class ImageDocumentFactory : public DocumentFactory
{
public:
	Document* createDocument(const char* name) override;
};
