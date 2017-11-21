/*
	Graph.h
	Michael Wilkie

	Graph class.
	Represented by vector of linked lists.
	vector<string> AcceptState is only part of the turing machine implementation of the program.

*/
#pragma once
#include <vector>
#include <list>
#include <string>
#include "Slot.h"
#include "Node.h"
using namespace std;
class Graph
{
public:
	vector<list<Node>> Vertices;
	vector<string> Names;
	vector<string> AcceptState;
	string description;
	int nvertices;
	int nedges;
	Graph();
	~Graph();
	bool Graph::Contains(string &str);
	list<Node> getNeighbors(string &vertex);
	list<Node> getEdge(string &src, string &dest);
	bool AddVertex(string &s, bool accept);
	int NameIndex(string &str);
	Node nextVertex(char &input, int current);
	bool AddEdge(string &src, string &dest, Slot &s);
	void setDescription(string &str);
	void print();
};
