#pragma once
//
// The 'tape' that a turing machine reads from
//
class Slot
{
public:
	char read;
	char write;
	char direction;
	Slot()
	{
		read = '-';
		write = '-';
		direction = '-';
	}
};
