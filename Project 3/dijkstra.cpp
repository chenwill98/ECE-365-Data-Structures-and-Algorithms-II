#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <ctime>
#include <algorithm>
#include <vector>
#include "graph.h"

int construct (std::string &root, graph &g);

int main () {
        std::string root, out_path;

        graph g;

        if (construct(root, g) == 0) {
                clock_t begin = clock();
                g.dijkstra(root);
                clock_t end = clock();
                double elapsed_secs = ((double)(end-begin)) / CLOCKS_PER_SEC;
                std::cout << "Total time (in seconds) to apply Dijkstra's algorithm: " << elapsed_secs << std::endl;

                std::cout << "Enter name of output file: ";
                std::cin >> out_path;

                g.output(out_path);
        }
}

int construct (std::string &root, graph &g) {
        std::ifstream data_file;
        std::string in_file, line;

        std::cout << "Enter name of graph file: ";
        std::cin >> in_file;

        data_file.open(in_file);
        if (!data_file) {
                std::cout << "Error: could not open " << in_file << std::endl;
                return -1;
        }

        std::cout << "Enter a valid vertex id for the staring vertex: ";
        std::cin >> root;

        while (std::getline(data_file, line))
                g.insert(line);

        data_file.close();
        return 0;
}
