#include "UI.h"

#include "Windows.h"
#include <iostream>
#include <wchar.h>

using namespace std;

UI_class::UI_class()
{

}

UI_class::~UI_class()
{

}

void UI_class::DrawUI()
{

}

void UI_class::ClearRow(int X, int Y, int rowWidth)
{
	HANDLE hStdOut;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD count;
	COORD homeCoords = { X,Y };

	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hStdOut == INVALID_HANDLE_VALUE) return;

	if (!GetConsoleScreenBufferInfo(hStdOut, &csbi)) return;

	// Fill the row with spaces
	if (!FillConsoleOutputCharacter(
		hStdOut,
		(TCHAR) 'A',
		rowWidth,
		homeCoords,
		&count
	)) return;

	//Fill the row with the current colors and attributes
	if (!FillConsoleOutputAttribute(
		hStdOut,
		csbi.wAttributes,
		rowWidth,
		homeCoords,
		&count
	)) return;

	//Move the cursor home
	SetConsoleCursorPosition(hStdOut, homeCoords);
}

void UI_class::ClearRectangle(int X1, int Y1, int X2, int Y2)
{
	while (Y1<Y2)
		ClearRow(X1, Y1++, X2 - X1);
}

void UI_class::SetFont()
{
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = 0;	// Width of each character in the font
	cfi.dwFontSize.Y = 24;	// Height
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	wcscpy_s(cfi.FaceName, L"Lucida Console");	// Choose your font
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
}

void UI_class::TextColor(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void UI_class::SetCmdSize(int width, int height)
{
	COORD coord = { width, height};

	_SMALL_RECT Rect;
	Rect.Top = 0;
	Rect.Left = 0;
	Rect.Bottom = height - 1;
	Rect.Right = width - 1;

	HANDLE Handle = GetStdHandle(STD_OUTPUT_HANDLE);	// Get Handle 
	SetConsoleWindowInfo(Handle, TRUE, &Rect);	// Set Window Size 
	SetConsoleScreenBufferSize(Handle, coord);	// Set Buffer Size 
}
