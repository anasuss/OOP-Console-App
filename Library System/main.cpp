#include<bits/stdc++.h>



using namespace std;



int ReadChoice(int low , int heigh){
	cout << "\nEnter number in range " << low << " - " << heigh << ": ";
    int x ;
    cin >> x ;
    if (x>=low && x<=heigh){
        return x ;
    }
	cout << "ERROR: invalid number...Try again\n";
    return ReadChoice(low,heigh) ;
}

int ShowMenu(const vector<string>& choices){
	cout << "\nLibrary Menu;\n";
	for (int i = 0; i < choices.size(); ++i) {
		cout << "\t" << i + 1 << ": " << choices[i] << "\n";
	}
	return ReadChoice(1, choices.size());
}



class book{
private :
    int Id ;
    string Name ;
    int TotalQuantity = 0 ;
    int TotalBorrowed = 0 ;
public :
    book():Id(0),TotalQuantity(0),TotalBorrowed(0){
    }
    book(int id , string name , int quantity , int borrowed = 0){
        Id = id ;
        Name = name ;
        TotalQuantity = quantity ;
        TotalBorrowed = borrowed ;
    }
    const string& GetName() const {
        return Name ;
    }
    void SetName(const string& n){
        Name = n ;
    }
    int GetId()const{
        return Id ;
    }
    void SetId(int i){
        Id = i ;
    }
    int GetTotalQuantity()const{
        return TotalQuantity ;
    }
    void SetTotalQuantity(int t){
        TotalQuantity += t ;
    }
    int GetTotalBorrowed()const{
        return TotalBorrowed ;
    }
    void SetTotalBorrowed(int t){
        TotalBorrowed += t ;
    }
    bool has_prefix(string prefix)const{
        if (prefix.size()>Name.size()){
            return false ;
        }
        for (int i = 0 ; i<prefix.size() ; i++){
            if (prefix[i] != Name[i])
                return false ;
        }
        return true ;
    }
    void print() const {
        cout << "\nid = " << Id <<" name = " << Name <<" total quantity = " << TotalQuantity <<" total borrowed = " << TotalBorrowed ;
        return ;
    }
};

