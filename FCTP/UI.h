#pragma once

class UI_class
{
public:
	UI_class();
	~UI_class();
	
	void DrawUI();
	void ClearRow(int X, int Y, int rowWidth);
	void ClearRectangle(int X1, int Y1, int X2, int Y2);
	void SetFont();
	void TextColor(int color);
	void SetCmdSize(int width, int height);
};