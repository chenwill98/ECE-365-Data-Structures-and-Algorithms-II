#include "hash.h"
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <string.h>
#include <locale>
#include <algorithm>
#include <iterator>
#include <regex>
#include <vector>

void loadDict(std::string dict);
void spellChecker(std::string in_path, std::string out_path);
void parse(std::string line);
bool hasDigit(std::string line);

hashTable dictionary(50000);
std::vector<std::string> tokens;

int main() {
        std::string dict_path, in_path, out_path;

        clock_t begin = clock();
        loadDict(dict_path);
        clock_t end = clock();
        double elapsed_secs = ((double)(end-begin)) / CLOCKS_PER_SEC;
        std::cout << "Total time (in seconds) to load dictionary: " << elapsed_secs << std::endl;

        begin = clock();
        spellChecker(in_path, out_path);
        end = clock();
        elapsed_secs = ((double)(end-begin)) / CLOCKS_PER_SEC;
        std::cout << "Total time (in seconds) to check document: " << elapsed_secs << std::endl;

        return 0;
}

void loadDict(std::string dict_path) {
        std::fstream data_file;
        std::string word;

        std::cout << "Enter name of dictionary: ";
        std::cin >> dict_path;

        data_file.open(dict_path);
        if (!data_file) {
                std::cout << "Error: could not open " << dict_path << std::endl;
                exit(0);
        }


        while (data_file >> word) {
                for (int i = 0; i < word.length(); i++)
                        word[i] = std::tolower(word[i]);

                dictionary.insert(word);
        }
        data_file.close();
}

void spellChecker(std::string in_path, std::string out_path) {
        std::ifstream in_file;
        std::ofstream out_file;
        std::string line;
        int line_count = 0;

        std::cout << "Enter name of input file: ";
        std::cin >> in_path;
        in_file.open(in_path);
        if (!in_file) {
                std::cout << "Error: could not open " << in_path << std::endl;
                exit(0);
        }


        std::cout << "Enter name of output file: ";
        std::cin >> out_path;
        out_file.open(out_path);
        if (!out_file) {
                std::cout << "Error: could not open " << out_path << std::endl;
                exit(0);
        }

        while (!in_file.eof()) {
                std::getline(in_file, line);
                line_count++;
                parse(line);
                for(int i = 0; i < tokens.size(); i++) {
                        if (tokens[i].length() <= 20 && !hasDigit(tokens[i]) && !dictionary.contains(tokens[i]))
                                out_file << "Unknown word at line " << line_count << ": " << tokens[i] << std::endl;
                        else if (tokens[i].length() > 20 && !hasDigit(tokens[i]))
                                out_file << "Long word at line " << line_count << ", starts: " << tokens[i].substr(0, 20) << std::endl;
                }
                tokens.clear();
        }
        in_file.close();
        out_file.close();
}
//Parses each line passed to the function
//After making the line lowercase, it divides it
//into words based on whitespace and special characters
void parse(std::string line) {
        for (int i = 0; i < line.length(); i++)
                line[i] = std::tolower(line[i]);
        std::regex re("\[-'[:alnum:]]+");
        std::sregex_token_iterator begin(line.begin(), line.end(), re), end;
        std::copy(begin, end, std::back_inserter(tokens));
}

bool hasDigit(std::string word) {
        for (int i = 0; i < word.length(); i++)
                if(isdigit(word[i]))
                        return true;
        return false;
}