class library_system{
private :
    int id_book ;
    unordered_map<string,string> users ;
    map<string,vector<string>> userBorrowed;
    vector<book> BooksSystem ;
    unordered_set<string> books_in_library ;
    map<string,vector<string>> whoBorrowedBook ;
    void add_user(){
        string name ;
        string NationalId ;
        cout << "\nEnter user name & national id : " ;
        cin >> name >> NationalId ;
        users[NationalId] = name;
        return ;
    }
    void add_book(){
        string name ;
        int quantity ;
        cout << "\nEnter info of book : name & quantity : " ;
        cin >> name >> quantity ;
        if (books_in_library.count(name) == 0){
            BooksSystem.push_back(book(id_book,name,quantity)) ;
            books_in_library.insert(name) ;
            ++id_book ;
        }else{
            int IdxOfBook = 0 ;
            for(int i = 0 ; i<BooksSystem.size() ; i++){
                if (BooksSystem[i].GetName() == name){
                    IdxOfBook = i ;
                    break ;
                }
            }
            BooksSystem[IdxOfBook].SetTotalQuantity(quantity);
        }
        return ;
    }
    void search_books_by_prefix() const {
        string prefix ;
        cout << "\nEnter book name prefix : " ;
        cin >> prefix ;
        bool check = false ;
        for (const book &B : BooksSystem){
            if (B.has_prefix(prefix)){
                cout << "\n" << B.GetName() ;
                check = true ;
            }
        }
        if (check == false){
            cout << "\nNo books with such prefix" ;
            return ;
        }
        return ;
    }
    bool read_name_idUser(string &NationalIdUser , string &nameB , int trials = 3){

        while(trials--){
            cout << "\nEnter national id & book name : "  ;
            cin >> NationalIdUser >> nameB ;
            if (users.count(NationalIdUser) == 0){
                cout << "\nInvalid national id . Try again" ;
                continue ;
            }
            if (books_in_library.count(nameB) == 0){
                cout << "\nInvalid book name . Try again";
                continue ;
            }
            return true ;
        }
        return false ;
    }
    void user_borrow_book(){
        string NationalIdUser ;
        string nameB ;
        if (!read_name_idUser(NationalIdUser,nameB)){
            cout << "\nTry again later." ;
            return ;
        }
        int IdxOfBook = -1 ;
        for(int i = 0 ; i<BooksSystem.size() ; i++){
            if(BooksSystem[i].GetName() == nameB){
                IdxOfBook = i ;
                break ;
            }
        }
        if (BooksSystem[IdxOfBook].GetTotalQuantity()  <= 0){
            cout << "\nSorry, " << users[NationalIdUser] << " " << nameB << " is out of quantity"  ;
            return ;
        }
        BooksSystem[IdxOfBook].SetTotalBorrowed(1) ;
        BooksSystem[IdxOfBook].SetTotalQuantity(-1) ;
        whoBorrowedBook[nameB].push_back(users[NationalIdUser]) ;
        userBorrowed[NationalIdUser].push_back(nameB) ;
        return ;
    }
    void print_who_borrowed_book_by_name()  {
        string name ;
        cout << "\nEnter book name : " ;
        cin >> name ;
        if (books_in_library.count(name) == 0){
            cout << "\nThis book dosen't exist" ;
            return ;
        }
        if (whoBorrowedBook[name].size() == 0){
            cout << "\nNo borrowed copies" ;
            return ;
        }
        for (int i = 0 ; i<whoBorrowedBook[name].size() ; i++){
            cout << "\n" << whoBorrowedBook[name][i] ;
        }
        return ;
    }
    void user_return_book(){
        string NationalIdUser ;
        string nameB ;
        if (!read_name_idUser(NationalIdUser,nameB)){
            cout << "\nTry again later." ;
            return ;
        }
        int IdxOfBook = -1 ;
        for(int i = 0 ; i<BooksSystem.size() ; i++){
            if(BooksSystem[i].GetName() == nameB){
                IdxOfBook = i ;
                break ;
            }
        }
        auto it = find(userBorrowed[NationalIdUser].begin(),userBorrowed[NationalIdUser].end(),nameB) ;
        if (it == userBorrowed[NationalIdUser].end()){
            cout << "\nYou don't borrow this book" ;
            return ;
        }
        BooksSystem[IdxOfBook].SetTotalBorrowed(-1) ;
        BooksSystem[IdxOfBook].SetTotalQuantity(1) ;
        userBorrowed[NationalIdUser].erase(it) ;
        return ;
    }
    void print_library_by_id()  {
        sort(BooksSystem.begin(),BooksSystem.end(), [](book a, book b){
            return a.GetId() < b.GetId() ;
        });
        for (const book &B : BooksSystem){
            B.print() ;
        }
        return ;
    }
    void print_library_by_name(){
        sort(BooksSystem.begin(),BooksSystem.end(), [](book a, book b){
            return a.GetName() <= b.GetName() ;
        });
        for (const book& B : BooksSystem){
            B.print() ;
        }
        return ;
    }
    void print_users() const {
        for(const auto &p : userBorrowed){
            const string &NationalId = p.first ;
            const string &Name = users.find(NationalId)->second;
            cout << "\nUser " << Name << " National ID  " << NationalId << " borrowed books names :" ;
            for (const string &s : p.second){
                cout << " " << s ;
            }
        }
        return ;
    }
public :
    library_system() : id_book(0){
    }
	void run() {
	    vector<string> menu ;
	    menu.push_back("add_book") ;
	    menu.push_back("search_books_by_prefix") ;
	    menu.push_back("print_who_borrowed_book_by_name") ;
	    menu.push_back("print_library_by_id") ;
	    menu.push_back("print_library_by_name") ;
	    menu.push_back("add_user") ;
	    menu.push_back("user_borrow_book") ;
	    menu.push_back("user_return_book") ;
	    menu.push_back("print_users") ;
	    menu.push_back("Exit") ;
	    while(true){
			 int choice = ShowMenu(menu);
			if (choice == 1)
				add_book();
			else if (choice == 2)
				search_books_by_prefix();
			else if (choice == 3)
				print_who_borrowed_book_by_name();
			else if (choice == 4)
				print_library_by_id();
			else if (choice == 5)
				print_library_by_name();
			else if (choice == 6)
				add_user();
			else if (choice == 7)
				user_borrow_book();
			else if (choice == 8)
				user_return_book();
			else if (choice == 9)
				print_users();
			else
				break;
        }
	}
};

int main()
{
    library_system L ;
   // freopen("input.txt","r",stdin) ;
    L.run() ;
    return 0;
}
