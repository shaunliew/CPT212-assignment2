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

    g.PrintGraph(citiesName);

    cout << "\n\n" << "Shortest distance is " << g.dijkstra() << endl;
    return 0;
}

