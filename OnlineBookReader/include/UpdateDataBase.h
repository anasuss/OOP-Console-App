#ifndef UPDATEDATABASE_H
#define UPDATEDATABASE_H
using namespace std ;

class Book ;

class Admin ;

class User ;

class UpdateDataBase{
private:

public:
    static void AddBookToDataBase(const Book& book) ;
    static map<string,Admin*> GetAdminsFromDatabase() ;
    static map<string,User*> GetUsersFromDatabase() ;
    static  const vector<Book*>& GetBooksFromDatabase() ;
};

#endif // UPDATEDATABASE_H
