#include "Interface.h"
#include <bits/stdc++.h>

int Interface :: ReadChoice(int low , int heigh){
	cout << "\nEnter number in range " << low << " - " << heigh << ": ";
    int x ;
    cin >> x ;
    if (x>=low && x<=heigh){
        return x ;
    }
	cout << "ERROR: invalid number...Try again\n";
    return ReadChoice(low,heigh) ;
}

int Interface :: ShowMenu(const vector<string>& choices){
	cout << "\nMenu:\n";
	for (int i = 0; i < choices.size(); ++i) {
		cout << "\t" << i + 1 << ": " << choices[i] << "\n";
	}
	return ReadChoice(1, choices.size());
}
