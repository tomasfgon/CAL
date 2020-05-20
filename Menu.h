//
// Created by Tomas Goncalves on 20/05/2020.
//

#ifndef PROJETO_MENU_H
#define PROJETO_MENU_H

#include <iostream>
using namespace std;

class Menu {
private:
    int login;
public:
    Menu();

    int getLogin() const;

    void setLogin(int login);

public:
    bool verifyOption();
    void mainMenu();
    void loginMenu();
};


#endif //PROJETO_MENU_H
