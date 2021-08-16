#pragma once

#include "../UserInterface.h"
#include "ImageDocument.h"

using Cell = ImageDocument::Cell;


enum class TUIElement : unsigned char
{
	cellBuffer 	= 0b0001,
	commandLine = 0b0010,
	statusLine 	= 0b0100
};

class ImageUserInterface : public UserInterface
{
private:
	uvec2d screenSize;
	uvec2d imageSize;
	uvec2d drawingHeadPos;

	unsigned char queueFlags;

	struct element
	{
		TUIElement flag;
		rect bounds;
		const char* data;
	};

	element cellBufferElement;
	element commandLineElement;
	element statusLineElement;

public:
	ImageUserInterface();
	~ImageUserInterface() override {}

	void setImageSize(const uvec2d& size);
	uvec2d getCanvasSize();

	void clearScreen();
	void moveCursor(const uvec2d& pos);
	void moveDrawingHead(const uvec2d& pos);

	int draw() override;
	void drawLine(const uvec2d& from, const uvec2d& to, char body);
	void drawPipe(const uvec2d& from, const uvec2d& to, char body);
	void drawBox(const rect& box, char body, char border);
	void drawText(const char* text, const rect& boudary);
	void drawCellAtDrawingHead();
	void drawCells(const Cell* cells);

	void enqueueData(TUIElement flag, const char* data);
	bool isEnqueued(TUIElement flag);

	void startCommand();
};

