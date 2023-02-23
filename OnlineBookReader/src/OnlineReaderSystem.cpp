#include "OnlineReaderSystem.h"
#include "Interface.h"
OnlineReaderSystem :: OnlineReaderSystem (){
    adminManager = new AdminManager() ;
    userManager = new UserManager() ;
}
OnlineReaderSystem  :: ~OnlineReaderSystem(){
    cout << "Destructor of OnlineReaderSystem" << endl ;
    if (userManager != nullptr){
        delete userManager ;
        userManager= nullptr ;
    }
    if (adminManager != nullptr){
        delete adminManager ;
        adminManager = nullptr ;
    }
}
void OnlineReaderSystem  :: run(){
    while(true){
        menu = {"Admin","User","Logout"} ;
        int choix = Interface :: ShowMenu(menu) ;
        if (choix == 1){
            adminManager->Access_system() ;
            menu = {"View Profile","Add Book","Logout"} ;
            while(true){
                choix = Interface :: ShowMenu(menu) ;
                if (choix == 1){
                    adminManager->getCurrentAdmin()->to_string() ;
                }else if (choix == 2){
                    adminManager->getCurrentAdmin()->addBook() ;
                }else{
                    system("cls");
                    break ;
                }
            }
        }else if (choix == 2){
            userManager->accesSystem() ;
            menu = {"View Profile","List & Select from My reading History","List & Select from Available Books","Logout"} ;
            while(true){
                choix = Interface :: ShowMenu(menu) ;
                if (choix == 1){
                    userManager->getCurrentUser()->to_string() ;
                }else if (choix == 2){
                    userManager->getCurrentUser()->ListAndSelectFromReadingBookHistory() ;
                }else if (choix == 3){
                    userManager->getCurrentUser()->ListAndSelectFromAvailableBooksToRead() ;
                }else{
                    system("cls");
                    break ;
                }
            }
        }else
            return ;
    }
}


