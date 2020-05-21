//
// Created by Tomas Goncalves on 20/05/2020.
//

#include "Menu.h"

Menu::Menu(){
    loginMenu();
    if(login == 1){menuUM();}

    else if(login ==2){menuUE();}

    else if(login==3){menuUP();}
}

bool Menu::verifyOption(){
    if (!cin.good())
    {
        cout <<"Por favor introduza um valor valido" << endl<<endl;
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        return false;
    }
    else
        return true;
}
/*
void Menu::mainMenu(int login) {
    int option = -1;

    cout << endl << endl;
    cout << "\t\tMain Menu\n\n" << endl;

    cout << "1 - Add Collection Point" << endl;
    cout << "2 - Determine Truck Rout For Waste Collection - UM" << endl;
    cout << "3 - Execute House Waste Collection - UE" << endl;
    cout << "4 - Subscribe to House Waste Collection - UP" << endl;
    cout << "5 - View Closest Collection Points - UP" << endl;
    cout << "6 - Exit\n\n" << endl;
    cout << endl;
    cout << "Choose option: ";


    cin >> option;

    if(!verifyOption()){
    mainMenu();
    }

    if (option == 6){
        exit(0);
    }

    else if (option == 1){

    }
    else if (option == 2){

    }

    else if (option == 3){

    }

    else if (option == 4){

    }

    else if (option == 5){

    }

}
*/


void Menu::loginMenu(){
    int login;


    cout << "\t\t Login\n\n" << endl;
    cout << "1 - Utilizador Municipal - UM" << endl;
    cout << "2 - Utilizador Empreendedor - UE" << endl;
    cout << "3 - Utilizador Particular - UP" << endl;
    cout << endl;
    cout << "Choose user type: ";
    cin>> login;
    if (!verifyOption()){
        loginMenu();
    }
    if(login<1 || login>3){
        cout << endl;
        cout << "Please choose valid option" << endl;
        loginMenu();
    }
    if (verifyOption()){
        this->login = login;
    }

}

int Menu::getLogin() const {
    return login;
}

void Menu::setLogin(int login) {
    Menu::login = login;
}


void Menu::menuUE() {
    int option=-1;

    cout << endl << endl;
    cout << "\t\tUtilizador Empreendedor\n\n" << endl;

    cout << "1 - Add Collection Point" << endl;
    cout << "2 - Execute House Waste Collection" << endl;
    cout << "3 - Exit\n\n" << endl;
    cout << endl;
    cout << "Choose option: ";


    cin >> option;

    if(!verifyOption()){
        menuUE();
    }
    if(option <1 || option>3){
        menuUE();
    }


}

void Menu::menuUP() {int option=-1;

    cout << endl << endl;
    cout << "\t\tUtilizador Particular\n\n" << endl;

    cout << "1 - Add Collection Point" << endl;
    cout << "2 - Subscribe to House Waste Collection" << endl;
    cout << "3 - View Closest Collection Points" << endl;
    cout << "4 - Exit\n\n" << endl;
    cout << endl;
    cout << "Choose option: ";


    cin >> option;

    if(!verifyOption()){
        menuUP();
    }
    if(option <1 || option>4){
        menuUP();
    }}

void Menu::menuUM() {

    int option;
    cout << endl << endl;
    cout << "\t\tUtilizador Municipal\n\n" << endl;

    cout << "1 - Add Collection Point" << endl;
    cout << "2 - Determine Truck Rout For Waste Collection" << endl;
    cout << "3 - Exit\n\n" << endl;
    cout << endl;
    cout << "Choose option: ";


    cin >> option;

    if(!verifyOption()){
        menuUM();
    }
    if(option <1 || option>3){
        menuUM();
    }}