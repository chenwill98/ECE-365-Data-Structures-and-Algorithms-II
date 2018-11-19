#include "graph.h"

graph::graph() {
        size = 0;
        graph_nodes = new hashTable(100000);
}

//insert the node into the graph
void graph::insert(std::string &line) {
        edge new_edge;
        std::string token;
        std::istringstream iss(line);
        std::vector<std::string> tokens{
                std::istream_iterator<std::string>(iss), {}
        };

        node * cur = (node *)graph_nodes->getPointer(tokens[0]);
        node * next = (node *)graph_nodes->getPointer(tokens[1]);

        if (!cur) {
                size++;
                cur = new node;
                cur->id = tokens[0];
                node_list.push_back(cur);
                graph_nodes->insert(tokens[0], cur);
        }

        if (!next) {
                size++;
                next = new node;
                next->id = tokens[1];
                node_list.push_back(next);
                graph_nodes->insert(tokens[1], next);
        }

        new_edge.dest = next;
        new_edge.cost = stoi(tokens[2]);
        cur->adj.push_back(new_edge);
}

//checks to see if the node is valid
bool graph::validNode(std::string &node) {
        bool valid = graph_nodes->contains(node);
        return valid;
}

//applies Dijkstra's algorithm on a graph, given a root node
int graph::dijkstra(std::string &root) {
        node * cur;
        std::list<node*>::const_iterator it = node_list.begin(), end = node_list.end();
        for (; it != end; ++it) {
                (*it)->dist = INT_MAX;
                (*it)->known = false;
        }

        heap queue(size);
        node * start = (node *)graph_nodes->getPointer(root);
        start->dist = 0;
        start->known = true;
        start->path.push_back(root);
        for (it = node_list.begin(); it != end; ++it) {
                queue.insert((*it)->id, (*it)->dist, *it);
        }

        for (int i = 0; i < size; i++) {
                queue.deleteMin(nullptr, nullptr, &cur);
                for (std::list<edge>::const_iterator it = cur->adj.begin(), end = cur->adj.end(); it != end && cur->dist != INT_MAX; ++it) {
                        if (it->dest->dist > (it->cost + cur->dist) && !it->dest->known) {
                                queue.setKey(it->dest->id, (it->cost + cur->dist));
                                it->dest->dist = (it->cost + cur->dist);
                                it->dest->path.clear();
                                it->dest->path.insert(it->dest->path.begin(), cur->path.begin(), cur->path.end());
                                it->dest->path.push_back(it->dest->id);
                        }
                }
                cur->known = true;
        }
        return 0;
}

//output the graph
void graph::output(std::string &out_path) {
        std::ofstream out_file;
        out_file.open(out_path);
        if (!out_file) {
                std::cout << "Error: could not open " << out_path << std::endl;
                exit(-1);
        }

        for (std::list<node*>::const_iterator it = node_list.begin(), end = node_list.end(); it != end; ++it) {
                out_file << (*it)->id << ": ";
                if ((*it)->dist != INT_MAX) {
                        out_file << (*it)->dist << " [";

                        std::list<std::string>::const_iterator it_path = (*it)->path.begin(), end_path = (*it)->path.end();
                        out_file << (*it_path);
                        it_path++;
                        while (it_path != end_path) {
                                out_file << ", " << (*it_path);
                                it_path++;
                        }
                        out_file << "]" << std::endl;

                } else {
                        out_file << "NO PATH" << std::endl;
                }
        }
}
