#pragma once


struct vec2d
{
	int x;
	int y;
};

enum screen_places : int
{
	TOPRIGHT 	= 0xFFF0,
	TOPLEFT 	= 0xFFF1,
	BOTTOMRIGHT	= 0xFFF2,
	BOTTOMLEFT 	= 0xFFF3,
	CENTER 		= 0xFFF4,
	MIDRIGHT 	= 0xFFF5,
	MIDLEFT 	= 0xFFF6
};

class UserInterface
{
protected:
	vec2d screen_size;
	vec2d cursor_pos;

public:
	virtual void initialize() = 0;
	virtual void move_cursor(const vec2d& pos) = 0;
	virtual void clear_screen() = 0;
	vec2d get_cursor_pos() { return cursor_pos; }
};

class UserInterfaceAbstraction
{
private:
	UserInterface* impl;

public:
	UserInterfaceAbstraction(UserInterface* impl)
	{
		this->impl = impl;
	}

	void initialize()
	{
		impl->initialize();
	}

	void move_cursor(const vec2d& pos)
	{
		impl->move_cursor(pos);
	}

	void clear_screen()
	{
		impl->clear_screen();
	}

	vec2d get_cursor_pos()
	{
		return impl->get_cursor_pos();
	}
};


#if defined (__linux__)

#include <sys/ioctl.h>
#include <unistd.h>
#include <iostream>


class LinuxUserInterface : public UserInterface
{
public:
	void initialize() override
	{
		winsize size {};
		ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);

		screen_size.x = size.ws_col;
		screen_size.y = size.ws_row;

		move_cursor({0, 0});
	}

	void move_cursor(const vec2d& pos) override
	{
		switch (pos.x)
		{
		case TOPRIGHT:
			cursor_pos = { 0, screen_size.y };
			break;
		case TOPLEFT:
			cursor_pos = { 0, 0 };
			break;
		case BOTTOMRIGHT:
			cursor_pos = { screen_size.x, screen_size.y };
			break;
		case BOTTOMLEFT:
			cursor_pos = { screen_size.x, 0 };
			break;
		case CENTER:
			cursor_pos = { screen_size.x / 2, screen_size.y / 2 };
			break;
		case MIDRIGHT:
			cursor_pos = { int(screen_size.x / 1.75f), screen_size.y / 2 };
			break;
		case MIDLEFT:
			cursor_pos = { int(screen_size.x / 1.25f), screen_size.y / 2 };
			break;
		defalut:
			cursor_pos = pos;
			break;
		}

		printf("\033[%d;%df", cursor_pos.y, cursor_pos.x);
	}

	void clear_screen() override
	{
		system("clear");
	}
};

#elif defined (_WIN32) or defined (_WIN64)

#include <Windows.h>
#include <iostream>


class WindowsUserInterface : public UserInterface
{
public:
	void initialize() override
	{
		CONSOLE_SCREEN_BUFFER_INFO csbi {};
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
		screen_size.x = csbi.srWindow.Right - csbi.srWindow.Left + 1;
		screen_size.y = csbi.srWindow.Right - csbi.srWindow.Left + 1;

		move_cursor({0, 0});
	}

	void move_cursor(const vec2d& pos) override
	{
		cursor_pos = pos;
		COORD coord = { (short)pos.x, (short)pos.y };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	}

	void clear_screen() override
	{
		system("cls");
	}
};

#endif
