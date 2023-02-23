#ifndef ADMINMANAGER_H
#define ADMINMANAGER_H
#include <map>
#include "Admin.h"

using namespace std ;

class AdminManager{
private :
    map<string,Admin*> admins ;
    Admin* currentAdmin{nullptr} ;
public:
	AdminManager(const AdminManager&) = delete;
	void operator=(const AdminManager&) = delete;
    AdminManager(){
    }
    ~AdminManager() ;
    Admin* getCurrentAdmin() ;
    void Access_system() ;
    void GetAdminsFromDatabase() ;
    void logIn() ;
};
#endif // ADMINMANAGER_H
