#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <string>

using namespace std;

const string SEPARATOR = "###";

struct given_inputs{
    vector<string> meaning_words;
    vector<string> sentences;
    given_inputs(vector<string> mean_val, vector<string> sent_val) :
     meaning_words(mean_val), sentences(sent_val) {}
};

vector<string> reading_from_file(const string file_name){
    ifstream input_file(file_name);
    string line;
    vector<string> lines;
    while(getline(input_file, line)){
        lines.push_back(line);
    }
    input_file.close();
    return lines;
}

int index_of_separator(const vector<string> lines){
    int index;
    for(int i = 0; i < lines.size(); i++){
        if(lines[i] == SEPARATOR){
            index = i;
        }
    }
    return index;
}

given_inputs filling_strcut_with_inputs(const vector<string> lines){
    int index = index_of_separator(lines);
    vector<string> meaning_words(lines.begin(), lines.begin() + index);
    vector<string> sentences(lines.begin() + index + 1, lines.end());
    given_inputs result(meaning_words, sentences);
    return result;
}

int main(int argc, char*argv[]){
    given_inputs my_inputs = filling_strcut_with_inputs(reading_from_file(argv[1]));
    return 0;
}