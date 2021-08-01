#pragma once

#include "Document.h"

// disk input/output manager
// responsible for all communications with disk storage
class DiskIOManager
{
private:
	static DiskIOManager* instance;

public:
	DiskIOManager();
	
	static DiskIOManager* getInstance();

	int saveDocument(DocumentFileSpec* fileSpec);
	Document openDocument(const char* filepath);
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


