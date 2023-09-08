#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <string>

using namespace std;

const string SEPARATOR = "###";
const char SPACE = ' ';

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

void get_word_breaks(string sentence, vector<string> dictionary, vector<string>& word_breaks, string result = ""){
    for(int i = 1 ; i <= sentence.size(); i++){
        string prefix = sentence.substr(0,i);
        if(find(dictionary.begin(), dictionary.end(), prefix) != dictionary.end()){
            if(i == sentence.size()){
                result += prefix;
                word_breaks.push_back(result);
                return;
            }
            get_word_breaks(sentence.substr(i, sentence.size()), dictionary, word_breaks, result + prefix + " ");
        }
    }
}

vector<vector<string>> get_all_word_breaks(given_inputs inputs){
    vector<vector<string>> all_words_breaks;
    for(auto sentence: inputs.sentences){
        vector<string> word_breaks;
        get_word_breaks(sentence, inputs.meaning_words, word_breaks);
        all_words_breaks.push_back(word_breaks);
    }
    return all_words_breaks;
}

int main(int argc, char*argv[]){
    given_inputs inputs = filling_strcut_with_inputs(reading_from_file(argv[1]));
    vector<vector<string>> all_possible_answers = get_all_word_breaks(inputs);
    return 0;
}