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
    //initalize graph
    Graph g(5);
    vector<pair<int, int>> adj[5];
    vector<pair<int, int>> transpose[5];
    int weight[5][5] = 
    {
        {0,3383,3315,16659,6390},       //Depart: HE; Destination: HE,CA,TE,AU,DH
        {3383,0,1984,16579,5849},       //Depart: CA; Destination: HE,CA,TE,AU,DH
        {3315,1984,0,15010,3964},       //Depart: TE; Destination: HE,CA,TE,AU,DH
        {16659,16570,15010,0,11090},    //Depart: AU; Destination: HE,CA,TE,AU,DH
        {6390,5849,3964,11090,0}        //Depart: DH; Destination: HE,CA,TE,AU,DH
    };

    // map declaration
    map<int,string> citiesName;

    // mapping integers to city name
    /*
    	HE,Helsinki, Finland is 0
	    CA,Cairo, Egypt is 1
	    TE,Tehran, Iran is 2
	    AU, Auckland, New Zealand is 3
	    DH,Dhaka, Bangladesh is 4
    */
    citiesName[0] = "HE";
    citiesName[1] = "CA";
    citiesName[2] = "TE";
    citiesName[3] = "AU";
    citiesName[4] = "DH";
   


    g.initialize();
    cout << "The graph has been initialized\n";
    
    int option = 0;
    bool SCCheck;
    bool cycle;
	
    do
    {
        system("cls");
        cout << "Graph Algorithm\n\n";
        cout << "We have 5 cities in our graph which are:\n";
        cout << "HE -> Helsinki, Finland is 0\n";
        cout << "CA -> Cairo, Egypt is 1\n";
        cout << "TE -> Tehran, Iranis 2\n";
        cout << "AU -> Auckland, New Zealand is 3\n";
        cout << "DH -> Dhaka, Bangladesh is 4\n\n\n";

        cout << "Please choose 1 option below:\n";
        cout << "========================================\n";
        cout << "Press 1 to print graph\n";
        cout << "Press 2 to check whether the graph is strongly connected\n";
        cout << "Press 3 to detect cycle in the graph\n";
        cout << "Press 4 to find the shortest path between 2 vertex in the graph\n";
        cout << "Press 5 to find the minimum spanning tree in the graph according to the vertex chosen\n";
        cout << "Press 6 to reset to default graph\n";
        cout << "Press 7 to add new edges to the graph\n";
        cout << "Press 8 to remove edges from the graph\n";
        cout << "Press 9 to exit the program\n\n";

        cout << "Your choice: ";
        cin >> option;
        cin.ignore();

        switch (option)
        {
        case 1:
            g.PrintGraph(citiesName);
            system("pause");
            break;
        case 2:
            //check whether the graph is strongly connected
            cout << "***************************************************************" << endl;
            cout << "*           Function 1: Connectivity of Graph Detection       *" << endl;
            cout << "***************************************************************" << endl;
            SCCheck = g.isStronglyConnected(adj, transpose, 5);
            if (g.isStronglyConnected(adj, transpose, 5) == true)
                cout << "THE GRAPH IS STRONGLY CONNECTED" << endl;
            else {
                cout << "THE GRAPH IS NOT STRONGLY CONNECTED" << endl << endl;

                while (SCCheck == false)
                {
                    g.generateRandEdges();
                    cout << "\nModified Graph: " << endl;
                    cout << "***************************************************************" << endl;
                    g.PrintGraph(citiesName);
                    cout << "***************************************************************" << endl;
                    system("pause");
                    SCCheck = g.isStronglyConnected(adj, transpose, 5);
                    if (SCCheck == true)
                        cout << "\n\nTHE GRAPH IS STRONGLY CONNECTED" << endl;
                    else
                        cout << "\n\nTHE GRAPH IS NOT STRONGLY CONNECTED" << endl;
                }
            }
            g.minimumEdges(adj, transpose, 5);
            g.PrintGraph(citiesName);
            system("pause");
        case 2:
            //check whether the graph is strongly connected
            system("pause");
            break;
       case 3:
            // detect cycle in the graph
            // Cycle Detection Section
            cout << "***************************************************************" << endl;
            cout << "*                 Function 2: Cycle  Detection                *" << endl;
            cout << "***************************************************************" << endl;
            cycle = g.isCyclic(adj);

            if (cycle == true)
                cout << "CYCLE DETECTED" << endl;
	        else {
		        cout << "NO CYCLE DETECTED" << endl << endl;

                while (cycle == false)
                {
                    g.generateRandEdges();
                    cout << "Modified Graph: " << endl;
                    cout << "***************************************************************" << endl;
                    g.PrintGraph(citiesName);
                    cout << "***************************************************************" << endl;
                    cycle = g.isCyclic(adj);
                    if (cycle == true)
                        cout << "CYCLE DETECTED! " << endl << endl;
                    else
                        cout << "NO CYCLE DETECTED." << endl << endl;
                }
            }
	        system("pause");
	        break;
        case 4:
            //find the shortest path between 2 vertex in the graph
            // Shortest Path Section
            cout << "***************************************************************" << endl;
            cout << "*      Function 3: Shortest Path Between 2 Locations          *" << endl;
            cout << "***************************************************************" << endl;
            g.dijkstra(citiesName);
            cout << "\n\nLatest graph is as follows: " << endl;
            g.PrintGraph(citiesName);
            system("pause");
            break;
        case 5:
            //find the minimum spanning tree in the graph according to the vertex chosen
            system("pause");
            break;
        case 6:
            // reset to default graph
	        g.clear(5);
            g.initialize();
            cout << "GRAPH HAS BEEN RESET TO DEFAULT \n";
            cout << endl;
            system("pause");
            break;
        case 7:
            //add new edges to the graph
            int v1, v2, wt;
            cout << "***************************************************************" << endl;
            cout << "*                      Add New Edges                          *" << endl;
            cout << "***************************************************************" << endl  << endl;
            cout << "0: HE -> Helsinki, Finland \n";
            cout << "1: CA -> Cairo, Egypt \n";
            cout << "2: TE -> Tehran, Iran\n";
            cout << "3: AU -> Auckland, New Zealand \n";
            cout << "4: DH -> Dhaka, Bangladesh \n";
            cout << "Select the first Vertex: ";
            cin >> v1; cin.ignore();

            while (v1 > 4 || v1 < 0) {
                cout << "\n\nPlease select the correct country code!" << endl;
                cout << "0: HE -> Helsinki, Finland \n";
                cout << "1: CA -> Cairo, Egypt \n";
                cout << "2: TE -> Tehran, Iran\n";
                cout << "3: AU -> Auckland, New Zealand \n";
                cout << "4: DH -> Dhaka, Bangladesh \n";
                cin >> v1; cin.ignore();
            }

            cout << "\n0: HE -> Helsinki, Finland \n";
            cout << "1: CA -> Cairo, Egypt \n";
            cout << "2: TE -> Tehran, Iran\n";
            cout << "3: AU -> Auckland, New Zealand \n";
            cout << "4: DH -> Dhaka, Bangladesh \n";
            cout << "Select the second Vertex: ";
            cin >> v2; cin.ignore();

            while (v2 > 4 || v2 < 0) {
                cout << "Please select the correct country code!" << endl;
                cout << "0: HE -> Helsinki, Finland \n";
                cout << "1: CA -> Cairo, Egypt \n";
                cout << "2: TE -> Tehran, Iran\n";
                cout << "3: AU -> Auckland, New Zealand \n";
                cout << "4: DH -> Dhaka, Bangladesh \n";
                cin >> v2; cin.ignore();
            }

            wt = weight[v1][v2];
            g.addEdge(v1, v2, wt);
            system("pause");
            break;
        case 8:
            //remove edges from the graph
            system("pause");
            break;
        case 9:
            //exit the program
            cout << "Thank you for using this program\n";
            system("pause");
            break;
        default:
            cout << "Invalid choice!\n";
            cout << "Please make sure you choose the number between 1 to 9\n";
            system("pause");
        }

    } while (option!= 9);



    return 0;
}

