#include "DocumentIO.h"

#include <iostream>
#include <fstream>
#include <string.h>


DiskIOManager* DiskIOManager::instance = nullptr;

DiskIOManager::DiskIOManager()
{
	if (instance == nullptr)
		instance = this;
}

void DiskIOManager::appendToBuffer(char*& dst, const char* src)
{
	unsigned dstlen = 0;
	if (dst != nullptr)
		dstlen = strlen(dst);
	unsigned srclen = strlen(src);
	char* res = new char[dstlen + srclen + 1];

	if (dstlen != 0)
	{
		for (unsigned i = 0; i < dstlen; i++)
			res[i] = dst[i];
	}

	for (unsigned i = 0; i < srclen; i++)
		res[dstlen + i] = src[i];
	res[dstlen + srclen] = '\0';

	if (dst != nullptr)
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

	char* buffer = nullptr;
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

	char* buffer = nullptr;
	char tmp[32568] {};
	unsigned streamsize = 0;

	while (!ifstr.eof())
	{
		memset(tmp, 0, 32568);
		ifstr.getline(tmp, 32568, '\0');
		appendToBuffer(buffer, tmp);
	}

	ifstr.close();
	return fileSpec->parseData(buffer);
}


PrinterIOManager* PrinterIOManager::instance = nullptr;

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

