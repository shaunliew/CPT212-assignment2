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
    //TODO: find out what city is corresponding to this weight
    int weight[5][5] = 
    {
        {0,3383,3315,16659,6390},       //Depart: HE; Destination: HE,CA,TE,AU,DH
        {3383,0,1984,16579,5849},       //Depart: CA; Destination: HE,CA,TE,AU,DH
        {3315,1984,0,15010,3964},       //Depart: TE; Destination: HE,CA,TE,AU,DH
        {16659,16570,15010,0,11090},    //Depart: AU; Destination: HE,CA,TE,AU,DH
        {6390,5849,3964,11090,0}        //Depart: DH; Destination: HE,CA,TE,AU,DH
    };

    vector<string> cities = { "Helsinki, Finland", "Cairo, Egypt", "Tehran, Iran", "Auckland, New Zealand", "Dhaka, Bangladesh" };
    Graph g(cities);
    //initialize according to the diagram , refer to CPT_212_CITY.png
    // first agrument is the depart , second is destination, third arguement is the weight of the weight edges
    g.addEdge("Cairo, Egypt", "Helsinki, Finland", 3383);
    g.addEdge("Cairo, Egypt", "Tehran, Iran", 1984);
    g.addEdge("Tehran, Iran", "Auckland, New Zealand", 15010);
    g.addEdge("Auckland, New Zealand", "Dhaka, Bangladesh", 11090);
    g.addEdge("Dhaka, Bangladesh", "Helsinki, Finland", 6390);
    g.printAdjList();
    return 0;
}

