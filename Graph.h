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
		{3383,0,1984,16570,5849},       //Depart: CA; Destination: HE,CA,TE,AU,DH
		{3315,1984,0,15010,3964},       //Depart: TE; Destination: HE,CA,TE,AU,DH
		{16659,16570,15010,0,11090},    //Depart: AU; Destination: HE,CA,TE,AU,DH
		{6390,5849,3964,11090,0}        //Depart: DH; Destination: HE,CA,TE,AU,DH
	};
	vector <pair<int, int>>* adj; // the adjacency list pointer
	bool isCyclicUtil(vector<pair<int, int> > adj[], int v, bool visited[], bool* rs); // check the graph is cyclic or not
public:
	Graph(int v);
	void addEdge(int u, int v, int weight, bool undir = false);
	void removeEdge(int u, int v, map<int, string> cityName);
	void initialize();
	void clear(int V);
	void PrintGraph(map<int,string> cityName);
	bool isCyclic(vector<pair<int, int> > adj1[]);
	void generateRandEdges(map<int, string> cityName);
	void generateRandEdgesUndirected(map<int, string> cityName);
	bool isAvailableEdge(int start, int end);
	bool isReachable(int start, int end);
	void dijkstra(map<int, string> cityName);
	Graph getTranspose();
	bool isStronglyConnected();
	void DFS(int v, bool* visited);
	void prim_jarnik_mst(map<int, string> cityWeight);
};


Graph::Graph(int v)
{
	this->V = v;
	adj = new vector< pair<int, int> > [V]; // create new node 
}

void Graph::addEdge(int u, int v, int weight, bool undir)
{
	adj[u].push_back(make_pair(v, weight)); // for directed graph
	if (undir)
	{
		adj[v].push_back(make_pair(u, weight)); // for undirected graph
	}
}



// A utility function to delete an edge in an undirected graph.
void Graph::removeEdge(int u, int v, map<int, string> cityName)
{
	for (auto i = adj[u].begin(); i < adj[u].end(); i++) {
		if (i->first == v) {
			adj[u].erase(i);
			cout << "\nEdge between " << cityName[u] << " and " << cityName[v] << " is deleted" << endl << endl;
			break;
		}
	}
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
	*/
	addEdge(1, 0, 3383);
	addEdge(1, 2, 1984);
	addEdge(2, 3, 15010);
	addEdge(3, 4, 11090);
	addEdge(4, 0, 6390);
}

