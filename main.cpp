#include <iostream>
#include "src/Graph.h"

using namespace std;


void mainMenu() {

    int login = -1;

    while(login<=1 && login >=3){
        cout << "\t\t Login\n\n" << endl;
        cout << "1 - Utilizador Municipal - UM" << endl;
        cout << "2 - Utilizador Empreendedor - UE" << endl;
        cout << "3 - Utilizador Particular - UP" << endl;
        cout << "Choose user type" << endl;
        cin>> login;
    }


    int option = -1;

    while (option < 0 || option > 6) {
        cout << "\t\tMain Menu\n\n" << endl;

        cout << "1 - Add Collection Point" << endl;
        cout << "2 - Determine Truck Rout For Waste Collection - UM" << endl;
        cout << "3 - Execute House Waste Collection - UE" << endl;
        cout << "4 - Subscribe to House Waste Collection - UP" << endl;
        cout << "5 - View Closest Collection Points - UP" << endl;
        cout << "0 - Exit\n\n" << endl;


        cin >> option;

        if (option == 0)
            return;
/*
        else if (option == 1)
            //TODO
            else if (option == 2)
            //TODO
                else if (option == 3)
            //TODO
                else if (option == 4)
            //TODO
                else if (option == 5)
            //TODO
*/


        option = -1;
    }
}

int main()
{
    cout << "CAL 2019/2020 - FEUP\n"
            "Tema 2 - WasteAPP\n\n"
            "Miguel Neves\nTomás Freitas\nAbel Tiago\n\n\n";

    //TODO  loadMap();

    mainMenu();

    return 0;
}
