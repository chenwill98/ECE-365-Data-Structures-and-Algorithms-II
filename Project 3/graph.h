#ifndef _GRAPH_H
#define _GRAPH_H

#include <vector>
#include <string>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <sstream>
#include <math.h>
#include <list>
#include <bits/stdc++.h>
#include "heap.h"


class graph {

        public:
        //initializes the graph hashTable
        graph();

        //insert the node into the graph
        void insert(std::string &line);

        //applies Dijkstra's algorithm on a graph, given a root node
        int dijkstra(std::string &start);

        //output the graph
        void output(std::string &out_path);


        private:
        int size;

        class edge;
        class node;

        std::list<node *> node_list; //list that holds all of the vertices in the graph
        hashTable * graph_nodes; //hashtable for quick lookup of each node

        class edge {
        public:
                int cost;
                node *dest; //destination node
        };

        class node {
        public:
                std::string id;
                std::list<edge> adj; //list of all adjacent edges

                bool known;
                int dist;
                std::list<std::string> path;
        };
};

#endif
