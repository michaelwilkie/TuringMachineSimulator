/*
	TM.h
	Michael Wilkie

	Turing Machine header class.

*/
#pragma once
#include <vector>
#include <string>
#include "Slot.h"
using namespace std;
class TM
{
public:
	int index;
	string tape;
	TM(string &str);
	~TM();
	bool process(Slot &s);
	void print();
};
