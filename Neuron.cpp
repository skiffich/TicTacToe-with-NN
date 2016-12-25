#include "Neuron.h"



Neurons::Neurons()
{
	fin.open("data/network", std::ios_base::binary);
	if (fin.is_open())
	{
		fin.close();
		MyNeurons("data/network");
		return;
	}

	fin.close();
	path = "data/network";
	fout.open("data/network", std::ios_base::binary);
	byte ch = byte(1);
	for (int i = 0; i < NumberOfElements; i++)
		for (int j = 0; j < NumberOfElements; j++)
			fout << ch;
	fout.close();

	MyNeurons("data/network");
}

void Neurons::MyNeurons(string read_path)
{
	path = read_path;
	fin.open(path, std::ios_base::binary);
	int i = 0;
	int j = 0;
	for (int i(0); i < NumberOfElements; i++)
		for (int j(0); j < NumberOfElements; j++)
			fin >> neuron[i].neuron[j];
	fin.close();
}

bool Neurons::Write2Network(int cell, int n, byte Teach) {
	if (Teach > 0)
	{
		neuron[step - 1].neuron[n] += Teach;
		return true;
	}
	neuron[step].neuron[n]++;

	stepsMemory[step].cell = cell;
	stepsMemory[step].next = n;
	step++;

	return true;
}

bool Neurons::SaveNetwork(void) {
	fout.open(path, ios_base::binary);
	for (int i = 0; i < NumberOfElements; i++)
		for (int j = 0; j < NumberOfElements; j++)
		{
			byte ch = neuron[i].neuron[j];
			fout << ch;
		}
	fout.close();

	step = 0;

	return true;
}

void Neurons::Victory(bool IsIt) {
	if (IsIt)
	{
		step--; //decrement step after after win iteration
		int result = 1;
		while (step >= 0)
		{
			if (neuron[step].neuron[stepsMemory[step].next] > 0 && neuron[step].neuron[stepsMemory[step].next] < 255)
				neuron[step].neuron[stepsMemory[step].next] += result;
			result *= -1;
			step--;
		}
	}
	else
	{
		while (step >= 0)
		{
			if (neuron[step].neuron[stepsMemory[step].next] > 0 && neuron[step].neuron[stepsMemory[step].next] < 255)
				neuron[step].neuron[stepsMemory[step].next]++;
			step--;
		}
	}
	SaveNetwork();
}

int Neurons::GetFromNetwork(int cell, int* arr) {
	int *Arr;
	Arr = arr;

	byte Percent[9];
	for (int i(0); i < NumberOfElements; i++)
	{
		Percent[i] = neuron[step].neuron[i];
		if (Arr[i] != 0)
			Percent[i] = byte(0);
	}

	byte AllSum = byte(0);
	for (int i(0); i < NumberOfElements; i++)
		AllSum += Percent[i];

	if (AllSum > 0)
	{
		srand(time(NULL));
		byte rndnmb = (rand() % AllSum) + 1;

		byte temp = byte(0);
		for (int i(0); i < NumberOfElements; i++)
		{
			temp = temp + Percent[i];
			if (temp >= rndnmb)
				return i;
		}
	}
}

template<typename type>
void Neurons::QuickSort(type* arr, int l, int r) {
	int i, j;
	i = l;
	j = r;
	type middle = arr[(i + j) / 2];

	do
	{
		while (middle > arr[i]) i++;
		while (middle < arr[j]) j--;

		if (i <= j)
		{
			swap(arr[i], arr[j]);
			i++;
			j--;
		}

	} while (i < j);

	if (i < r) QuickSort(arr, i, r);
	if (j > l) QuickSort(arr, l, j);
}

Neurons::~Neurons()
{
	SaveNetwork();
}