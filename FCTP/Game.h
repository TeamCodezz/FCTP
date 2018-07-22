#pragma once

#include "UI.h"

#define COLLISION_TYPE_NULL 1
#define COLLISION_TYPE_WALL_LEFT 2
#define COLLISION_TYPE_WALL_RIGHT 3
#define COLLISION_TYPE_BLOCK 4
#define COLLISION_TYPE_FLOOR 5

struct Block_struct
{
	int m_X, m_Y;
	int m_W, m_H;
	int m_Structure[4][4] = { 0 };
};

struct Collision_struct
{
	int m_Type;
	bool m_State;
};

class Game_class
{
public:
	Game_class(UI_class* UI);
	~Game_class();

	// Methodes here
	void Loop();
	void ClearArea();
	void PushBlockToArea(Block_struct block);
	Collision_struct Collision(Block_struct colliding_block);
	Block_struct CreateRandomBlock(int random_number);

	// Variables here
	bool m_Finished;
	bool m_Playing;
	bool m_BlockSpawned;
	double m_TimePlayed;
	int m_Area[20][10];
	Block_struct m_CurrentFallingBlock;

private:
	// Don't touch this shit
	UI_class* m_UI;
};