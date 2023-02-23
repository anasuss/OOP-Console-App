#include "UserManager.h"
#include "Interface.h"
#include "UpdateDataBase.h"
#include "fileHandler.h"

UserManager :: ~UserManager(){
    cout << "Destructor Of UserManager" << endl ;
    for (auto &pair : users){
        delete pair.second ;
    }
    users.clear() ;
    if (currentUser != nullptr){
        delete currentUser ;
        currentUser = nullptr ;
    }
}


void UserManager::GetUsersFromDatabase(){
    const string path = "users.txt";
    vector<string> lines = readfileline(path) ;
    for (string &l : lines){
        User* user = new User(l) ;
        users[user->getUsername()] = user ;
    }
    return ;
}

void UserManager :: DoLogIn(){
    if (users.size() == 0)
        GetUsersFromDatabase() ;
    string username,password ;
    while(true){
        cout << "Enter user name : " ;
        cin >> username ;
        if (users.count(username) == 0){
            cout << "Incorrect user name please try again ...\n" ;
            continue ;
        }
        cout << "Enter password : " ;
        cin >> password ;
        if (users[username]->getPassword() != password){
            cout << "Incorrect password please try again ...." ;
            continue ;
        }
        break ;
    }
    currentUser = users[username] ;
    cout << "\nHello " << currentUser->getName() << " | User View" << endl ;
    return ;
}

void UserManager :: DoSignUp(){
    if (users.size() == 0)
        GetUsersFromDatabase() ;
    string username,password,name,email ;
    while(true){
        cout << "Enter user name : " ;
        cin >> username ;
        if (users.count(username)){
            cout << "User Name Already Exist Enter Another One\n" ;
            continue ;
        }
        cout << "Enter password : " ;
        cin >> password ;
        cout << "Enter name : "  ;
        cin >> name ;
        cout << "Enter Email : " ;
        cin >> email ;
        break ;
    }
    currentUser = new User(username,password,name,email) ;
    WriteFileLines("users.txt",{username+","+password+","+name+","+email}) ;
    return ;
}

void UserManager :: accesSystem(){
    int choix = Interface :: ShowMenu({"LogIn","Sign Up"}) ;
    if (choix == 1){
        DoLogIn() ;
    }else{
        DoSignUp() ;
    }
}

User* UserManager ::getCurrentUser(){
    return currentUser ;
}
