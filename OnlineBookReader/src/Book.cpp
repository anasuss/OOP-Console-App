#include "Book.h"
#include <vector>


Book::Book(){
}

Book::Book(const string &ISBN , const string &title , const string &name , int numberOfpages , const vector<string> &pages){
        this->ISBN = ISBN ;
        this->title = title ;
        this->name = name ;
        this->numberOfpages = numberOfpages ;
        this->pages = pages ;
}
Book::Book(string &line){
    const vector<string> words =  Split_string(line) ;
    ISBN = words[0] ;
    title = words[1] ;
    name = words[2] ;
    numberOfpages = ToInt(words[3]) ;
    for (int i = 4 ; i<words.size() ; i++){
        pages.push_back(words[i]) ;
    }
}
void Book::ReadBook(){
    cout << "Enter ISBN : " ;
    cin >> ISBN ;
    cout << "Enter Title : " ;
    cin >> title ;
    cout << "Enter Author Name : " ;
    cin >> name ;
    cout << "Enter How many pages : " ;
    cin >> numberOfpages ;
    cin.ignore() ;
    string page ;
    for (int i = 0 ; i<numberOfpages ; i++){
        cout << "Enter page # " << i+1 << " : " ;
        getline(cin,page) ;
        pages.push_back(page) ;
    }
}
const string& Book :: getISBN() const {
        return ISBN ;
}
const string& Book :: getTitle() const {
    return title ;
}
const string& Book :: getName() const {
    return name ;
}
const int Book :: getNumberOfpages() const {
    return numberOfpages ;
}
const vector<string>& Book::getPages() const {
    return pages ;
}
const string& Book::getPage() const {
    return pages[currentNumberPage-1] ;
}
int Book::getCurrentNubmerPage() const {
    return currentNumberPage ;
}
void Book::setCurrentNumberPage(int currentNumberPage){
    this->currentNumberPage = currentNumberPage ;
}
