#pragma once

#include "Document.h"


// disk input/output manager
// responsible for all communications with disk storage
class DiskIOManager
{
private:
	static DiskIOManager* instance;

	unsigned appendToBuffer(char*& dst, unsigned dstlen, 
						const char* src, unsigned srclen);

public:
	DiskIOManager();
	
	static DiskIOManager* getInstance();

	int saveDocument(const char* filepath, DocumentFileSpec* fileSpec);
	Document* openDocument(const char* filepath, DocumentFileSpec* fileSpec);
};


// printer input/output manager
// responsible for all communications with printers
class PrinterIOManager
{
private:
	static PrinterIOManager* instance;

public:
	PrinterIOManager();

	static PrinterIOManager* getInstance();

	int print(DocumentRenderer* renderer);
};

