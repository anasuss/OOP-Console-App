#include "User.h"
#include "BookManger.h"

void User :: ListAndSelectFromAvailableBooksToRead(){
    bookManger.choseFromAvailableBookToRead() ;
    bookManger.ReadingSessionOfBook(ReadingBooks) ;
}

void User :: ListAndSelectFromReadingBookHistory(){
    if (ReadingBooks.size() == 0){
        cout << "No Reading Books History\n";
        return ;
    }
    bookManger.choseFromReadingHistory(ReadingBooks) ;
    bookManger.ReadingSessionOfBook(ReadingBooks) ;
}
