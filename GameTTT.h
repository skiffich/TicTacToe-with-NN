#pragma once

#include "Neuron.h"

// definition for check
// H - Horizontal
// V - Vertical
//numeration starts from top left corner from 1
// D1 - diagonal from top left corner
// D2 - diagonal from top right corner
// DH - DeadHead
#define H1 1
#define H2 2
#define H3 3

#define V1 4
#define V2 5
#define V3 6

#define D1 7
#define D2 8

#define DH 9

// Modes
// P - Player
// M - Machine
#define PvsP 1
#define PvsM 2
#define MvsM 3

class GameTTT
{
private:
	int player = 1;
	int step, next, prevStep, PrevCell;
	int get;
	Neurons network;
	unsigned int steps;

	int Check4Winner();
	bool Write2Mas(int cell);

public:

	int Mas[9];

	int GameMain(int Mode = 1, int cell = -1);

	int GetMasCell(int cell);

	void Clear();

	void Teach(int add = 0);

	void ReturnStep();

	GameTTT();
	~GameTTT();
};