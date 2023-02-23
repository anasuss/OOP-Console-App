#ifndef BOOKMANAGER_H
#define BOOKMANAGER_H
#include <bits/stdc++.h>
#include "Book.h"
#include "User.h"
//class Book ;

class BookManager{
private :

public :
    static void addBook() ;
    static void choseBook(User &user) ;
    static void ReadBook(const User &user) ;
};

#endif // BOOKMANAGER_H
