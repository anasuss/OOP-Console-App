#ifndef ADMIN_H
#define ADMIN_H
#include <Person.h>
#include "Book.h"
#include "BookManger.h"

class Admin : public Person{
private :
    BookManger bookManger ;
public :
    using Person :: Person ;
    void addBook() ;
};

#endif // ADMIN_H
