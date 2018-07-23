#include "UI.h"

#include "Windows.h"
#include <iostream>
#include "wchar.h"
#include "conio.h"

//enum eDirection {UP, DOWN, CHOOSE};

using namespace std;

UI_class::UI_class()
{

}

UI_class::~UI_class()
{

}

bool UI_class::MainMenu()
{
	ClearRectangle(0, 0, 24, 22);
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {9, 8});
	cout << "Start";
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {9, 11});
	cout << "Exit";
	bool choice = true;
	while(true)
	{
		if (_kbhit())
		{
			switch (_getch())
			{
				case 'w':
				{
					ClearRectangle(7, 8, 9, 12);
					SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 7, 8 });
					cout << "->";
					choice = true;
					break;
				}
				case 's':
				{
					ClearRectangle(7, 8, 9, 12);
					SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 7, 11 });
					cout << "->";
					choice = false;
					break;
				}
				case '\r':
				{
					ClearRectangle(0, 0, 24, 22);
					return choice;
					break;
				}
			}
		}
	}
	return true;
}

void UI_class::DrawArea()
{
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD count = 1;
	for (int i = 0; i < 12; i++)
	{
		FillConsoleOutputCharacterW(hout, (WCHAR)'#', 1, { (SHORT)i,0 }, &count);
		FillConsoleOutputCharacterW(hout, (WCHAR)'#', 1, { (SHORT)i,21 }, &count);
	}
	for (int i = 1; i < 21; i++)
	{
		FillConsoleOutputCharacterW(hout, (WCHAR)'#', 1, { 0,(SHORT)i }, &count);
		FillConsoleOutputCharacterW(hout, (WCHAR)'#', 1, { 11,(SHORT)i }, &count);
	}
	m_AreaDrawn = true;
}

void UI_class::DrawUI(int area[20][10], int score = 0)
{
	if (!m_AreaDrawn)
		DrawArea();

	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD count = 1;

	ClearRectangle(1, 1, 10, 20);
	/*for (int mapY = 0; mapY < 20; mapY++)
	{
		for (int mapX = 0; mapX < 10; mapX++)
		{
			if(area[mapY][mapX] == )
		}
	}*/
	Sleep(1000);
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
		(TCHAR) ' ',
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

	SetConsoleTitleW(L"TETRIS (FCTP)");

	_SMALL_RECT Rect;
	Rect.Top = 0;
	Rect.Left = 0;
	Rect.Bottom = height - 1;
	Rect.Right = width - 1;

	HANDLE Handle = GetStdHandle(STD_OUTPUT_HANDLE);	// Get Handle 
	SetConsoleWindowInfo(Handle, TRUE, &Rect);	// Set Window Size 
	SetConsoleScreenBufferSize(Handle, coord);	// Set Buffer Size 
}
