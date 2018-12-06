//William Chen
//Professor Sable
//DSA II Project 4

#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <ctime>
#include <algorithm>
#include <vector>

int mat[1002][1002];

int check(std::string word_1, std::string word_2, std::string &word_merged);

int main() {
        std::ifstream in_file;
        std::ofstream out_file;
        std::string in_path, out_path, line;
        std::string word_1, word_2, word_merged;

        std::cout << "Enter name of input file: ";
        std::cin >> in_path;
        in_file.open(in_path);
        if (!in_file) {
                std::cout << "Error: could not open " << in_path << std::endl;
                return -1;
        }

        std::cout << "Enter name of output file: ";
        std::cin >> out_path;
        out_file.open(out_path);
        if (!out_file) {
                std::cout << "Error: could not open " << out_path << std::endl;
                return -1;
        }

        while (std::getline(in_file, word_1) && std::getline(in_file, word_2) && std::getline(in_file, word_merged)) {
                //resets the matrix
                for (int i = 0; i < 1002; i++)
                        for (int j = 0; j < 1002; j++)
                                mat[i][j] = -1;
                if (check(word_1, word_2, word_merged) < 0 || (word_1.length() + word_2.length() != word_merged.length()))
                        out_file << "*** NOT A MERGE ***" << std::endl;
                else
                        out_file << word_merged << std::endl;
        }
}

int check(std::string word_1, std::string word_2, std::string &word_merged) {
        int index_1 = word_1.length(), index_2 = word_2.length(), index_m = word_merged.length() - 1;
        //initializes the values based on the first letter of each word
        if (word_1[0] == word_merged[0])
                mat[1][0]++;
        if (word_2[0] == word_merged[0])
                mat[0][1]++;

        //populates the matrix
        for (int i = 0; i < index_1 + 1; i++)
                for (int j = 0; j < index_2 + 1; j++) {
                        if (mat[i][j] != -1 && word_merged[mat[i][j] + 1] == word_1[i])
                                mat[i + 1][j] = mat[i][j] + 1;
                        if (mat[i][j] != -1 && word_merged[mat[i][j] + 1] == word_2[j])
                                mat[i][j + 1] = mat[i][j] + 1;
                }

        //starts at the last valid matrix value and works backwards
        if (mat[index_1][index_2] != -1) {
                while (index_m >= 0) {
                        index_m--;
                        if (mat[index_1][index_2-1] == index_m && index_2 > 0)
                                index_2--;
                        else {
                                word_merged[index_m + 1] = toupper(word_merged[index_m + 1]);
                                index_1--;
                        }
                }
                return 0;
        }
        return -1;
}
