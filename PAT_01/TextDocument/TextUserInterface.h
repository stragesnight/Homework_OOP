#pragma once

#include "../UserInterface.h"


struct vec2d
{
	unsigned x, y;
};


struct rect
{
	vec2d ul, lr;
};


enum class TUIElement
{
	textBuffer 	= 0b0001,
	commandLine = 0b0010,
	statusLine 	= 0b0100
};

class TextUserInterface : public UserInterface
{
private:

	unsigned screenWidth;
	unsigned screenHeight;

	unsigned char queueFlags;

	struct element
	{
		TUIElement flag;
		rect bounds;
		const char* data;
	};

	element textBufferElement;
	element commandLineElement;
	element statusLineElement;

	element* UIElements[3];

	void moveCursor(const vec2d& pos);

public:
	TextUserInterface();
	~TextUserInterface() override {}

	int draw() override;

	void clearScreen();

	void drawLine(const vec2d& from, const vec2d& to, char body);
	void drawPipe(const vec2d& from, const vec2d& to, char body);
	void drawBox(const rect& box, char body, char border);
	void drawText(const char* text, const rect& boudary);

	void enqueueData(TUIElement flag, const char* data);
	bool isEnqueued(TUIElement flag);

	void startCommand();
};

