#include "Game.h"
#include "TimeManager.h"

#include <iostream>
#include <random>

Game_class::Game_class(UI_class* UI)
{
	m_UI = UI;
}

Game_class::~Game_class()
{

}

void Game_class::Loop()
{
	Time time_manager;

	m_Finished = false;
	m_BlockSpawned = false;
	m_Playing = true;
	m_Score = 0;
	m_TimePlayed = 0;
	ClearArea();

	std::random_device rand_d;
	std::mt19937 mt(rand_d());
	std::uniform_int_distribution<int> block_distribution(1, 4);

	while (!m_Finished)
	{
		if (m_Playing)
		{
			m_TimePlayed = time_manager.GetTime();

			if (!m_BlockSpawned)
			{
				m_CurrentFallingBlock = CreateRandomBlock(block_distribution(mt));
				m_BlockSpawned = true;
			}

			m_CurrentFallingBlock.m_Y += 1;

			Collision_struct tempCollision = Collision(m_CurrentFallingBlock);
			if (tempCollision.m_State)
			{
				if (tempCollision.m_Type == COLLISION_TYPE_BLOCK || tempCollision.m_Type == COLLISION_TYPE_FLOOR)
				{
					m_BlockSpawned = false;
				}

				if (tempCollision.m_Type == COLLISION_TYPE_WALL_LEFT)
				{
					m_CurrentFallingBlock.m_X += 1;
				}

				if (tempCollision.m_Type == COLLISION_TYPE_WALL_RIGHT)
				{
					m_CurrentFallingBlock.m_X -= 1;
				}
			}
		}
	}
}

void Game_class::PushBlockToArea(Block_struct block)
{
	for (int h = 0; h < block.m_H; h++)
	{
		for (int w = 0; w < block.m_W; w++)
		{
			if (m_Area[block.m_Y + h][block.m_X + w] == 0)
				m_Area[block.m_Y + h][block.m_X + w] = block.m_Structure[h][w];
		}
	}
}

Collision_struct Game_class::Collision(Block_struct colliding_block)
{
	Collision_struct tempCollision;
	tempCollision.m_State = false;
	tempCollision.m_Type = COLLISION_TYPE_NULL;

	for (int h = 0; h < colliding_block.m_H; h++)
		for (int w = 0; w < colliding_block.m_W; w++)
			if (colliding_block.m_Structure[h][w] == 1)
			{
				if (m_Area[colliding_block.m_Y + h + 1][colliding_block.m_X + w] == 1)
				{
					tempCollision.m_State = true;
					tempCollision.m_Type = COLLISION_TYPE_BLOCK;

					return tempCollision;
				}

				if (colliding_block.m_Y >= 20)
				{
					tempCollision.m_State = true;
					tempCollision.m_Type = COLLISION_TYPE_FLOOR;

					return tempCollision;
				}

				if (colliding_block.m_X <= 0)
				{
					tempCollision.m_State = true;
					tempCollision.m_Type = COLLISION_TYPE_WALL_LEFT;

					return tempCollision;
				}

				if (colliding_block.m_X + w >= 10)
				{
					tempCollision.m_State = true;
					tempCollision.m_Type = COLLISION_TYPE_WALL_RIGHT;

					return tempCollision;
				}
			}

	return tempCollision;
}

void Game_class::ClearArea()
{
	for (int i = 0; i < 20; i++)
		for (int j = 0; j < 10; j++)
			m_Area[i][j] = 0;
}

Block_struct Game_class::CreateRandomBlock(int random_number)
{
	Block_struct tempBlock;

	if (random_number > 4 || random_number < 1)
		return tempBlock;

	if (random_number == 1)
	{
		tempBlock.m_W = 3;
		tempBlock.m_H = 2;
		tempBlock.m_X = 4;
		tempBlock.m_Y = 0;

		tempBlock.m_Structure[0][1] = 1;
		tempBlock.m_Structure[1][0] = 1; tempBlock.m_Structure[1][1] = 1; tempBlock.m_Structure[1][2] = 1;

		return tempBlock;
	}

	if (random_number == 2)
	{
		tempBlock.m_W = 3;
		tempBlock.m_H = 2;
		tempBlock.m_X = 4;
		tempBlock.m_Y = 0;

		tempBlock.m_Structure[0][2] = 1;
		tempBlock.m_Structure[1][0] = 1; tempBlock.m_Structure[1][1] = 1; tempBlock.m_Structure[1][2] = 1;

		return tempBlock;
	}

	if (random_number == 3)
	{
		tempBlock.m_W = 2;
		tempBlock.m_H = 2;
		tempBlock.m_X = 4;
		tempBlock.m_Y = 0;

		tempBlock.m_Structure[0][0] = 1; tempBlock.m_Structure[0][1] = 1;
		tempBlock.m_Structure[1][0] = 1; tempBlock.m_Structure[1][1] = 1;

		return tempBlock;
	}
}