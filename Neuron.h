#pragma once
#include "ofMain.h"
#include <fstream>
#include <time.h>

/*--------------------------
-- result saved in file like bytes
-- 0x00 is reserved for next neuron
-- result is stored in a probability from 0x01 to 0xff
-- network start at position with 9 0x00
--
--
--
--
--
--
---------------------------*/

#define NumberOfElements 9

typedef unsigned char byte;

class Neurons
{
private:

	struct neurons
	{
		byte neuron[NumberOfElements];
	};

	struct GameMemory
	{
		int cell;
		int next;
	};

	neurons neuron[NumberOfElements];

	//path to the saved network memory
	string path;

	//Max number of steps is 9 in one game
	//in each step save current position
	GameMemory stepsMemory[NumberOfElements];

	//player1 is winner - win = 1
	//player2 is winner - win = 2
	//nobody win - win = 0

	// ssearch the highest neuron
	template<typename type>
	void QuickSort(type* arr, int l, int r);

	// overwrite all network memory
	bool SaveNetwork(void);

public:
	// create file "network.txt" with all memory, each element of which is 0
	Neurons();

	// open an existing network memory
	void MyNeurons(string path);


	int step = 0;

	~Neurons();

	// step - which step of game is now; Strarts counting from 0 for each game
	// next step is the previous n
	// n - which cell was chosen at current step
	bool Write2Network(int cell, int n, byte Teach = 0);

	// increase chanse on that steps which lead to victory and decrease on which not
	void Victory(bool IsIt);

	// return number of cell on next step
	// teke number of current cell
	int GetFromNetwork(int cell, int* arr);

	ifstream fin;
	ofstream fout;
};