#ifndef BOOK_H
#define BOOK_H
#include <bits/stdc++.h>
#include "PhraseHandler.h"

using namespace std ;
class Book{
private :
    string ISBN ;
    string title ;
    string name ;
    int numberOfpages ;
    int currentNumberPage = 1 ;
    vector<string> pages ;
public :
    Book() ;
    Book(const string &ISBN , const string &title , const string &name , int numberOfpages , const vector<string> &pages) ;
    Book(string &line);
    void ReadBook();
    const string& getISBN() const ;
    const string& getTitle() const ;
    const string& getName() const ;
    const int getNumberOfpages() const ;
    const vector<string>& getPages() const ;
    const string& getPage() const ;
    int getCurrentNubmerPage() const ;
    void setCurrentNumberPage(int currentNumberPage);

};


#endif // BOOK_H
