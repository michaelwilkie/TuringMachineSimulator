/*
	TM.cpp

	Michael Wilkie
	Logic of the turing machine when it reads in characters.
	The start and end of any tape read in are hard-coded to be '-'
*/
#include <iostream>
#include <vector>
#include <string>
#include "Slot.h"
#include "TM.h"

TM::TM(string &str)
{
	tape = "-" + str + "-";
	index = 1;
}
TM::~TM() {}
bool TM::process(Slot &s)
{
	char c = tape[index];
	if (c == s.read)
	{
		tape[index] = s.write;
		if (s.direction == 'R')
			++index;
		else if (s.direction == 'L')
			--index;
	}
	else
		return false;
	return true;
}
void TM::print()
{
	int inputlength = tape.length();
	for (int i = 0; i < inputlength; ++i)
		cout << tape[i] << " ";
	cout << endl;
	for (int i = 0; i < index; ++i)
		cout << "  ";
	cout << "^" << endl;
	return;
}