#pragma once
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
