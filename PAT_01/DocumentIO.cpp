#include "DocumentIO.h"

#include <iostream>
#include <fstream>
#include <string.h>


DiskIOManager::DiskIOManager()
{
	if (instance == nullptr)
		instance = this;
}

void DiskIOManager::appendToBuffer(char*& dst, const char* src)
{
	unsigned dstlen = strlen(dst);
	unsigned srclen = strlen(dst);
	char* res = new char[dstlen + srclen + 1];

	memcpy(res, dst, dstlen);
	memcpy(res + dstlen, src, srclen);

	delete[] dst;
	dst = res;
}

DiskIOManager* DiskIOManager::getInstance()
{
	return instance;
}

int DiskIOManager::saveDocument(const char* filepath, DocumentFileSpec* fileSpec)
{
	std::ofstream ofstr(filepath, std::ios::binary);

	if (!ofstr.is_open())
		return 1;

	char* buffer;
	unsigned streamsize = fileSpec->getSaveData(buffer);

	ofstr.write(buffer, streamsize);

	ofstr.close();
	return 0;
}

Document* DiskIOManager::openDocument(const char* filepath, DocumentFileSpec* fileSpec)
{
	std::ifstream ifstr(filepath, std::ios::binary);

	if (!ifstr.is_open())
		return nullptr;

	char* buffer = new char[1];
	char tmp[256];
	unsigned streamsize = 0;

	while (!ifstr.eof())
	{
		ifstr.readsome(tmp, 256);
		appendToBuffer(buffer, tmp);
	}

	ifstr.close();
	return fileSpec->parseData(buffer, streamsize);
}


PrinterIOManager::PrinterIOManager()
{
	if (instance == nullptr)
		instance = this;
}

PrinterIOManager* PrinterIOManager::getInstance()
{
	return instance;
}

int PrinterIOManager::print(DocumentRenderer* renderer)
{
	std::cout << "*printer prints the document*\n";
	return 0;
}

