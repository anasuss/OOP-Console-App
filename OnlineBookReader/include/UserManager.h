#ifndef USERMANAGER_H
#define USERMANAGER_H
#include <User.h>
using namespace std ;


class UserManager{
private:
    map<string,User*> users ;
    User* currentUser{nullptr} ;
public:
    UserManager(const UserManager&) = delete;
	void operator=(const UserManager&) = delete;
    UserManager(){
    }
    ~UserManager() ;
    void DoLogIn();
    void DoSignUp() ;
    void accesSystem();
    void GetUsersFromDatabase() ;
    User* getCurrentUser() ;
};

#endif // USERMANAGER_H
