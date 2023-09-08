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

struct fitted_word_per_sentence{
    vector<string> suitable_words;
    string sentece;
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

vector<string> finding_suitable_words(const string sentence, const vector<string> meaning_words){
    vector<string> suitable_words;
    for(auto word : meaning_words){
        size_t found = sentence.find(word);
        if(found == string::npos){
            suitable_words.push_back(word);
        }
    }
    return suitable_words;
}

vector<fitted_word_per_sentence> reassigning(const given_inputs inputs){
    vector<fitted_word_per_sentence> result;
    for(auto sentence : inputs.sentences){
        fitted_word_per_sentence temp;
        temp.suitable_words = finding_suitable_words(sentence, inputs.meaning_words);
        temp.sentece = sentence;
        result.push_back(temp);
    }
    return result;
}

int main(int argc, char*argv[]){
    vector<fitted_word_per_sentence> inputs = reassigning(filling_strcut_with_inputs(reading_from_file(argv[1])));
    return 0;
}