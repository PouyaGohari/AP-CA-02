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

void inverse_fnc(string& str, int it = 0){
    if(it == str.size() - 1){
        if(str[it] == '0') str[it] = '1';
        else str[it] = '0';
        return;
    }
    if(str[it] == '0') str[it] = '1';
    else str[it] = '0';
    it = it + 1;
    inverse_fnc(str, it);
}

void reverse_fnc(string& str, int it = 0){
    if(it == str.size()/2 && str.size()%2 == 1){
        swap(str[it], str[str.size()- 1 - it]);
        return; 
    }
    else if(it == str.size()/2 && str.size()%2 == 0){
        return;
    }
    swap(str[it], str[str.size() - 1 - it]);
    it = it + 1;
    reverse_fnc(str, it);
}

string create_sn_recursively(int n){
    if(n == 1){
        return "0";
    }
    string previous_sequence = create_sn_recursively(n - 1);
    string inv_rev_prev_seq = previous_sequence;
    inverse_fnc(inv_rev_prev_seq);
    reverse_fnc(inv_rev_prev_seq);
    return previous_sequence + "1" + inv_rev_prev_seq;
}

void finding(int n, int k){
    string seq = create_sn_recursively(n);
    cout << seq[k-1] << endl;
}


void writing_outputs_in_file(const string file_name, const int n, const int k){
    ofstream Ouputfile(file_name);
    streambuf* orignial_buffer = cout.rdbuf();
    cout.rdbuf(Ouputfile.rdbuf());
    finding(n, k);
    cout.rdbuf(orignial_buffer);
}

int main(int arg , char*argv[]){
    my_input inputs = assign_to_my_input(reading_from_file(argv[1]));
    exception_handeling(inputs);
    writing_outputs_in_file(argv[2], inputs.n, inputs.k); 
    return 0;
}