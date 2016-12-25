#include "GameTTT.h"

int GameTTT::Check4Winner()
{
	int result = 0;

	if (Mas[0] == Mas[1] && Mas[1] == Mas[2] && Mas[2] != 0)
		result = H1;
	if (Mas[3] == Mas[4] && Mas[4] == Mas[5] && Mas[5] != 0)
		result = H2;
	if (Mas[6] == Mas[7] && Mas[7] == Mas[8] && Mas[8] != 0)
		result = H3;

	if (Mas[0] == Mas[3] && Mas[3] == Mas[6] && Mas[6] != 0)
		result = V1;
	if (Mas[1] == Mas[4] && Mas[4] == Mas[7] && Mas[7] != 0)
		result = V2;
	if (Mas[2] == Mas[5] && Mas[5] == Mas[8] && Mas[8] != 0)
		result = V3;

	if (Mas[0] == Mas[4] && Mas[4] == Mas[8] && Mas[8] != 0)
		result = D1;
	if (Mas[2] == Mas[4] && Mas[4] == Mas[6] && Mas[6] != 0)
		result = D2;

	if (steps == 9 && result == 0)
		result = DH;

	if (result)
	{
		if (result == DH)
			network.Victory(false);
		else network.Victory(true);
	}

	return result;
}

bool GameTTT::Write2Mas(int cell)
{
	if (Mas[cell] == 0)
	{
		steps++;

		PrevCell = cell;
		Mas[cell] = player;

		if (player == 1) player = 2;
		else player = 1;

		next = cell;
		network.Write2Network(step, next);
		prevStep = step;
		step = next;

		return true;
	}
	return false;
}

int GameTTT::GameMain(int Mode, int cell)
{
	if (Mode == PvsP && cell != -1)
	{
		Write2Mas(cell);
	}
	if (Mode == PvsM && cell != -1)
	{
		if (Write2Mas(cell))
		{
			Sleep(500);
			if (Check4Winner()) return Check4Winner();
			while (!Write2Mas(network.GetFromNetwork(cell, Mas)));
		}
	}
	if (Mode == MvsM)
	{
		get = network.GetFromNetwork(get, Mas);
		if (Write2Mas(get))
		{
			Sleep(500);
			get = network.GetFromNetwork(get, Mas);
			if (Check4Winner()) return Check4Winner();
			while (!Write2Mas(get))
			{
				get = network.GetFromNetwork(get, Mas);
			}
		}
	}
	return Check4Winner();
}

int GameTTT::GetMasCell(int cell)
{
	return Mas[cell];
}

void GameTTT::Clear()
{
	for (int i(0); i < 9; i++) Mas[i] = 0;
	step = 0;
	steps = 0;
	get = 0;
	player = 1;
	network.step = 0;
}

void GameTTT::Teach(int add)
{
	unsigned char ch = unsigned char(add);
	network.Write2Network(prevStep, next, ch);
}

void GameTTT::ReturnStep()
{
	step = prevStep;
	steps--;
	if (player == 1) player = 2;
	else player = 1;
	Mas[PrevCell] = 0;
	network.step--;
}

GameTTT::GameTTT()
{
	for (int i(0); i < 9; i++) Mas[i] = 0;
	step = 0;
	steps = 0;
	get = 0;
}

GameTTT::~GameTTT()
{
}