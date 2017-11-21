#include <vector>
#include <list>
#include <string>
#include "Slot.h"
#include "Graph.h"
#include "Node.h"
#include <iostream>


Graph::Graph()
{
	nvertices = 0;
	nedges = 0;
}
Graph::~Graph()
{
	while (!Vertices.empty())
	{
		//for (auto &e : Vertices)
		//{
		//	e.pop_front();
		//}
		Vertices.pop_back();
	}
}
bool Graph::AddVertex(string &s, bool accept)
{
	list<Node> l;

	for (string &str : Names)
		if (s == str)
			return false;

	if (accept)	AcceptState.push_back(s);
	Names.push_back(s);
	Vertices.push_back(l);

	++nvertices;
	return true;
}
int Graph::NameIndex(string &str)
{
	for (int i = 0; i < Names.size(); ++i)
		if (Names[i] == str)
			return i;

	return -1;
}
bool Graph::Contains(string &str)
{
	for (auto &e : Names)
		if (e == str)
			return true;
	return false;
}
bool Graph::AddEdge(string &src, string &dest, Slot &s)
{
	int i = NameIndex(src);
	if (i == -1)	return false;

	auto e = find(Names.begin(), Names.end(), src);
	auto f = find(Names.begin(), Names.end(), dest);
	if (e == Names.end() || f == Names.end())
		return false;
	Node n;
	n.src = src;
	n.dest = dest;
	n.s = s;
	Vertices[i].push_front(n);

	++nedges;
	return true;
}
list<Node> Graph::getNeighbors(string &vertex)
{
	list<Node> neighbors;
	int index = NameIndex(vertex);
	if (index == -1)
		return neighbors;

	for (auto &e : Vertices[index])
		if (e.src == vertex)
			neighbors.push_back(e);
	return neighbors;
}
Node Graph::nextVertex(char &input, int current)
{
	Node n;
	n.src = "-";
	n.dest = "-";
	n.s.read = '-';
	n.s.write = '-';
	n.s.direction = '-';
	list<Node> neighbors = getNeighbors(Names[current]);
	for (auto &e : neighbors)
		if (e.s.read == input)
			return e;
	return n;
	// get the neighbors
	// test input against each edge to see which vertex is next
}
list<Node> Graph::getEdge(string &src, string &dest)
{
	list<Node> edgelist;
	int s, d;
	s = NameIndex(src);
	d = NameIndex(dest);
	if (s == -1 || d == -1)
		return edgelist;
	else
	{
		int size = Vertices.size();
		for (int i = 0; i < size; ++i)
			for (auto &e : Vertices[i])
				if (e.src == src && e.dest == dest)
					edgelist.push_back(e);
		return edgelist;
	}
}
void Graph::setDescription(string &str)
{
	description = str;
	return;
}
void Graph::print()
{
	for (int i = 0; i < Vertices.size(); ++i)
	{
		cout << Names[i] << ": ";
		for (auto &e : Vertices[i])
		{
			cout << "(" << e.src << ", " << e.dest << ", " << e.s.read << " " << e.s.write << " " << e.s.direction << ")";
		}
		cout << endl;
	}
}
