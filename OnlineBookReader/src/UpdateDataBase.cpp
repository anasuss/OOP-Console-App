#include <bits/stdc++.h>
#include "UpdateDataBase.h"
#include "Book.h"
#include "Admin.h"
#include "User.h"
#include "fileHandler.h"



void UpdateDataBase::AddBookToDataBase(const Book& book){
    string line = book.getISBN()+","+book.getTitle()+","+book.getName()+","+to_string(book.getNumberOfpages()) ;
    for (const string& page : book.getPages()){
        line = line+","+page ;
    }
    string path = "books.txt" ;
    vector<string> lines = {line} ;
    WriteFileLines(path,lines) ;
}








