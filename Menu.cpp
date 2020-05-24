//
// Created by Tomas Goncalves on 20/05/2020.
//

#include "Menu.h"
#include "src/UseCases.cpp"


Menu::Menu(Graph<VerticeInfo> graph) : graph(graph) {
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
    cout << "\n\t\tUtilizador Empreendedor\n\n" << endl;

    cout << "1 - Add Collection Point" << endl;
    cout << "2 - Execute House Waste Collection" << endl;
    cout << "3 - Imprimir todos os lixos da rua" << endl;
    cout << "4 - Exit\n\n" << endl;
    cout << endl;
    cout << "Choose option: ";


    cin >> option;

    if(!verifyOption()){
        menuUE();
    }
    if(option <1 || option>4){
        menuUE();
    }

    if(option != 4){
        UseCases useCases;
        if(option == 1){
/*        //criar ponto recolha exemplo
        vector<Vertex<VerticeInfo>*> vertexSet = graph.getVertexSet();
        Vertex<VerticeInfo> *vertex = vertexSet.at(0);
        Coordenadas coordenadas = vertex->getInfo()->getCoordenadas();
        vector<TipoLixo> tiposLixo;
        tiposLixo.push_back(papel);
        tiposLixo.push_back(metal);
        vector<double> capMax;
        capMax.push_back(100);
        capMax.push_back(333);
        PontoRecolha *pontoRecolha = new PontoRecolha(coordenadas, tiposLixo, capMax, vertex->getInfo()->getId());*/


            //Ler ponto de recolha
            cout << "Indique o id do vertice que pertende adicionar como ponto de recolha" << endl;
            int readId;
            cin >> readId;
            cout << "Indique o numero de tipos de lixo que contem:" << endl;
            int numTipo;
            cin >> numTipo;
            cout << "Usando os numeros respetivos aos tipos insira um numero de cada vez seguido de enter" << endl;
            vector<TipoLixo> tiposLixo;
            for(int i = 0; i < numTipo; i++){

                cout << "papel = 0 ,plastico = 1,vidro = 2 ,metal = 3,organico = 4 ,naoReciclavel = 5" << endl;
                int tipo;
                cin >> tipo;
                tiposLixo.push_back(TipoLixo(tipo));
            }
            cout << "Insira agora as capacidades maximas de cada tipo de lixo" << endl;
            vector<double> capMaxes;
            for(int i = 0; i < numTipo; i++){

                cout << "Capacidade do Tipo de lixo " << tiposLixo.at(i) << ":" << endl;
                double capMax;
                cin >> capMax;
                capMaxes.push_back(capMax);
            }
            Coordenadas coordenadasStub(0,0);
            VerticeInfo *verticeInfo = new VerticeInfo(coordenadasStub,readId);
            Vertex<VerticeInfo>* vertex = graph.findVertex(verticeInfo);


            PontoRecolha *pontoRecolha = new PontoRecolha(vertex->getInfo()->getCoordenadas(), tiposLixo, capMaxes, vertex->getInfo()->getId());


            useCases.addPontoRecolha(*pontoRecolha, graph);

            cout << "Operacao realizada com sucesso" << endl;




        } else if (option == 3){
            //print
            vector<PontoRecolha> pontosRecolha = useCases.getAllPontosRecolha(graph);

            for(PontoRecolha pontoRecolhaAtual : pontosRecolha){
                cout << "\nPonto Recolha ID: " << pontoRecolhaAtual.getId() << endl;
                cout << "Coordenada: " << pontoRecolhaAtual.getCoordenadas().getX() << ", " << pontoRecolhaAtual.getCoordenadas().getY() << endl;
                for(TipoLixo tipoLixo : pontoRecolhaAtual.getTipoLixo())
                    cout << "TipoLixo: " << tipoLixo << endl;
                for(double capMax : pontoRecolhaAtual.getCapacidadesMax())
                    cout << "Capacidade Max: " << capMax << endl;



            }
        }
    } else {
        return;
    }


    menuUE();


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

const Graph<VerticeInfo> &Menu::getGraph() const {
    return graph;
}




