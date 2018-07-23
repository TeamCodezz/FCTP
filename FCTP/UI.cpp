#include "UI.h"

#include "Windows.h"
#include <iostream>
#include "wchar.h"
#include "conio.h"

using namespace std;

UI_class::UI_class()
{

}

UI_class::~UI_class()
{

}

bool UI_class::MainMenu()
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	ClearRectangle(0, 0, 24, 22);
	SetConsoleCursorPosition(hOut, {9, 8});
	cout << "Start";
	SetConsoleCursorPosition(hOut, {9, 11});
	cout << "Exit";
	SetConsoleCursorPosition(hOut, { 6, 8 });
	TextColor(11);
	cout << "-> ";
	TextColor(15);
	bool choice = true;
	while(true)
	{
		if (_kbhit())
		{
			switch (_getch())
			{
				case 'w':
				{
					ClearRectangle(6, 8, 9, 12);
					SetConsoleCursorPosition(hOut, { 6, 8 });
					TextColor(11);
					cout << "-> ";
					TextColor(15);
					choice = true;
					break;
				}
				case 's':
				{
					ClearRectangle(6, 8, 9, 12);
					SetConsoleCursorPosition(hOut, { 6, 11 });
					TextColor(11);
					cout << "-> ";
					TextColor(15);
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

	for (SHORT i = 0; i < 23; i++)						//Horizontals
	{
		FillConsoleOutputCharacterW(hout, (WCHAR)'#', 1, { i,0 }, &count);
		if(i < 12)
			FillConsoleOutputCharacterW(hout, (WCHAR)'#', 1, { i,21 }, &count);
		else
			FillConsoleOutputCharacterW(hout, (WCHAR)'#', 1, { i,6 }, &count);
	}
	for (SHORT i = 1; i < 21; i++)						//Verticals
	{
		FillConsoleOutputCharacterW(hout, (WCHAR)'#', 1, { 0,i }, &count);
		FillConsoleOutputCharacterW(hout, (WCHAR)'#', 1, { 11,i }, &count);
		if(i < 6)
			FillConsoleOutputCharacterW(hout, (WCHAR)'#', 1, { 22,i }, &count);
	}
	m_AreaDrawn = true;
}

void UI_class::DrawBrick(SHORT x, SHORT y, int color, HANDLE hOut)
{
	SetConsoleCursorPosition(hOut, { x + 1, y + 1 });
	TextColor(color);
	cout << "@";
}

void UI_class::DrawUI(int area[20][10], int score = 0)
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD count = 1L;

	if (!m_AreaDrawn)									//Area borders and score bar
		DrawArea();

	TextColor(8);
	SetConsoleCursorPosition(hOut, { 14, 2 });
	cout << "Score:";
	SetConsoleCursorPosition(hOut, { 14, 4 });
	cout << score;
	TextColor(15);

	ClearRectangle(1, 1, 11, 21);
	for (SHORT mapY = 0; mapY < 20; mapY++)
	{
		for (SHORT mapX = 0; mapX < 10; mapX++)
		{
			switch (area[mapY][mapX])
			{
			case 0:
				//DrawBrick(mapX, mapY, 8, hOut);
				break;
			case 1:
				DrawBrick(mapX, mapY, 8, hOut);
				break;
			case 2:
				DrawBrick(mapX, mapY, 8, hOut);
				break;
			case 3:
				DrawBrick(mapX, mapY, 8, hOut);
				break;
			case 4:
				DrawBrick(mapX, mapY, 8, hOut);
				break;
			case 5:
				DrawBrick(mapX, mapY, 8, hOut);
				break;
			case 6:
				DrawBrick(mapX, mapY, 8, hOut);
				break; 
			case 7:
				DrawBrick(mapX, mapY, 8, hOut);
				break;
			}
		}
	}
	TextColor(15);
	Sleep(1000);
}

void UI_class::ClearRow(int X, int Y, int rowWidth)
{
	HANDLE						hStdOut;
	CONSOLE_SCREEN_BUFFER_INFO	csbi;
	DWORD						count;
	COORD						homeCoords = { X,Y };

	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hStdOut == INVALID_HANDLE_VALUE) return;

	if (!GetConsoleScreenBufferInfo(hStdOut, &csbi)) return;

	if (!FillConsoleOutputCharacter(					// Fill the row with spaces
		hStdOut,
		(TCHAR) ' ',
		rowWidth,
		homeCoords,
		&count
	)) return;

	if (!FillConsoleOutputAttribute(					//Fill the row with the current colors and attributes
		hStdOut,
		csbi.wAttributes,
		rowWidth,
		homeCoords,
		&count
	)) return;

	SetConsoleCursorPosition(hStdOut, homeCoords);		//Move the cursor home
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
	cfi.dwFontSize.X = 0;								// Width of each character in the font (automatic in cmd fonts)
	cfi.dwFontSize.Y = 24;								// Height
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	wcscpy_s(cfi.FaceName, L"Lucida Console");			// Choose your font
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
}

void UI_class::TextColor(int color)
{
	SetConsoleTextAttribute
	(
		GetStdHandle(STD_OUTPUT_HANDLE),
		color
	);
}

void UI_class::CmdSetup(int width, int height)
{
	COORD coord = { width, height};						// Create coordiate system

	SetConsoleTitleW(L"TETRIS (FCTP)");

	_SMALL_RECT Rect;									// Create window size blank
	Rect.Top = 0;
	Rect.Left = 0;
	Rect.Bottom = height - 1;
	Rect.Right = width - 1;

	HANDLE Handle = GetStdHandle(STD_OUTPUT_HANDLE);	// Get Handle
	SetConsoleWindowInfo(Handle, TRUE, &Rect);			// Set Window Size 
	SetConsoleScreenBufferSize(Handle, coord);			// Set Buffer Size 

	CONSOLE_CURSOR_INFO info;							// Set Cursor invisible
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(Handle, &info);
}
