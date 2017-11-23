// This file contains main()
// Turing Machine Simulator
//
// Michael Wilkie
// I made this program to see if I could create a turing machine. 
// Since turing machines are coupled with state diagrams, a graph class
// was added.
//
// Logic of the simulator:
// 
// Load/Create state diagram -> new Graph
// Test if words are in the language -> new TM
// Save/Close graph to text file -> program end
//
// It is not recommended that you copy the code if you are trying to learn about
// graphs.
//

#include <Windows.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <list>
#include "Slot.h"
#include "Graph.h"
#include "TM.h"
#include "Node.h"

using namespace std;

bool String_to_Bool(string &input)
{
	if (input == "Yes")
		return true;
	return false;
}
void readStates(Graph &machine)
{
	string input, input2;
	cout << "Create a Turing Machine:" << endl;
	cout << "Sequentially enter the name of the machine's states, proceed with '#':" << endl;
	cout << "Enter state name: ";
	cin >> input;
	while (input != "#")
	{
		cout << "Is this an accept state? (Yes / No) : " << endl;
		cin >> input2;
		machine.AddVertex(input, String_to_Bool(input2));
		cout << "Enter state name: ";
		cin >> input;
	}
	return;
}
void readEdges(Graph &machine)
{
	string input, input2;
	string r, w, d;
	cout << "Add edges to the graph:" << endl;
	cout << "Enter 'from' state: ";
	cin >> input;
	while (input != "#")
	{
		int index = machine.NameIndex(input);
		while (index < 0 && index >= machine.Names.size())
		{
			cout << "Enter 'from' state: ";
			cin >> input;
			index = machine.NameIndex(input);
		}
		cout << "Enter 'to' state: ";
		cin >> input2;
		index = machine.NameIndex(input);
		while (index < 0 && index >= machine.Names.size())
		{
			cout << "Enter 'to' state: ";
			cin >> input2;
		}
		cout << "Enter what TM should read: ";
		cin >> r;
		while (r.length() != 1)
		{
			cout << "Enter what TM should read: ";
			cin >> r;
		}
		cout << "Enter what TM should write: ";
		cin >> w;
		while (w.length() != 1)
		{
			cout << "Enter what TM should write: ";
			cin >> w;
		}
		cout << "Enter what direction TM should go: ";
		cin >> d;
		while (d.length() != 1)
		{
			cout << "Enter what direction TM should go: ";
			cin >> d;
		}
		Slot s;
		s.read = r[0];
		s.write = w[0];
		s.direction = d[0];
		machine.AddEdge(input, input2, s);

		cout << "Enter 'from' state: ";
		cin >> input;
	}
	return;
}
bool parseString(Graph &machine, string &parse)
{
	int state = 0;
	string next;

	TM reader(parse);
	Node n;
	n = machine.nextVertex(reader.tape[reader.index], state); // The index of the next vertex (next vertex finds string that the current tape index can take)
	if (!machine.Contains(n.dest))
		return false;
	system("cls");
	cout << "Processing..." << endl;
	reader.print();
	cout << "Current State: " << machine.Names[state] << endl;
	Sleep(500);
	while (reader.process(n.s))
	{
		state = machine.NameIndex(n.dest);
		system("cls");
		cout << "Processing..." << endl;
		reader.print();
		cout << "Current State: " << state << endl;
		n = machine.nextVertex(reader.tape[reader.index], state);
		if (!machine.Contains(n.dest))
			break;
		Sleep(100);
	}
	bool accepted = false;
	for (auto &e : machine.AcceptState)
		if (machine.Names[state] == e)
			accepted = true;
	
	return accepted;
}
bool fileExists(string &filename)
{
	FILE *f = fopen(filename.c_str(), "r");
	if (f == NULL)
		return false;
	fclose(f);
	return true;
}
void Load(Graph &machine, int &status)
{
	string filename;
	cout << "File name: ";
	cin >> filename;
	if (!fileExists(filename))
	{
		status = 1;
		return;
	}
	ifstream ifs(filename);
	string input, input2;

	ifs >> input >> input2;
	if (ifs.eof())
		return;
	while(input != "#")
	{
		machine.AddVertex(input, String_to_Bool(input2));
		ifs >> input >> input2;
	}
	Slot s;
	ifs >> input >> input2 >> s.read >> s.write >> s.direction;
	while (!ifs.eof())
	{
		machine.AddEdge(input, input2, s);
		ifs >> input >> input2 >> s.read >> s.write >> s.direction;
	}
	status = 0;
	return;
}

void Save(Graph &machine, int &status)
{
	string filename;
	ofstream ofs;
	cout << "New file name: ";
	cin >> filename;
	ofs.open(filename, ofstream::out | ofstream::trunc);
	for (auto &e : machine.Names)
		for (auto &f : machine.AcceptState)
			if (e == f)
				ofs << e << " Yes\n";
			else
				ofs << e << " No\n";
	ofs << "# #\n";
	for (auto &e : machine.Vertices)
		for (auto &f : e)
			ofs << f.src << " " << f.dest << " " << f.s.read << " " << f.s.write << " " << f.s.direction << "\n";
	status = 0;
	return;
}
void printMenu(vector<string> &status, int &statusindex)
{
	
	cout << "1] New machine:"  << endl;
	cout << "2] Open file:"    << endl;
	cout << "3] Save machine:" << endl;
	cout << "4] Input string"  << endl;
	cout << "5] Exit"          << endl;
	if (statusindex < 0 || statusindex >= status.size())
		statusindex = 4;
	cout << "Status >> " << status[statusindex] << endl;
	return;
}
void useMachine(Graph &machine)
{
	string inputstring;
	cout << "Enter input string: ";
	cin >> inputstring;
	while (inputstring != "#")
	{
		parseString(machine, inputstring) ? cout << inputstring << " : is in the lanuage" : cout << inputstring << " : is not in the language";
		cout << endl;
		cout << "Enter new input string: ";
		cin >> inputstring;
	}
	return;
}
bool fileExists(string &filename);
int main()
{
	vector<string> status;
	int statusindex = 2;
	status.push_back("Success");
	status.push_back("File not found");
	status.push_back("none");
	status.push_back("No machine loaded");
	status.push_back("Error");
	Slot s;
	Graph machine;
	string inputstring;
	int input;
	bool loaded = false;

	printMenu(status, statusindex);
	cin >> input;
	while (input != 5)
	{
		switch (input)
		{
		case 1:
			//config
			readStates(machine);
			readEdges(machine);
			loaded = true;
			statusindex = 2;
			break;
		case 2:
			Load(machine, statusindex);
			loaded = true;
			break;
		case 3:
			if (loaded)
				Save(machine, statusindex);
			else
				statusindex = 3;
			break;
		case 4:
			if (loaded)
				useMachine(machine);
			else
				statusindex = 3;
			break;
		case 5:
			exit(0);
		}
		system("cls");
		printMenu(status, statusindex);
		cin >> input;
	}
    return 0;
}

