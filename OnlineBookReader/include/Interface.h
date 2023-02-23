#ifndef INTERFACE_H
#define INTERFACE_H
#include <vector>
#include <string>
using namespace std ;

class Interface{
public :
    static int ReadChoice(int low , int heigh) ;
    static int ShowMenu(const vector<string>& choices) ;
};
#endif // INTERFACE_H
