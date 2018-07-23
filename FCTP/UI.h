#pragma once

#include "Windows.h"

class UI_class
{
public:
	UI_class();
	~UI_class();
	
	bool MainMenu();
	void DrawArea();
	void DrawBrick(SHORT x, SHORT y, int color, HANDLE hOut);
	void DrawUI(int area[20][10], int score);
	void ClearRow(int X, int Y, int rowWidth);
	void ClearRectangle(int X1, int Y1, int X2, int Y2);
	void SetFont();
	void TextColor(int color);
	void CmdSetup(int width, int height);

	bool m_AreaDrawn = false;
};