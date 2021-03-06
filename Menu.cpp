//
// Created by Tomas Goncalves on 20/05/2020.
//

#include "Menu.h"
#include "src/UseCases.cpp"
#include "src/fileReader.cpp"
#include "src/PrintGraph.cpp"


Menu::Menu(Graph<VerticeInfo> graph) : graph(graph) {
/*<<<<<<< HEAD

    string cidade = mapa();

    FileReader fileReader(graph, cidade);


=======*/

    string cidade = mapa();
    string low = cidade;
    transform(low.begin(), low.end(), low.begin(), ::tolower);
    FileReader fileReader(graph, cidade);


    PrintGraph::image = "maps/strong"+cidade+"/"+low+"_strong_component.png";
    setGraph(graph);
    while(login != -1)
        menuController();
}

void Menu::menuController() {


    loginMenu();
    if(login == 1){menuUM();}

    else if(login ==2){menuUE();}

    else if(login==3){menuUP();}

    else if(login == 4){menuAdmin();}

    if(login == -1)
        return;
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



string Menu::mapa(){
    int login;
    cout << "\t\t Map\n\n" << endl;
    cout << "1 - Espinho" << endl;
    cout << "2 - Penafiel" << endl;
    cout << "3 - Porto" << endl;
    cout << "4 - Exit" << endl;
    cout << endl;
    cout << "Choose user type: ";
    cin>> login;
    if (!verifyOption()) {
        return mapa();
    }
    if(login<1 || login>4){
        cout << endl;
        cout << "Please choose valid option" << endl;
        return mapa();
    }
    if (!verifyOption()){
        cout << endl;
        cout << "Please choose valid option" << endl;
        return mapa();
    }
    if(login==1){
        return "Espinho";
    }
    else if(login == 2){
        return "Penafiel";
    }
    else if(login == 3){
        return "Porto";
    }
    else if(login == 4){
        exit(0);
    }


}

void Menu::loginMenu(){
    int login;

    cout << "\t\t Login\n\n" << endl;
    cout << "1 - Utilizador Municipal - UM" << endl;
    cout << "2 - Utilizador Empreendedor - UE" << endl;
    cout << "3 - Utilizador Particular - UP" << endl;
    cout << "4 - Admin" << endl;
    cout << "5 - Exit" << endl;
    cout << endl;
    cout << "Choose user type: ";
    cin>> login;
    if (!verifyOption()){
        loginMenu();
    }
    if(login<1 || login>5){
        cout << endl;
        cout << "Please choose valid option" << endl;
        loginMenu();
    }
    if (verifyOption()){
        this->login = login;
    }
    if(login == 5){
        this->login = -1;
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

    cout << "1 - Execute House Waste Collection" << endl;
    cout << "2 - Exit\n\n" << endl;
    cout << endl;
    cout << "Choose option: ";


    cin >> option;

    if(!verifyOption()){
        menuUE();
    }
    if(option <1 || option>2){
        menuUE();
    }

    if(option != 2){
        UseCases useCases;
        if(option == 1){

            //escolher ponto de partida e de chegada
            cout << "Indique o id do seu ponto de partida" << endl;
            int idPartida;
            cin >> idPartida;
            cout << "Indique o id da Central de Recolha na qual depositar o lixo" << endl;
            int idCentral;
            cin >> idCentral;

            Coordenadas coordenadasStub(0,0);
            PontoPartida *pontoPartida = new PontoPartida(coordenadasStub,idPartida);

            CentroReciclagem *centroReciclagem = new CentroReciclagem(coordenadasStub,idCentral);

            cout << "Indique a sua capacidade maxima de Recolha" << endl;
            double capRecolha;
            cin >> capRecolha;

            vector<VerticeInfo> caminhos = useCases.determinarRotaUE(*pontoPartida,*centroReciclagem,capRecolha,graph);

            for(VerticeInfo caminho: caminhos){
                cout << "\nPonto Recolha ID: " << caminho.getId() << endl;
                cout << "Coordenada: " << caminho.getCoordenadas().getX() << ", "
                     << caminho.getCoordenadas().getY() << endl;
            }




            Graph<VerticeInfo> graph;
            for(int i=0;i<caminhos.size();i++){
                graph.addVertex(&caminhos[i]);
            }

            PrintGraph printGraph;
            printGraph.useCase4(graph);
        }



    } else {

        return;
    }


    menuUE();


}


void Menu::menuUP() {int option=-1;

    cout << endl << endl;
    cout << "\t\tUtilizador Particular\n\n" << endl;

    cout << "1 - Subscrever a colecao de lixo caseiro" << endl;
    cout << "2 - Visualizar Pontos de Lixo mais proximos" << endl;
    cout << "3 - Exit\n\n" << endl;

    cout << endl;
    cout << "Choose option: ";


    cin >> option;

    if(!verifyOption()){
        menuUP();
    }
    if(option <1 || option>3){
        menuUP();
    }

    if(option != 3){
        UseCases useCases;
        if(option == 1){
            //Ler ponto de recolha Domestica
            cout << "Indique o id do vertice que pertende adicionar como ponto de recolha domiciliaria" << endl;
            int readId;
            cin >> readId;
            cout << "Indique o numero de tipos de lixo que contem:" << endl;
            int numTipo;
            cin >> numTipo;
            cout << "Usando os numeros respetivos aos tipos insira um numero de cada vez seguido de enter" << endl;
            vector<TipoLixo> tiposLixo;
            for (int i = 0; i < numTipo; i++) {

                cout << "papel = 0 ,plastico = 1,vidro = 2 ,metal = 3,organico = 4 ,naoReciclavel = 5" << endl;
                int tipo;
                cin >> tipo;
                tiposLixo.push_back(TipoLixo(tipo));
            }
            cout << "Insira agora as capacidades maximas de cada tipo de lixo" << endl;
            vector<double> capMaxes;
            for (int i = 0; i < numTipo; i++) {

                cout << "Capacidade do Tipo de lixo " << tiposLixo.at(i) << ":" << endl;
                double capMax;
                cin >> capMax;
                capMaxes.push_back(capMax);
            }
            Coordenadas coordenadasStub(0, 0);
            VerticeInfo *verticeInfo = new VerticeInfo(coordenadasStub, readId);
            Vertex<VerticeInfo> *vertex = graph.findVertex(verticeInfo);


            PontoRecolhaDomiciliario *pontoRecolha = new PontoRecolhaDomiciliario(vertex->getInfo()->getCoordenadas(), tiposLixo, capMaxes,
                                                                                  vertex->getInfo()->getId());


            if (useCases.addRecolhaDomestica(*pontoRecolha, graph)) {
                cout << "\nOperacao realizada com sucesso" << endl;
            } else {
                cout << "\nNao foi possivel realizar a adicao, ponto nao conexo" << endl;
            }
        } else if(option == 2){


            cout << "Indique qual o seu local atual através do id do vertice mais proximo de si: " << endl;
            int idLocal;
            cin >> idLocal;
            Coordenadas coordenadas(0,0);
            VerticeInfo pontoAtual(coordenadas, idLocal);
            Graph<VerticeInfo> graph1;
            PrintGraph printGraph;
            graph1.addVertex(&pontoAtual);


            cout << "Indique o numero de tipos de lixo que contem:" << endl;
            int numTipo;
            cin >> numTipo;
            cout << "Usando os numeros respetivos aos tipos insira um numero de cada vez seguido de enter" << endl;
            vector<TipoLixo> tiposLixo;
            for (int i = 0; i < numTipo; i++) {

                cout << "papel = 0 ,plastico = 1,vidro = 2 ,metal = 3,organico = 4 ,naoReciclavel = 5" << endl;
                int tipo;
                cin >> tipo;
                tiposLixo.push_back(TipoLixo(tipo));



                vector<PontoRecolha> pontosRecolha = useCases.getAllPontosRecolha(graph);
                vector<VerticeInfo> listToReturn;
                useCases.obterPontosRecolhaMaisProximo(pontosRecolha, pontoAtual, TipoLixo(tipo), graph, listToReturn);
                cout << "Pontos de recolha na vizinhanca para este tipo de lixo: \n" << endl;


                for(int k=0;k<listToReturn.size();k++){
                    cout << "\nPonto Recolha ID: " << listToReturn[i].getId() << endl;
                    cout << "Coordenada: " << listToReturn[i].getCoordenadas().getX() << ", "
                         << listToReturn[i].getCoordenadas().getY() << endl;

                    if(i==0){


                        graph1.addVertex(&listToReturn[i]);



                    }
                }
                TipoLixo t = TipoLixo(tipo);
                printGraph.useCase6(graph1, pontoAtual, t);
            }




        }
    } else {
        return;
    }

    menuUP();


}

void Menu::menuUM() {

    int option;
    cout << endl << endl;
    cout << "\t\tUtilizador Municipal\n\n" << endl;

    cout << "1 - Determine Truck Route For Waste Collection" << endl;
    cout << "2 - Exit\n\n" << endl;
    cout << endl;
    cout << "Choose option: ";


    cin >> option;

    if(!verifyOption()){
        menuUM();
    }
    if(option <1 || option>2){
        menuUM();
    }

    if(option != 2){
        UseCases useCases;
        if(option == 1){

            //escolher ponto de partida e de chegada
            cout << "Indique o id do ponto de partida dos camioes" << endl;
            int idPartida;
            cin >> idPartida;
            cout << "Indique o id da Central de Recolha na qual depositar o lixo" << endl;
            int idCentral;
            cin >> idCentral;

            Coordenadas coordenadasStub(0,0);
            PontoPartida *pontoPartida = new PontoPartida(coordenadasStub,idPartida);

            CentroReciclagem *centroReciclagem = new CentroReciclagem(coordenadasStub,idCentral);

            Vertex<VerticeInfo>* vInicial = graph.findVertex(pontoPartida);
            Vertex<VerticeInfo>* vFinal = graph.findVertex(centroReciclagem);


/*            if(!useCases.checkConectividade2Points(graph,*vInicial,*vFinal)){
           //if(false){
                cout << "Nao conexos" << endl;
                menuUM();
            } else {*/



                vector<vector<VerticeInfo>> caminhos = useCases.determinarRotaCamioes(*pontoPartida,*centroReciclagem,graph);


                if(caminhos.empty()){
                    cout << "\nNao e necessario recolher lixos, esta tudo abaixo da taxa viavel de recolha" << endl;
                } else {

                    for(int j = 0; j < nTiposLixo; j++){

                        cout << "\nCaminho de contentores a percorrer para o : " << TipoLixo(j) << "\n" << endl;
                        for(int k = 0; k<caminhos.at(j).size();k++){
                            cout << "ID : " << caminhos.at(j).at(k).getId() << "    Coordenadas: " << caminhos.at(j).at(k).getCoordenadas().getX() << ", " << caminhos.at(j).at(k).getCoordenadas().getY() << endl;
                        }

                    }
                    cout << "\nOperacao realizada com sucesso" << endl;
                }

                Graph<VerticeInfo> graph2;
                /*
                for(VerticeInfo verticeInfo: caminhos[0]){
                    graph2.addVertex(&verticeInfo);
                }
                PrintGraph printGraph;
                printGraph.create(graph2);
                 */
        }


    } else {
        return;
    }

    menuUM();

}

const Graph<VerticeInfo> &Menu::getGraph() {
    return graph;
}

void Menu::menuAdmin() {

int option = -1;

    cout << endl << endl;
    cout << "\n\t\tAdmin\n\n" << endl;

    cout << "1 - Add Collection Point" << endl;
    cout << "2 - Imprimir todos os lixos de rua" << endl;
    cout << "3 - Imprimir todos os lixos domiciliarios" << endl;
    cout << "4 - Imprimir grafo da cidade" << endl;
    cout << "5 - Back\n\n" << endl;
    cout << endl;
    cout << "Choose option: ";


    cin >> option;

    if (!verifyOption()) {
        menuAdmin();
    }
    if (option < 1 || option > 5) {
        menuAdmin();
    }

    if (option != 5) {
        UseCases useCases;

        if (option == 1) {

            //Ler ponto de recolha
            cout << "Indique o id do vertice que pertende adicionar como ponto de recolha" << endl;
            int readId;
            cin >> readId;
            cout << "Indique o numero de tipos de lixo que contem:" << endl;
            int numTipo;
            cin >> numTipo;
            cout << "Usando os numeros respetivos aos tipos insira um numero de cada vez seguido de enter" << endl;
            vector<TipoLixo> tiposLixo;
            for (int i = 0; i < numTipo; i++) {

                cout << "papel = 0 ,plastico = 1,vidro = 2 ,metal = 3,organico = 4 ,naoReciclavel = 5" << endl;
                int tipo;
                cin >> tipo;
                tiposLixo.push_back(TipoLixo(tipo));
            }
            cout << "Insira agora as capacidades maximas de cada tipo de lixo" << endl;
            vector<double> capMaxes;
            for (int i = 0; i < numTipo; i++) {

                cout << "Capacidade do Tipo de lixo " << tiposLixo.at(i) << ":" << endl;
                double capMax;
                cin >> capMax;
                capMaxes.push_back(capMax);
            }
            Coordenadas coordenadasStub(0, 0);
            VerticeInfo *verticeInfo = new VerticeInfo(coordenadasStub, readId);
            Vertex<VerticeInfo> *vertex = graph.findVertex(verticeInfo);


            PontoRecolha *pontoRecolha = new PontoRecolha(vertex->getInfo()->getCoordenadas(), tiposLixo, capMaxes,
                                                          vertex->getInfo()->getId());


            if (useCases.addPontoRecolha(*pontoRecolha, graph)) {
                cout << "\nOperacao realizada com sucesso" << endl;
            } else {
                cout << "\nNao foi possivel realizar a adicao, ponto nao conexo" << endl;
            }


        } else if (option == 2) {
            //print pontos de recolha
            vector<PontoRecolha> pontosRecolha = useCases.getAllPontosRecolha(graph);

            for (PontoRecolha pontoRecolhaAtual : pontosRecolha) {
                cout << "\nPonto Recolha ID: " << pontoRecolhaAtual.getId() << endl;
                cout << "Coordenada: " << pontoRecolhaAtual.getCoordenadas().getX() << ", "
                     << pontoRecolhaAtual.getCoordenadas().getY() << endl;
                for (TipoLixo tipoLixo : pontoRecolhaAtual.getTipoLixo())
                    cout << "TipoLixo: " << tipoLixo << endl;
                for (double capMax : pontoRecolhaAtual.getCapacidadesMax())
                    cout << "Capacidade Max: " << capMax << endl;

            }

        } else if (option == 3) {
            //print pontos de recolha domiciliarios
            vector<PontoRecolhaDomiciliario> pontosRecolha = useCases.getAllPontosRecolhaDomestica(graph);

            for (PontoRecolhaDomiciliario pontoRecolhaAtual : pontosRecolha) {
                cout << "\nPonto Recolha ID: " << pontoRecolhaAtual.getId() << endl;
                cout << "Coordenada: " << pontoRecolhaAtual.getCoordenadas().getX() << ", "
                     << pontoRecolhaAtual.getCoordenadas().getY() << endl;
                for (TipoLixo tipoLixo : pontoRecolhaAtual.getTipoLixo())
                    cout << "TipoLixo: " << tipoLixo << endl;
                for (double capMax : pontoRecolhaAtual.getCapacidadesMax())
                    cout << "Capacidade Max: " << capMax << endl;

            }

        }
        else if(option == 4){
            PrintGraph printGraph;
            printGraph.create(graph);
        }
    }

    else {
        return;
    }
    menuAdmin();
}

void Menu::setGraph(const Graph<VerticeInfo> &graph) {
    Menu::graph = graph;
}






