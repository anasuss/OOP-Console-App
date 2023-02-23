#include "BookManger.h"
#include "Interface.h"
#include <ctime>
#include "fileHandler.h"





BookManger::BookManger(){

}

BookManger::~BookManger(){
    cout << "Destructor of BookManager" << endl ;
    for (int i = 0 ; i<AllBooks.size() ; i++){
        delete AllBooks[i] ;
    }
    AllBooks.clear() ;
}


void BookManger :: setCurrentReadingBook(Book *book){
    currentReadingBook = book ;
    return ;
}


const Book* BookManger :: getCurrentReadingBook(){
    return currentReadingBook ;
}
//Helper function to get Date and Time
string currentDateTime() {
    std::time_t t = std::time(nullptr);
    std::tm* now = std::localtime(&t);
    char buffer[128];
    strftime(buffer, sizeof(buffer), "%m-%d-%Y %X", now);
    return buffer;
}
void BookManger :: GetBooksFromDatabase(){
    vector<string> lines = readfileline("books.txt") ;
    for (string &l : lines){
        Book *book = new Book(l) ;
        AllBooks.push_back(book) ;
    }
    return ;
}


void BookManger :: AddBookToDataBase(const Book& book){
    string line = book.getISBN()+","+book.getTitle()+","+book.getName()+","+to_string(book.getNumberOfpages()) ;
    for (const string& page : book.getPages()){
        line = line+","+page ;
    }
    string path = "books.txt" ;
    vector<string> lines = {line} ;
    WriteFileLines(path,lines) ;
}


void BookManger :: choseFromReadingHistory(const vector<pair<Book*,string>>& ReadingBooks){
    cout << "Our current book collection : \n" ;
    for (int i = 0 ; i<ReadingBooks.size() ; i++){
            Book *book = ReadingBooks[i].first ;
            string DateTime = ReadingBooks[i].second ;
            cout << "\t" << i+1 << " : " << book->getTitle() << " Page: " << book->getCurrentNubmerPage() << "/" << book->getNumberOfpages() << " - " << DateTime << "\n" ;
    }
    cout << "Which Session to open?:\n" ;
    int choice = Interface :: ReadChoice(1,ReadingBooks.size()) ;
    setCurrentReadingBook(ReadingBooks[choice-1].first) ;
    return ;
}

void BookManger :: choseFromAvailableBookToRead(){
    GetBooksFromDatabase() ;
    if (AllBooks.size() == 0){
        cout << "No Books are available for now\n" ;
        return ;
    }
    cout << "Our current book collection : " << endl ;
    for (int i = 0 ; i<AllBooks.size() ; i++){
            cout << "\t" << i+1 << " : " << AllBooks[i]->getTitle() << "\n" ;
    }
    cout << "Which book to read\n" ;
    int choice = Interface :: ReadChoice(1,AllBooks.size()) ;
    currentReadingBook = AllBooks[choice-1] ;
    return ;
}



void BookManger :: ReadingSessionOfBook(vector<pair<Book*,string>>& ReadingBooks){
    vector<string> menu = {"Next Page","Previous Page","Stop reading"} ;
    while(true){
        int currentPageNumber = currentReadingBook->getCurrentNubmerPage() ;
        cout << "Current Page: " << currentPageNumber << "/" << currentReadingBook->getNumberOfpages() << endl ;
        cout << currentReadingBook->getPage() << endl;
        int choix = Interface::ShowMenu(menu) ;
        if (choix == 3){
            ReadingBooks.push_back({currentReadingBook,currentDateTime()}) ;
            return ;
        }
        if (choix == 1){
            if (currentPageNumber < currentReadingBook->getNumberOfpages()){
                ++currentPageNumber ;
                currentReadingBook->setCurrentNumberPage(currentPageNumber);
            }
        }else{
            if (currentPageNumber>1)
                --currentPageNumber ;
                currentReadingBook->setCurrentNumberPage(currentPageNumber) ;
        }
    }

}
