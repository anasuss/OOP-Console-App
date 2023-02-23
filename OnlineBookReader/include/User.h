#ifndef USER_H
#define USER_H
#include<Person.h>
#include "UpdateDataBase.h"
#include <bits/stdc++.h>
#include "Book.h"
#include "BookManger.h"
using namespace std ;

class User : public Person{
private:
    BookManger bookManger ;
    vector<pair<Book*,string>> ReadingBooks ;
public:
    User(const User&) = delete;
	void operator=(const User&) = delete;
    using Person::Person ;
    User() ;
    void ListAndSelectFromAvailableBooksToRead() ;
    void ListAndSelectFromReadingBookHistory() ;
};

#endif // USER_H
