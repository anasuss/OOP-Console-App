#include "fileHandler.h"

vector<string> readfileline(const string& path){
    vector<string> lines ;
    fstream file_handler(path.c_str()) ;
    if (file_handler.fail()){
        cout << "\n\nERROR: Can't open the file\n\n";
        return lines ;
    }
    string line ;
    while(getline(file_handler,line)){
        if (line.size() == 0)
            continue ;
        lines.push_back(line) ;
    }
    file_handler.close() ;
    return lines ;
}

void WriteFileLines(const string &path , const vector<string>& lines){
    auto status = ios::in | ios::out | ios:: app ;
    fstream file_handler(path.c_str(),status) ;
    if (file_handler.fail()){
        cout << "\n\nERROR: Can't open the file\n\n";
        return ;
    }
    for (const string &line : lines){
        if (line.size() == 0)
            continue ;
        file_handler << line << "\n" ;
    }
    file_handler.close() ;
}
