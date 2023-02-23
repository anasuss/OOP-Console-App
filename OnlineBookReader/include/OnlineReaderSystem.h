#ifndef ONLINEREADERSYSTEM_H
#define ONLINEREADERSYSTEM_H
#include "AdminManager.h"
#include "UserManager.h"
#include "vector"

class OnlineReaderSystem{
private :
    AdminManager *adminManager{nullptr} ;
    UserManager *userManager{nullptr} ;
    vector<string> menu ;
public :
    OnlineReaderSystem();
    ~OnlineReaderSystem();
    void run();
};

#endif // ONLINEREADERSYSTEM_H
