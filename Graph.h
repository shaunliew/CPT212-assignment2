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
	int weight[5][5] =
	{
		{0,3383,3315,16659,6390},       //Depart: HE; Destination: HE,CA,TE,AU,DH
		{3383,0,1984,16579,5849},       //Depart: CA; Destination: HE,CA,TE,AU,DH
		{3315,1984,0,15010,3964},       //Depart: TE; Destination: HE,CA,TE,AU,DH
		{16659,16570,15010,0,11090},    //Depart: AU; Destination: HE,CA,TE,AU,DH
		{6390,5849,3964,11090,0}        //Depart: DH; Destination: HE,CA,TE,AU,DH
	};
	vector <pair<int, int>>* adj; // the adjacency list pointer
	vector <pair<int, int>>* transpose; // the transposed adjacency list pointer for validating strong connected components
	//bool isCyclicUtil(vector<pair<int, int> > adj[], int v, bool visited[], bool* rs); // check the graph is cyclic or not
public:
	Graph(int v); 
	void addEdge(int u, int v, int weight);
	void initialize();
	void PrintGraph(map<int,string> cityName);
	bool isAvailablePath(int start, int end);
	void generateRandEdges();
	bool isReachable(int start, int end);
	void dijkstra(map<int, string> cityName);
};


Graph::Graph(int v)
{
	this->V = v;
	adj = new vector< pair<int, int> > [V]; // create new node 
}

void Graph::addEdge(int u, int v, int weight)
{
	adj[u].push_back(make_pair(v, weight)); // for directed graph
}

void Graph::initialize()
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
	addEdge(1, 0, 3383);
	addEdge(1, 2, 1984);
	addEdge(2, 3, 15010);
	addEdge(3, 4, 11090);
	addEdge(4, 0, 6390);
}

void Graph::PrintGraph(map<int,string> cityName)
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

// returns true if the path is in the adjacency list, else returns false
bool Graph::isAvailablePath(int start, int end) {
	for (auto i = adj[start].begin(); i != adj[start].end(); i++) {
		if (i->first == end) {
			return true;
		}
	}
	return false;
}

void Graph::generateRandEdges() {

	int rand_start = 0, rand_end = 0;

	// generate random seed
	srand(time(0));

	// if both location is same or exist in the original graph, repeat till new unique edge
	while (rand_start == rand_end || isAvailablePath(rand_start, rand_end)) {
		rand_start = rand() % V;
		rand_end = rand() % V;
	}

	addEdge(rand_start, rand_end, weight[rand_start][rand_end]);
	cout << "Edge between " << rand_start << " and " << rand_end << " is created" << endl << endl;
}

bool Graph::isReachable(int start, int end) {
	
	// Base case
	if (start == end) {
		return true;
	}

	// Mark all vertices as not visited
	bool* visited = new bool[V];
	for (int i = 0; i < V; i++) {
		visited[i] = false;
	}

	// Create a stack for BFS
	stack<int> visits;

	// mark the current node as visited and push it
	visited[start] = true;
	visits.push(start);

	while (!visits.empty()) {
		// pop the top stack
		int current = visits.top();
		visits.pop();

		// found the ending location
		if (current == end) {
			return true;
		}

		// visit each adjacent nodes of the current nodes
		for (auto i = adj[current].begin(); i != adj[current].end(); i++) {
			if (!visited[i->first]) {
				visited[i->first] = true;
				visits.push(i->first);
			}
		}

	}

	// if BFS is complete without visiting end
	return false;
	
}

void Graph::dijkstra(map<int, string> cityName) {
	
	// initialise data structures and variables
	vector<int> distance(V, INT_MAX); // initialise a vector with a size V with extremely large values as infinity
	set<pair<int, int>> tracker; // keep track of visited notes, <position,distance>
	vector<int> path;
	int start = 0, end = 0;

	// request for inputs
	cout << "\nPlease enter your starting location: ";
	cin >> start;
	// since we only have 5 locations, hence only allow between 0 - 4
	while (start < 0 || start > 4) {
		cout << "Invalid input. Please key in values range in 0 to 4: ";
		cin >> start;
	}
	cout << "Please enter your ending location: ";
	cin >> end;
	// only allow between 0 - 4 and must different location
	while ((end < 0 || end >4) || start == end) {
		cout << "Invalid input. Please key in values range in 0 to 4 and different from starting location: ";
		cin >> end;
	}

	// check if not reachable
	int count = 0;
	while(!isReachable(start, end)) {
		cout << "\nPath does not exist!" << endl;

		// generating random edges
		generateRandEdges();
		count++;
	}

	if (count != 0) {
		cout << count << " path(s) are generated randomly." << endl;
	}

	// initialise the starting node
	distance[start] = 0;
	tracker.insert(make_pair(start, 0));
	path.push_back(start);

	while (!tracker.empty()) {
		auto it = tracker.begin();
		int pos = it->first;
		int cumulated_dist = it->second;
		tracker.erase(it); // pop the initial one

		// iterate over the neighbours of the node (BFS)
		for (auto nbrNode : adj[pos]) {

			// store values
			int nbr_pos = nbrNode.first;
			int current_edge = nbrNode.second;

			// check distance and update distance, check in tracker set
			if (cumulated_dist + current_edge < distance[nbr_pos]) {
				
				// check whether neighbour is in the set
				auto found = tracker.find(make_pair(nbr_pos, distance[nbr_pos]));

				// remove if neighbour already exist in the set
				if (found != tracker.end()) {
					tracker.erase(found);
					auto pos_remove = find(path.begin(), path.end(), nbr_pos);
					path.erase(pos_remove);
				}

				// insert the updated values with the new distance
				distance[nbr_pos] = cumulated_dist + current_edge;
				tracker.insert(make_pair(nbr_pos, distance[nbr_pos]));
				path.push_back(nbr_pos);
			}
		}

	}

	// print out the shortest path
	cout << "\nShortest path: ";
	for (auto location : path) {
		cout << cityName.at(location) << "\t";
		if (location == end) {
			break;
		}
	}
	cout << endl;

	// print out the shortest distance
	cout << "Shortest path distance: " << distance[end] << endl;
	
}
#endif