void Graph::clear(int V)
{

	for (int i = 0; i < V; i++)
		adj[i].clear();
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


bool Graph::isCyclicUtil(vector<pair<int, int> > adj1[], int v, bool visited[], bool* recStack)
{
	if (visited[v] == false)
	{
		// Mark the current node as visited and part of recursion stack
		visited[v] = true;
		recStack[v] = true;

		// Recur for all the vertices adjacent to this vertex
		vector<pair<int, int> >::iterator i;
		for (i = adj[v].begin(); i != adj[v].end(); ++i)
		{
			if (!visited[(*i).first] && isCyclicUtil(adj1, (*i).first, visited, recStack))
				return true;
			else if (recStack[(*i).first])
				return true;
		}

	}
	recStack[v] = false;  // remove the vertex from recursion stack
	return false;
}

// returns true if the graph contains a cycle
bool Graph::isCyclic(vector<pair<int, int> > adj1[])
{
	bool* visited = new bool[V];
	bool* recStack = new bool[V];
	for (int i = 0; i < V; i++)
	{
		visited[i] = false;
		recStack[i] = false;
	}

	for (int i = 0; i < V; i++)
		if (isCyclicUtil(adj1, i, visited, recStack))
			return true;

	return false;
}

// returns true if the path is in the adjacency list, else returns false
bool Graph::isAvailableEdge(int start, int end) {
	for (auto i = adj[start].begin(); i != adj[start].end(); i++) {
		if (i->first == end) {
			return true;
		}
	}
	return false;
}

void Graph::generateRandEdges(map<int, string> cityName) {

	int rand_start = 0, rand_end = 0;

	// generate random seed
	srand(time(0));

	// if both location is same or exist in the original graph, repeat till new unique edge
	while (rand_start == rand_end || isAvailableEdge(rand_start, rand_end)) {
		rand_start = rand() % V;
		rand_end = rand() % V;
	}

	addEdge(rand_start, rand_end, weight[rand_start][rand_end]);
	cout << "Edge between " << cityName[rand_start] << " and " << cityName[rand_end] << " is created" << endl << endl;
}

void Graph::generateRandEdgesUndirected(map<int, string> cityName)
{
	int rand_start = 0, rand_end = 0;

	// generate random seed
	srand(time(0));

	// if both location is same or exist in the original graph, repeat till new unique edge
	while (rand_start == rand_end || isAvailableEdge(rand_start, rand_end)) {
		rand_start = rand() % V;
		rand_end = rand() % V;
	}

	addEdge(rand_start, rand_end, weight[rand_start][rand_end], true); // for undirected graph
	cout << "Edge between " << cityName[rand_start] << " and " << cityName[rand_end] << " is created" << endl << endl;
}

//This function is to get the transpose graph (Graph with edges reversed)
Graph Graph::getTranspose() {
	Graph gt(V);	
	for (int v = 0; v < V; v++){
		for (int j = 0; j < adj[v].size(); j++)
			//Make sure is starting point and ending point reverse
			gt.addEdge(adj[v][j].first, v, weight[adj[v][j].first][v]);
	}
	return gt;
}

//This function is to perfrom DFS starting from v
void Graph::DFS(int v, bool* visited)
{
	//Mark the current node as visited and print it
	visited[v] = true;

	//Repeat for all the vertices adjacent to this vertex
	for (auto i = adj[v].begin(); i != adj[v].end(); ++i)
		if (!visited[i->first])
			DFS(i->first, visited);
}

//This function is determining the connectivity and returns true if the graph is strongly connected
bool Graph::isStronglyConnected()
{
	//Step 1: Mark all the vertices as not visited (It is for first DFS)
	bool* visited = new bool[V];
	for (int i = 0; i < V; i++) {
		visited[i] = false;
	}

	//Step 2: Perform DFS traversal starting from the first vertex.
	DFS(0, visited);
	//If DFS traversal doesn???t visit all vertices, then return false.
	for (int i = 0; i < V; i++) 
	{
		if (visited[i] == false)
			return false;
	}
	
	//Step 3: Create a reversed graph
	Graph gt(V); 
	gt = getTranspose();

	//Step 4: Mark all the vertices as not visited (It is for second DFS)
	for (int i = 0; i < V; i++) 
	{
		visited[i] = false;
	}

	//Step 5: Perform DFS traversal for reversed graph starting from first vertex.
	//Staring Vertex must be same starting point of first DFS
	gt.DFS(0, visited);
	//If all vertices are not visited in second DFS, then return false.
	for (int i = 0; i < V; i++) 
	{
		if (visited[i] == false)
			return false;
	}
	return true;
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
	unordered_map<int,int> previous_points;
	deque<int> path;
	int start = 0, end = 0;

	// request for inputs
	cout << "\nPlease select the correct starting country code: ";
	cin >> start;
	// since we only have 5 locations, hence only allow between 0 - 4
	while (start < 0 || start > 4) {
		cout << "Invalid input. Please key in values range in 0 to 4: ";
		cin >> start;
	}
	cout << "Please select the correct ending country code: ";
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
		generateRandEdges(cityName);
		count++;
		system("pause");
	}

	if (count != 0) {
		cout << count << " path(s) are generated randomly." << endl;
	}

	// initialise the starting node
	distance[start] = 0;
	tracker.insert(make_pair(start, 0));

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
				}

				// insert the updated values with the new distance
				distance[nbr_pos] = cumulated_dist + current_edge;
				tracker.insert(make_pair(nbr_pos, distance[nbr_pos]));
				previous_points[nbr_pos] = pos;
			}
		}

	}

	// trace back the shortest path
	int currentLocation = end;
	while(currentLocation != start){
		path.push_front(currentLocation);
		currentLocation = previous_points[currentLocation];
	}
	path.push_front(start);

	// print out the shortest path
	cout << "\nShortest path: ";
	for (auto location : path) {
		cout << cityName.at(location) << "\t";
	}
	cout << endl;

	// print out the shortest distance
	cout << "Shortest path distance: " << distance[end] << endl;
	
}

//Function 4: minimum spanning tree using prim-Jarnik algorithm
//for this function, we need to use undirected graph
void Graph::prim_jarnik_mst(map<int, string> cityWeight)
{
	cout << "The minimum spanning tree is: " << endl;
	// Initialize a minimum Heap
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> Q;

	// create another array
	// this array is visited array that denotes whether a node has been included in minimum spanning tree or not
	bool* vis = new bool[V] {0};
	int ans = 0;

	Q.push({ 0, 0 }); // the weight and the node

	while (!Q.empty())
	{
		// pick out the edge that have minimum weight
		auto best = Q.top();
		Q.pop();
		int to = best.second;
		int weight = best.first;

		if (vis[to])
		{
			// if it is visited, then discard the edge, and continue
			continue;
		}

		if (weight != 0)
		{
			cout << "( " << cityWeight[weight] << " , " << weight << " )" << endl; // display the edge of the minimum spanning tree together with the weight
		}

		// if it is not visited,  take the current edge and add the current weight
		ans += weight;
		vis[to] = 1;

		// add the new edges in the queue
		for (auto x : adj[to])
		{

			if (vis[x.first] == 0)
			{
				Q.push({ x.second, x.first });
			}
		}
	}
	//display the total weight for the minimum spanning tree
	cout << "Total Weight: " << ans << endl;
}
#endif
