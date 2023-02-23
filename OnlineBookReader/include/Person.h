#ifndef PERSON_H
#define PERSON_H
#include <bits/stdc++.h>
#include<PhraseHandler.h>
#include "UpdateDataBase.h"

using namespace std ;

class Person{
protected :
    string username ;
    string password ;
    string name ;
    string email ;
public :
    Person() ;
    Person(const string &username ,const string &password ,const string &name ,const string &email);
    Person(string& line);
    void setUsername(const string& username);
    const string& getUsername() const;
    void setName(const string& name);
    const string& getName() const;
    void setPassword(const string& password);
    const string& getPassword() const;
    void setEmail(const string& email);
    const string& getEmail() const;
    void to_string() const;
};


#endif // PERSON_H
