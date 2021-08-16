#pragma once

#include "../SessionManager.h"
#include <string>
#include <map>

class ImageSessionManager : public SessionManager
{
protected:
	std::map<std::string, int(*)(const char*)>* sessionCommands;

	int update() override;
	int processInput(char input) override;
	int processCommand() override;

public:
	ImageSessionManager();
	~ImageSessionManager() override;
	int startSession() override;
	void selectDocument(const char* name) override;
	void selectDocumentByIndex(unsigned index) override;
};
