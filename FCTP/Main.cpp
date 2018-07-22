#include "UI.h"
#include "Game.h"

#include <iostream>

int main()
{
	UI_class* UI = new UI_class();
	Game_class* Game = new Game_class(UI);

	UI->SetFont();
	UI->TextColor(15);
	UI->SetCmdSize(24, 22);
	if (UI->MainMenu())
	{
		UI->DrawUI(Game->m_Area, Game->m_Score);
		Game->Loop();
	}
	
	//UI->ClearRectangle(0, 0, 12, 23);
  
	//Game->Loop();

	delete Game;
	delete UI;

	return 0;
}
