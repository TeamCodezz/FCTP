#include "UI.h"
#include "Game.h"

#include <iostream>

int main()
{
	UI_class* UI = new UI_class();
	Game_class* Game = new Game_class(UI);

	UI->SetFont();
	UI->TextColor(15);
	UI->SetCmdSize(12, 23);

	UI->ClearRectangle(0, 0, 12, 23);
  
	Game->Loop();

	delete Game;
	delete UI;

	return 0;
}
