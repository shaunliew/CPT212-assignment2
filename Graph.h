#pragma once
#ifndef GRAPH_H
#define GRAPH_H
#include <bits/stdc++.h>
#include<unordered_map>
#include <queue>
using namespace std;

class Graph
{
	int V; // vertices
	vector <pair<int, int>>* adj; // the adjacency list pointer
	vector <pair<int, int>>* transpose; // the transposed adjacency list pointer for validating strong connected components
	//bool isCyclicUtil(vector<pair<int, int> > adj[], int v, bool visited[], bool* rs); // check the graph is cyclic or not
public:
	Graph(int V); 
	void addEdge(vector<pair<int, int> > adj[], int u, int v, int weight);
	void initialize(Graph& g, vector<pair<int, int> > adj[]);
	void PrintGraph(vector<pair<int, int> > adj[], int V, map<int,string> cityName);
};


Graph::Graph(int v)
{
	this->V = v;
	adj = new vector< pair<int, int> >; // create new node 
}

void Graph::addEdge(vector<pair<int, int>> adj[], int u, int v, int weight)
{
	adj[u].push_back(make_pair(v, weight)); // for directed graph
}

void Graph::initialize(Graph& g, vector<pair<int, int> > adj[])
{
	/*
	assume that
	HE,Helsinki, Finland is 0
	CA,Cairo, Egypt is 1
	TE,Tehran, Iran is 2
	AU, Auckland, New Zealand is 3
	DH,Dhaka, Bangladesh is 4
	initialize according to the diagram , refer to CPT_212_CITY.png
	first agrument is the depart , second is destination, third arguement is the weight of the weight edges
	g.addEdge("Cairo, Egypt", "Helsinki, Finland", 3383);
	g.addEdge("Cairo, Egypt", "Tehran, Iran", 1984);
	g.addEdge("Tehran, Iran", "Auckland, New Zealand", 15010);
	g.addEdge("Auckland, New Zealand", "Dhaka, Bangladesh", 11090);
	g.addEdge("Dhaka, Bangladesh", "Helsinki, Finland", 6390);
	*/
	g.addEdge(adj, 1, 0, 3383);
	g.addEdge(adj, 1, 2, 1984);
	g.addEdge(adj, 2, 3, 15010);
	g.addEdge(adj, 3, 4, 11090);
	g.addEdge(adj, 4, 0, 6390);
}

void Graph::PrintGraph(vector<pair<int, int> > adj[], int V, map<int,string> cityName)
{
	int v, w;
	cout << "\nPrint Graph (Adjacency List): " << endl;
	cout << "Vertex --> Incidence Collection\n";
	cout << "-------------------------------\n";
	for (int u = 0; u < V; u++)
	{
		cout << cityName.at(u) << "-->";
		for (auto it = adj[u].begin(); it != adj[u].end(); it++)
		{
			v = it->first;
			w = it->second;
			cout << " (" << cityName.at(v) << ", ";
			cout << w << "), ";
		}
		cout << "\n\n";
	}
}
#endif