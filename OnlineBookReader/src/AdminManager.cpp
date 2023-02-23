#include "AdminManager.h"
#include "fileHandler.h"
#include "Interface.h"
#include "vector"
using namespace std ;

void AdminManager :: GetAdminsFromDatabase(){
    const string path = "admins.txt" ;
    vector<string> lines = readfileline(path) ;
    for (string &l : lines){
        Admin* admin = new Admin(l) ;
        admins[admin->getUsername()] = admin ;
    }
    return ;
}


AdminManager ::~AdminManager(){
    cout << "Destructor of AdminManager" << endl;
    for (auto &pair : admins){
        delete pair.second ;
    }
    admins.clear() ;
    if (currentAdmin != nullptr){
        delete currentAdmin ;
        currentAdmin = nullptr ;
    }
}

void AdminManager :: logIn(){
    if (admins.size() == 0 )
        GetAdminsFromDatabase() ;
    string username , password ;
    while(true){
        cout << "\nEnter user name (no spaces) : " ;
        cin >> username ;
        if (admins.count(username) == 0){
            cout << "Invalid user name please try again...." ;
            continue ;
        }
        cout << "\nEnter password (no spaces) : " ;
        cin >> password ;
        if (admins[username]->getPassword() != password){
            cout << "Invalid password please try again....." ;
            continue ;
        }
        break ;
    }
    currentAdmin = admins[username] ;
    cout << "Hello " << currentAdmin->getName() << " | Admin view\n\n" ;
}
Admin* AdminManager :: getCurrentAdmin(){
    return currentAdmin ;
}
void AdminManager :: Access_system(){
    vector<string> menu = {"Login"} ;
    int choice = Interface :: ShowMenu(menu) ;
    logIn() ;
}
