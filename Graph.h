#ifndef GRAPH_H
#define GRAPH_H
#include <iostream>
#include <vector>
#include <ctime>
#include <queue>
#include <stack>
#include <iostream>
#include <bits/stdc++.h>

using namespace std;

class Graph
{
    int V;
    vector <pair<int, int> >* adj1;
    vector <pair<int, int> >* transpose;
    bool isCyclicUtil(vector<pair<int, int> > adj1[], int v, bool visited[], bool* rs);
public:
    Graph(int V);
    void addEdge(vector<pair<int, int> > adj1[], int v, int w, int wt);
    bool isCyclic(vector<pair<int, int> > adj1[]);
    void randEdges(int V, vector<pair<int, int> > adj1[]);
    bool isAvailable(int& v1, int& v2);
    void PrintGraph(vector<pair<int, int> > adj1[], int V);
    void initialize(Graph& g, vector<pair<int, int> > adj1[]);
    void clear(vector<pair<int, int> > adj1[], int V);
};

Graph::Graph(int V)
{
    this->V = V;
    adj1 = new vector< pair<int, int> >;
    //adj=new list<int>[V];
}

void Graph::addEdge(vector<pair<int, int> > adj1[], int v, int w, int wt)
{
    adj1[v].push_back(make_pair(w, wt));
}

bool Graph::isCyclicUtil(vector<pair<int, int> > adj1[], int v, bool visited[], bool* recStack)
{
    if (visited[v] == false)
    {
        visited[v] = true;
        recStack[v] = true;

        vector<pair<int, int> >::iterator i;
        for (i = adj1[v].begin(); i != adj1[v].end(); ++i)
        {
            if (!visited[(*i).first] && isCyclicUtil(adj1, (*i).first, visited, recStack))
                return true;
            else if (recStack[(*i).first])
                return true;
        }

    }
    recStack[v] = false;
    return false;
}

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

bool Graph::isAvailable(int& v1, int& v2) {
    for (auto it = adj1[v1].begin(); it != adj1[v1].end(); it++) {
        int v = it->first;
        if (v2 == v) {
            return true;
        }
        return false;
    }
}

void Graph::randEdges(int V, vector<pair<int, int> > adj1[]) {
    int wt[5][5] = {
    {0,3383,3315,16659,6390},
    {3383,0,1984,16579,5849},
    {3315,1984,0,15010,3964},
    {16659,16570,15010,0,11090},
    {6390,5849,3964,11090,0} };
    int v1;
    int v2;
    //srand(time(0));
    v1 = rand() % V;
    v2 = rand() % V;
    while (v1 == v2 || isAvailable(v1, v2)) {
        v1 = rand() % V;
        v2 = rand() % V;
    }
    int Temp_Weight = wt[v1][v2];
    addEdge(adj1, v1, v2, Temp_Weight);
    cout << "EDGE " << v1 << v2 << " IS CREATED " << endl << endl;
}

void Graph::PrintGraph(vector<pair<int, int> > adj1[], int V)
{
    int v, w;
    cout << "\nPrint Graph (Adjacency List): " << endl;
    for (int u = 0; u < V; u++)
    {
        for (auto it = adj1[u].begin(); it != adj1[u].end(); it++)
        {
            v = it->first;
            w = it->second;
            cout << "(" << u << ", ";
            cout << v << ", "
                << w << ")\t";
        }
        cout << "\n\n";
    }
}

void Graph::initialize(Graph& g, vector<pair<int, int> > adj1[])
{
    g.addEdge(adj1, 1, 0, 3383);
    g.addEdge(adj1, 4, 0, 6390);
    g.addEdge(adj1, 1, 2, 1984);
    g.addEdge(adj1, 2, 3, 15010);
    g.addEdge(adj1, 3, 4, 11090);
}

void Graph::clear(vector<pair<int, int> > adj1[], int V)
{

    for (int i = 0; i < V; i++)
        adj1[i].clear();
}

#endif
