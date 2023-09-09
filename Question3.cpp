#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <string>

using namespace std;

const string SEPARATOR = "###";
const char SPACE = ' ';
const string PRINT_DELIM = "***";
const string NO_POSSIBLE = "-1";

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

void get_word_breaks(const string sentence,const vector<string> dictionary, vector<string>& word_breaks, string result = ""){
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

vector<vector<string>> get_all_word_breaks(const given_inputs inputs){
    vector<vector<string>> all_words_breaks;
    for(auto sentence: inputs.sentences){
        vector<string> word_breaks;
        get_word_breaks(sentence, inputs.meaning_words, word_breaks);
        all_words_breaks.push_back(word_breaks);
    }
    return all_words_breaks;
}

void print_possible_answers(const vector<vector<string>> all_possible_answers){
    for(auto answers : all_possible_answers){
        if(answers.size() == 0) cout << NO_POSSIBLE << endl;
        else{
            for(auto answer : answers){
                cout << answer << endl;
            }
        }
        cout << PRINT_DELIM << endl;
    }
}

void writing_in_file(const string file_name, const vector<vector<string>> all_possible_answers){
    ofstream my_file(file_name);
    streambuf* origin = cout.rdbuf();
    cout.rdbuf(my_file.rdbuf());
    print_possible_answers(all_possible_answers);
    cout.rdbuf(origin);
    my_file.close();
}

int main(int argc, char*argv[]){
    given_inputs inputs = filling_strcut_with_inputs(reading_from_file(argv[1]));
    vector<vector<string>> all_possible_answers = get_all_word_breaks(inputs);
    writing_in_file(argv[2], all_possible_answers);
    return 0;
}