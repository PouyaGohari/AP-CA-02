#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>

using namespace std;

string reading_from_file(const string file_name){
    ifstream input_file(file_name);
    string line;
    getline(input_file, line);
    return line;
}

int main(int argc, char*argv[]){
    string line = reading_from_file(argv[1]);
    return 0;
}