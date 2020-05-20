//
// Created by Tomas Goncalves on 20/05/2020.
//

#include "Menu.h"

bool Menu::verifyOption(){
    if (!cin.good())
    {
        cout << "Por favor introduza um valor valido";
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        return false;
    }
    else
        return true;
}

void Menu::mainMenu(){
    int option = -1;

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
}

