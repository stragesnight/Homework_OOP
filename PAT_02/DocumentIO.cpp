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

unsigned DiskIOManager::appendToBuffer(char*& dst, unsigned dstlen,
										   const char* src, unsigned srclen)
{
	char* res = new char[dstlen + srclen]{};

	for (unsigned i = 0; i < dstlen; i++)
		res[i] = dst[i];

	for (unsigned i = 0; i < srclen; i++)
		res[dstlen + i] = src[i];

	delete[] dst;
	dst = res;

	return dstlen + srclen + 1;
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

	const unsigned CLUSTER_SIZE = 2048;
	char* buffer = nullptr;
	char* tmp = new char[CLUSTER_SIZE]{};
	unsigned streamsize = 0;

	while (!ifstr.eof())
	{
		memset(tmp, 0, CLUSTER_SIZE);
		unsigned readsize = ifstr.readsome(tmp, CLUSTER_SIZE);
		if (readsize == 0)
			break;
		streamsize = appendToBuffer(buffer, streamsize, tmp, readsize - 1);
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

