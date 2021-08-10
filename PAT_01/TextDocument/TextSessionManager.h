#pragma once

#include "../SessionManager.h"
#include <string>
#include <map>

class TextSessionManager : public SessionManager
{
protected:
	std::map<std::string, int(*)(const char*)>* sessionCommands;

	int update() override;
	int processInput(char input) override;
	int processCommand() override;

public:
	TextSessionManager();
	~TextSessionManager() override;
	int startSession() override;
};
