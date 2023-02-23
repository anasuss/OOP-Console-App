#include "PhraseHandler.h"

int ToInt(const string &s){
    istringstream ss(s) ;
    int x ;
    ss >> x ;
    return x;
}

vector<string> Split_string(string &line , const string &delemiter ){
    int pos = 0 ;
    vector<string> words ;
    while((pos = (int)line.find(delemiter)) != -1){
        string s = line.substr(0,pos) ;
        words.push_back(s);
        line.erase(0,pos+1) ;
    }
    words.push_back(line) ;
    return words ;
}
