// CPT212-assignment2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <bits/stdc++.h>
#include <ctime>
#include <vector>
#include "Graph.h"
using namespace std;

int main()
{
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

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
