#pragma once

#include "../UserInterface.h"


struct vec2d
{
	unsigned x, y;
	
	unsigned length();
	vec2d lerp(const vec2d& other, float t);
};

class TextUserInterface : public UserInterface
{
private:

	unsigned screenWidth;
	unsigned screenHeight;

	void moveCursor(const vec2d& pos);
	void clampToScreen(vec2d& pos);

public:
	TextUserInterface();
	~TextUserInterface() override {}

	int draw() override;

	void drawLine(const vec2d& pos, unsigned depth, char body);
	void drawBox(const vec2d& pos, unsigned depth, char border, char body);
	void drawText(const vec2d& pos, const char* text, 
			const vec2d& boudary = {0, 0}, unsigned margin = 1);
};

