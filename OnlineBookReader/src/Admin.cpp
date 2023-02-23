#include "Admin.h"

void Admin :: addBook(){
    Book book ;
    book.ReadBook() ;
    bookManger.AddBookToDataBase(book) ;
}
