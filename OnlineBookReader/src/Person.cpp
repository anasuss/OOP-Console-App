#include "Person.h"


Person :: Person(){
}
Person :: Person(const string &username ,const string &password ,const string &name ,const string &email){
    this->username = username ;
    this->password = password ;
    this->name = name ;
    this->email = email ;
}
Person :: Person(string& line){
    vector<string> words = Split_string(line) ;
    assert(words.size() == 4) ;
    this->username = words[0] ;
    this->password = words[1] ;
    this->name = words[2] ;
    this->email = words[3] ;
}
void Person :: setUsername(const string& username){
    this->username = username ;
}
const string& Person :: getUsername() const{
    return username ;
}
void Person :: setName(const string& name){
    this->name = name ;
}
const string& Person :: getName() const{
    return name ;
}
void Person :: setPassword(const string& password){
    this->password = password ;
}
const string& Person :: getPassword() const{
    return password ;
}
void Person:: setEmail(const string& email){
    this->email = email ;
}
const string& Person :: getEmail() const{
    return email ;
}
void Person :: to_string() const{
    cout << "Name: " << name ;
    cout << "\nEmail: " << email ;
    cout << "\nUser name: " << username ;
    cout << "\npassword : " << password ;
}

