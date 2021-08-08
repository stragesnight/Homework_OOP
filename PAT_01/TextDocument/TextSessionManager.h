#pragma once

#include "../SessionManager.h"

class TextSessionManager : public SessionManager
{
protected:
	int update() override;
	int processInput(char input) override;
public:
	TextSessionManager();
	~TextSessionManager() override;
	int startSession() override;
};
