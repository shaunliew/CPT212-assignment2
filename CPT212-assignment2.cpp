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
    Graph undirected_g(5); // for minimum spanning tree
    vector<pair<int, int>> adj[5];
    vector<pair<int, int>> transpose[5];
    int weight[5][5] = 
    {
        {0,3383,3315,16659,6390},       //Depart: HE; Destination: HE,CA,TE,AU,DH
        {3383,0,1984,16570,5849},       //Depart: CA; Destination: HE,CA,TE,AU,DH
        {3315,1984,0,15010,3964},       //Depart: TE; Destination: HE,CA,TE,AU,DH
        {16659,16570,15010,0,11090},    //Depart: AU; Destination: HE,CA,TE,AU,DH
        {6390,5849,3964,11090,0}        //Depart: DH; Destination: HE,CA,TE,AU,DH
    };
    int v1 = 0, v2 = 0, wt = 0;

    //map declaration for cityWeight
    map<int, string> cityWeight =
    {
        {3383, "HE to CA"},
        {3315, "HE to TE"},
        {16659, "HE to AU"},
        {6390, "HE to DH"},
        {1984, "CA to TE"},
        {16570, "CA to AU"},
        {5849, "CA to DH"},
        {15010, "TE to AU"},
        {3964, "TE to DH"},
        {11090, "AU to DH"},
        {3964, "DH to TE"} 
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
        cout << "0: HE -> Helsinki, Finland \n";
        cout << "1: CA -> Cairo, Egypt \n";
        cout << "2: TE -> Tehran, Iran\n";
        cout << "3: AU -> Auckland, New Zealand \n";
        cout << "4: DH -> Dhaka, Bangladesh \n\n\n";

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
            //Check whether the graph is strongly connected
            cout << "***************************************************************" << endl;
            cout << "*           Function 1: Connectivity of Graph Detection       *" << endl;
            cout << "***************************************************************" << endl;
            SCCheck = g.isStronglyConnected();
            cout << "-----------------------AFTER DETECTING-------------------------" << endl;
            if (SCCheck == true)
                cout << "\nTHE GRAPH IS STRONGLY CONNECTED" << endl;
            else
            {
                cout << "\nTHE GRAPH IS NOT STRONGLY CONNECTED, RANDOM EDGES ARE GENERATED!" << endl;
                cout << "---------------------------------------------------------------" << endl << endl;
            }
            
            //Loop the process of adding random edges until the graph is strongly connected
            while (SCCheck == false)
            {
                g.generateRandEdges(citiesName);
                cout << "***************************************************************" << endl;
                cout << "*                      MODIFIED GRAPH:                        *" << endl;
                cout << "***************************************************************" << endl;
                g.PrintGraph(citiesName);
                
                SCCheck = g.isStronglyConnected();
                cout << "-----------------------DETECTING AGAIN-------------------------" << endl;
                if (SCCheck == true)
                    cout << "\nTHE GRAPH IS STRONGLY CONNECTED NOW!" << endl;
                else
                {
                    cout << "\nTHE GRAPH IS STILL NOT STRONGLY CONNECTED!" << endl;
                    cout << "PLS PROCEED WITH THE ADDING RANDOM EDGES PROCESS!" << endl;
                }
                system("pause");
                system("CLS");
            }
            cout << "***************************************************************" << endl;
            cout << "*                  STRONGLY CONNECTED GRAPH:                  *" << endl;
            cout << "***************************************************************" << endl;
            g.PrintGraph(citiesName);
            system("pause");
            break;
			
        case 3:
            // detect cycle in the graph
            // Cycle Detection Section
            cout << "***************************************************************" << endl;
            cout << "*                 Function 2: Cycle  Detection                *" << endl;
            cout << "***************************************************************" << endl;
            cycle = g.isCyclic(adj);
            cout << "-----------------------AFTER DETECTING-------------------------" << endl;

            if (cycle == true)
                cout << "CYCLE DETECTED!" << endl;
            else {
                cout << "NO CYCLE DETECTED! RANDOM EDGES ARE GENERATED." << endl << endl;

                while (cycle == false)
                {
                    g.generateRandEdges(citiesName);
                    cout << "***************************************************************" << endl;
                    cout << "*                      MODIFIED GRAPH:                        *" << endl;
                    cout << "***************************************************************" << endl;
                    g.PrintGraph(citiesName);

                    cycle = g.isCyclic(adj);
                    cout << "-----------------------DETECTING AGAIN-------------------------" << endl;
                    if (cycle == true)
                        cout << "CYCLE DETECTED! " << endl << endl;
                    else
                        cout << "NO CYCLE DETECTED." << endl << endl;
                    system("pause");
                    system("CLS");
                }
            }
            cout << "***************************************************************" << endl;
            cout << "*                  CYCLE DETECTION GRAPH                      *" << endl;
            cout << "***************************************************************" << endl;
            g.PrintGraph(citiesName);
            system("pause");
            break;
			
        case 4:
            //find the shortest path between 2 vertex in the graph
            // Shortest Path Section
            cout << "***************************************************************" << endl;
            cout << "*      Function 3: Shortest Path Between 2 Locations          *" << endl;
            cout << "***************************************************************" << endl;
            g.PrintGraph(citiesName);
            //show index with respective to the location
            cout << "***************************************************************" << endl;
            cout << "*                      Location                               *" << endl;
            cout << "*              0: HE -> Helsinki, Finland                     *" << endl;
            cout << "*              1: CA -> Cairo, Egypt                          *" << endl;
            cout << "*              2: TE -> Tehran, Iran                          *" << endl;
            cout << "*              3: AU -> Auckland, New Zealand                 *" << endl;
            cout << "*              4: DH -> Dhaka, Bangladesh                     *" << endl;
            cout << "***************************************************************" << endl << endl;
            g.dijkstra(citiesName);
            cout << "\n\nLatest graph is as follows: " << endl;
            g.PrintGraph(citiesName);
            system("pause");
            break;
			
        case 5:
            //find the minimum spanning tree in the graph according to the vertex chosen
            //create undirected graph just for this function
            system("cls");
            cout << "***************************************************************" << endl;
            cout << "*     Function 4: Minimum Spanning Tree for selected edges    *" << endl;
            cout << "***************************************************************" << endl << endl;
            undirected_g.clear(5);

            cout << "For this function 4, we need to use undirected graph to find minimum spanning tree\n\n";

            int start, end;
            bool breaker;
            breaker = false;
            while (!breaker)
            {
                    cout << "The current edges that we have:\n";
                    undirected_g.PrintGraph(citiesName);
                    cout << endl;
                    cout << "These are the cities available: " << endl;
                    cout << "0: HE -> Helsinki, Finland \n";
                    cout << "1: CA -> Cairo, Egypt \n";
                    cout << "2: TE -> Tehran, Iran\n";
                    cout << "3: AU -> Auckland, New Zealand \n";
                    cout << "4: DH -> Dhaka, Bangladesh \n";
                    cout << "Enter the start city code: ";
                    cin >> start;
                    cout << "Enter the end city code: ";
                    cin >> end;
                    if (start == end)
                    {
                        cout << "Start and end city cannot be the same" << endl;
                        system("pause");
                    }
                    else if (start < 0 || start > 4 || end < 0 || end > 4)
                    {
                        cout << "Invalid city code" << endl;
                        system("pause");
                    }
                    else
                    {
                        // need to make sure that we add the undirected edges
                        undirected_g.addEdge(start, end, weight[start][end], true);
                        cout << endl;
                        cout << "The edge is added successfully\n";
                        
                        char ch;
                        ch = 'z';
                        while (ch != 'n' && ch != 'y')
                        {
                            cout << "Do you wanna to add more edges? (y/n)\n";
                            cout << "Answer: ";
                            cin >> ch;
                            if (ch == 'n')
                            {
                                breaker = true;
                            }
                            else if (ch == 'y')
                            {
                                breaker = false;
                            }
                            else
                            {
                                cout << "Invalid Input. Please Try Again\n";
                            }
                        }
                    }
                    system("cls");
             }
            cout << endl;
            cout << endl;
            cout << "The current edges that we have:\n";
            undirected_g.PrintGraph(citiesName);
            if (!undirected_g.isStronglyConnected())
            {
                cout << "\n***************************************************************" << endl;
                cout << "This is impossible to form Minimum Spanning Tree with current edges\n";
                cout << "Will add random edges until a Minimum Spanning Tree is formed\n";
                cout << "***************************************************************" << endl;
                system("pause");
                cout << endl;
                cout << endl;
            }
            cout << "***************************************************************" << endl;
            while (!undirected_g.isStronglyConnected())
            {
                undirected_g.generateRandEdgesUndirected(citiesName);
            }
            cout << "***************************************************************" << endl;
            system("pause");
             
            //use these value to validate whether it produces MST or not
            //0,1
            //1,2
            //2,3
            //3,4
            //4,0
            cout << endl << endl;
            cout << "***************************************************************" << endl;
            undirected_g.prim_janik_mst(cityWeight);
            cout << "***************************************************************" << endl;
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
            cout << "***************************************************************" << endl;
            cout << "*                      Add New Edges                          *" << endl;
            cout << "*              0: HE -> Helsinki, Finland                     *" << endl;
            cout << "*              1: CA -> Cairo, Egypt                          *" << endl;
            cout << "*              2: TE -> Tehran, Iran                          *" << endl;
            cout << "*              3: AU -> Auckland, New Zealand                 *" << endl;
            cout << "*              4: DH -> Dhaka, Bangladesh                     *" << endl;
            cout << "***************************************************************" << endl  << endl;

            cout << "Select the first Vertex: ";
            cin >> v1; cin.ignore();
            while (v1 > 4 || v1 < 0) {
                cout << "\nError! Please select the correct country code: ";
                cin >> v1; cin.ignore();
            }

            cout << "\nSelect the second Vertex: ";
            cin >> v2; cin.ignore();

            while (v2 > 4 || v2 < 0) {
                cout << "\nError! Please select the correct country code: ";
                cin >> v2; cin.ignore();
            }

            wt = weight[v1][v2];
            g.addEdge(v1, v2, wt);

            system("pause");
            break;
			
        case 8:
            cout << "Current Graph: " << endl;
            cout << "***************************************************************" << endl;
            g.PrintGraph(citiesName);
            cout << "***************************************************************" << endl;

            //remove edges from the graph
            cout << "***************************************************************" << endl;
            cout << "*                      Remove Edges                           *" << endl;
            cout << "*              0: HE -> Helsinki, Finland                     *" << endl;
            cout << "*              1: CA -> Cairo, Egypt                          *" << endl;
            cout << "*              2: TE -> Tehran, Iran                          *" << endl;
            cout << "*              3: AU -> Auckland, New Zealand                 *" << endl;
            cout << "*              4: DH -> Dhaka, Bangladesh                     *" << endl;
            cout << "***************************************************************" << endl << endl;

            // validate whether the edge exist in the graph and request user inputs
            while (!g.isAvailableEdge(v1, v2)) {
                cout << "Select the first Vertex: ";
                cin >> v1; cin.ignore();
                while (v1 > 4 || v1 < 0) {
                    cout << "\nError! Please select the correct country code: ";
                    cin >> v1; cin.ignore();
                }

                cout << "Select the second Vertex: ";
                cin >> v2; cin.ignore();
                while (v2 > 4 || v2 < 0) {
                    cout << "\nError! Please select the correct country code: ";
                    cin >> v2; cin.ignore();
                }

                if (!g.isAvailableEdge(v1, v2)) {
                    cout << "\n Edge is not available. Please select another one!\n\n";
                }
            }

            // Remove the edge by calling the function removeEdge().
            g.removeEdge(v1, v2, citiesName);

            cout << "Modified Graph: " << endl;
            cout << "***************************************************************" << endl;
            g.PrintGraph(citiesName);
            cout << "***************************************************************" << endl;
			
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

