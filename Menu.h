//
// Created by Tomas Goncalves on 20/05/2020.
//

#ifndef PROJETO_MENU_H
#define PROJETO_MENU_H

#include <iostream>
#include "src/Dados.h"

using namespace std;

class Menu {
private:
    int login;
    Graph<VerticeInfo> graph;


public:
    Menu(Graph<VerticeInfo> graph);

    int getLogin() const;

    void setLogin(int login);

    const Graph<VerticeInfo> &getGraph() const;

    void setGraph(const Graph<VerticeInfo> &graph);

    string mapa();


public:
    bool verifyOption();
    //void mainMenu(int login);
    void loginMenu();
    void menuUM();
    void menuUP();
    void menuUE();
    void menuAdmin();
    void menuController();

};


#endif //PROJETO_MENU_H
