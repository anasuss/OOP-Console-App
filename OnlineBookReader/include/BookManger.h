#ifndef BOOKMANGER_H
#define BOOKMANGER_H
#include "Book.h"

class BookManger{
private :
    vector<Book*> AllBooks ;
    Book* currentReadingBook ;
public:
     BookManger(const BookManger&) = delete;
	 void operator=(const BookManger&) = delete;
     BookManger();
    ~BookManger();
    void GetBooksFromDatabase() ;
    void setCurrentReadingBook(Book* book) ;
    void AddBookToDataBase(const Book& book) ;
    const Book* getCurrentReadingBook() ;
    void choseFromAvailableBookToRead() ;
    void choseFromReadingHistory(const vector<pair<Book*,string>>& ReadingBooks) ;
    void ReadingSessionOfBook(vector<pair<Book*,string>>& ReadingBooks) ;

};

#endif // BOOKMANGER_H
