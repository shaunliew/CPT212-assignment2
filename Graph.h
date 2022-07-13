#pragma once
#ifndef GRAPH_H
#define GRAPH_H
#include <bits/stdc++.h>
#include<unordered_map>
#include <queue>
using namespace std;

class Node
{
	public:
		string city;
		vector<pair<string, int>> nbrs;
	
		Node(string cityName)
		{
			this->city = cityName;
		}
};


class Graph
{
	unordered_map<string, Node*> m;

public:
	Graph(vector<string> cities)
	{
		for (auto city : cities) 
		{
			m[city] = new Node(city);
		} 
	}

	void addEdge(string x, string y, int weight)
	{
		m[x]->nbrs.push_back(make_pair(y, weight));
	}
	void printAdjList() 
	{
		for (auto cityPair : m) 
		{
			auto city = cityPair.first;
			Node* node = cityPair.second;
			cout << city << "-->";
			for (auto nbr : node->nbrs) 
			{

				cout << "( " << nbr.first << " , " << nbr.second << "), ";
			}
			cout << endl;
		}
	}
};

#endif