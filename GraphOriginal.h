#pragma once
#ifndef GRAPHSENIOR_H
#define GRAPHSENIOR_H
#include <bits/stdc++.h>

using namespace std;

class Graph
{
    int V;
    vector <pair<int, int> >* adj1;
    vector <pair<int, int> >* transpose; // for checking strongly connected components function
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

Graph::Graph(int v)
{
    this->V = v;
    adj1 = new vector< pair<int, int> >;
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
/*
 srand(time(0));
    Graph g(5);
    vector<pair<int, int> > adj[5];
    vector<pair<int, int> > transpose[5];
    int weight[5][5] = {
    {0,3383,3315,16659,6390},
    {3383,0,1984,16579,5849},
    {3315,1984,0,15010,3964},
    {16659,16570,15010,0,11090},
    {6390,5849,3964,11090,0} };
    int option;

    g.initialize(g, adj);
    cout << "GRAPH HAS BEEN INITIALIZED..." << endl << endl;

    do {
        cout << "PRESS 1 TO PRINT GRAPH" << endl;
        cout << "PRESS 2 TO ADD EDGES" << endl;
        cout << "PRESS 3 TO REMOVE EDGES" << endl;
        cout << "PRESS 4 TO CHECK IF GRAPH IS STRONGLY CONNECTED" << endl;
        cout << "PRESS 5 TO DETECT CYCLE IN GRAPH" << endl;
        cout << "PRESS 6 TO FIND SHORTEST PATH BETWEEN 2 VERTEX" << endl;
        cout << "PRESS 7 TO FIND MINIMUM SPANNING TREE" << endl;
        cout << "PRESS 8 TO RESET TO DEFAULT GRAPH" << endl;
        cout << "PRESS 9 TO EXIT" << endl << endl;
        cin >> option; cin.ignore();

        switch (option) {
        case 1:
            g.PrintGraph(adj, 5);
            break;

        case 2:
            int v1, v2, wt;
            cout << "0 - HELSINKI" << endl << "1 - CAIRO" << endl << "2 - TEHRAN" << endl << "3 - AUCKLAND" << endl << "4 - DHAKA" << endl;
            cout << "ENTER VERTEX 1: "; cin >> v1; cin.ignore();
            while (v1 > 5 || v1 < 0) {
                cout << "PLEASE ENTER THE CORRECT CODE FOR THE COUNTRY!!!" << endl;
                cout << "0 - HELSINKI" << endl << "1 - CAIRO" << endl << "2 - TEHRAN" << endl << "3 - AUCKLAND" << endl << "4 - DHAKA" << endl;
                cin >> v1; cin.ignore();
            }
            cout << "ENTER VERTEX 2: "; cin >> v2; cin.ignore();
            while (v2 > 5 || v2 < 0) {
                cout << "PLEASE ENTER THE CORRECT CODE FOR THE COUNTRY!!!" << endl;
                cout << "0 - HELSINKI" << endl << "1 - CAIRO" << endl << "2 - TEHRAN" << endl << "3 - AUCKLAND" << endl << "4 - DHAKA" << endl;
                cin >> v1; cin.ignore();
            }
            wt = weight[v1][v2];
            g.addEdge(adj, v1, v2, wt);

        case 3:

        case 4:


        case 5:
            if (g.isCyclic(adj))
                cout << "CYCLE DETECTED" << endl;
            else
                cout << "NO CYCLE DETECTED" << endl << endl;
            while (!g.isCyclic(adj)) {
                g.randEdges(5, adj);
                if (g.isCyclic(adj))
                    cout << "CYCLE CREATED !!!" << endl;
            }
            g.PrintGraph(adj, 5);
            cout << endl;
            break;

        case 6:


        case 7:

        case 8:
            g.clear(adj, 5);
            g.initialize(g, adj);
            cout << "GRAPH HAS BEEN RESET TO DEFAULT \n";
            cout << endl;
            break;

        case 9:
            cout << "THANK YOU AND COME AGAIN" << endl;
            break;

        default:
            cout << "INVALID CHOICE!!!" << endl << "PLEASE PRESS AGAIN. " << endl;
        }
    } while (option != 9);

*/