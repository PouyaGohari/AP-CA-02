#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>
#include <cctype>

using namespace std;

const int MIN_LENGTH = 1;
const int MAX_LENGHT = 100;
const char OPENING_SQUARE_BRACKET = '[';
const char CLOSING_SQUARE_BRACKET = ']';

struct coded_string{
    int number;
    string str;
    coded_string(int number_val, string str_val) : number(number_val), str(str_val) {}
};

struct open_close_indexes{
    int open_index;
    int close_index;
};

void exception_handeling(const string line){
    if(line.length() > MAX_LENGHT || line.length() < MIN_LENGTH)
     throw runtime_error("Limits for length has been ignored ur input length must be more than 0 and less than 31");
}   

string reading_from_file(const string file_name){
    ifstream input_file(file_name);
    string line;
    getline(input_file, line);
    exception_handeling(line);
    input_file.close();
    return line;
}

string times_of_string(coded_string& coded){
    if(coded.number == 1){
        return coded.str;
    }
    coded.number -= 1;
    return coded.str + times_of_string(coded);
} 

int finding_square_indexs(const string str,int i ,const char which_one){
    if(which_one == OPENING_SQUARE_BRACKET){
        if(str[i] == OPENING_SQUARE_BRACKET || i == 0) return i;
        return finding_square_indexs(str, i-1, which_one);
    }
    if(str[i] == CLOSING_SQUARE_BRACKET || i == str.size()) return i;
    return finding_square_indexs(str, i+1, which_one);
}

open_close_indexes finding_inner_square(const string str){
    open_close_indexes indexes;
    indexes.open_index = finding_square_indexs(str, str.size()-1, OPENING_SQUARE_BRACKET);
    indexes.close_index = finding_square_indexs(str, indexes.open_index, CLOSING_SQUARE_BRACKET);
    return indexes;
}

string number_behind_open_square(const string str, int it){
    if(!isdigit(str[it])) return "";
    return number_behind_open_square(str, it-1) + str[it];
}

string decode_partially(const string str, open_close_indexes index){
    string number = number_behind_open_square(str, index.open_index - 1);
    string before_number(str.begin(), str.begin() + index.open_index - number.size());
    string after_closed_square(str.begin() + index.close_index + 1, str.end());
    string remained(str.begin()+ index.open_index + 1, str.begin() + index.close_index);
    coded_string code(stoi(number), remained);
    return before_number + times_of_string(code) + after_closed_square;
}

void decoding(const string str, string& acc){
    open_close_indexes index = finding_inner_square(str);
    if(index.open_index == 0 && index.close_index == str.size()){
        acc += str;
        return;
    }
    string new_str = decode_partially(str, index);
    decoding(new_str, acc);
}

void writing_output_file(const string file_name, const string acc){
    ofstream Output(file_name);
    streambuf* oringin_buff = cout.rdbuf();
    cout.rdbuf(Output.rdbuf());
    cout << acc << endl;
    cout.rdbuf(oringin_buff);
    Output.close();
}

int main(int argc, char*argv[]){
    string line = reading_from_file(argv[1]);
    string acc = "";
    decoding(line, acc);
    writing_output_file(argv[2], acc);
    return 0;
}