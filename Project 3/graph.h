#ifndef _GRAPH_H
#define _GRAPH_H

#include <vector>
#include <string>
#include <iterator>
#include <iostream>
#include <list>
#include <bits/stdc++.h>
#include "heap.h"


class graph {

        public:
        //initializes the graph hashTable
        graph();

        //insert the node into the graph
        void insert(std::string &line);

        //checks to see if the node is valid
        bool validNode(std::string &node);

        //applies Dijkstra's algorithm on a graph, given a root node
        int dijkstra(std::string &start);

        //output the graph in the proper format
        void output(std::string &out_path);


        private:
        class edge;
        class node;
        int size;
        hashTable * graph_nodes; //hashtable for quick lookup of each node
        std::list<node *> node_list; //list that holds all of the vertices in the graph

        class edge {
        public:
                int cost;
                node *dest; //destination node
        };

        class node {
        public:
                int dist;
                bool known;
                std::string id;
                std::list<edge> adj;
                std::list<std::string> path;
        };
};

#endif
