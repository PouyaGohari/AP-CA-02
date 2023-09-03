#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>

using namespace std;

const int MIN_LENGTH = 1;
const int MAX_LENGHT = 30;

void exception_handeling(const string line){
    if(line.length() > MAX_LENGHT || line.length() < MIN_LENGTH)
     throw runtime_error("Limits for length has been ignored ur input length must be more than 0 and less than 31");
}   

string reading_from_file(const string file_name){
    ifstream input_file(file_name);
    string line;
    getline(input_file, line);
    exception_handeling(line);
    return line;
}

int main(int argc, char*argv[]){
    string line = reading_from_file(argv[1]);
    return 0;
}