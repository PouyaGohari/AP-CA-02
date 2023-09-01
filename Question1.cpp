#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <math.h>

const int MIN_N = 1;
const int MAX_N = 20;
const int MIN_K = 1;

using namespace std;

struct my_input{
    int n;
    long long int k;
};

vector<string> reading_from_file(const string file_name){
    ifstream reading_file(file_name);
    string line;
    vector<string> lines;
    while(getline(reading_file, line)){
        lines.push_back(line);
    }
    reading_file.close();
    return lines;
}

void exception_handeling(const my_input inputs){
    if(inputs.n < MIN_N || inputs.n > MAX_N){
        throw runtime_error("Invalid input for n");
    }
    if(inputs.k < MIN_K || inputs.k > pow(2, inputs.n)-1){
        throw runtime_error("Invalid input for k");
    }
}

my_input assign_to_my_input(const vector<string> lines){
    my_input result;
    result.n = stoi(lines[0]);
    result.k = stoll(lines[1]);
    exception_handeling(result);
    return result;
} 

int main(int arg , char*argv[]){
    my_input inputs = assign_to_my_input(reading_from_file(argv[1]));
    exception_handeling(inputs);
    return 0;
}