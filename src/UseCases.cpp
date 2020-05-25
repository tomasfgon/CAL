//
// Created by neves on 21/05/2020.
//

#include "UseCases.h"
#include <math.h>
#include <float.h>
#include <algorithm>

bool UseCases::addPontoRecolha(PontoRecolha &pontoRecolha, Graph<VerticeInfo> &graph) {

/*    //Verifica conectividade
    Graph<VerticeInfo> graphCopy = graph;
    Vertex<VerticeInfo> *vertex = graphCopy.findVertex(pontoRecolha);
    vertex->setInfo(pontoRecolha);
    if(checkConectividade(graphCopy)){
        graph.findVertex(pontoRecolha);
        Vertex<VerticeInfo> *actualVertex = graph.findVertex(pontoRecolha);
        actualVertex->setInfo(pontoRecolha);
        return true;
    }*/

    Vertex<VerticeInfo> *vertex = graph.findVertex(&pontoRecolha);
    if(checkConectividade(graph,*vertex)){
        vertex->setInfo(&pontoRecolha);
        return true;
    }


    return false;

}

bool UseCases::checkConectividade(Graph<VerticeInfo> graph, Vertex<VerticeInfo> v) { //usando dfs

    vector<VerticeInfo> verticesOrdenado = graph.dfs();

    bool first = false;
    int numOfLixos = 0;
    int totalSizeLixos = 0;
    for(VerticeInfo verticeInfo : verticesOrdenado){
        if(verticeInfo == *(v.getInfo()))
            first = true;
        vector<PontoRecolha> pontosRecolha = getAllPontosRecolha(graph);
        totalSizeLixos = pontosRecolha.size();
        for(PontoRecolha pontoRecolha : pontosRecolha){
            if(verticeInfo == pontoRecolha)
                numOfLixos++;
        }
    }
    return numOfLixos == totalSizeLixos && first;


    //para o grafo transposto

}

bool UseCases::checkConectividadeDomiciliario(Graph<VerticeInfo> graph, Vertex<VerticeInfo> v) { //usando dfs

    vector<VerticeInfo> verticesOrdenado = graph.dfs();

    bool first = false;
    int numOfLixos = 0;
    int totalSizeLixos = 0;
    for(VerticeInfo verticeInfo : verticesOrdenado){
        if(verticeInfo == *(v.getInfo()))
            first = true;
        vector<PontoRecolhaDomiciliario> pontosRecolha = getAllPontosRecolhaDomestica(graph);
        totalSizeLixos = pontosRecolha.size();
        for(PontoRecolhaDomiciliario pontoRecolha : pontosRecolha){
            if(verticeInfo == pontoRecolha)
                numOfLixos++;
        }
    }
    return numOfLixos == totalSizeLixos && first;


    //para o grafo transposto

}
bool UseCases::checkConectividade2Points(Graph<VerticeInfo> graph, Vertex<VerticeInfo> vInicial, Vertex<VerticeInfo> vFinal) {

    vector<VerticeInfo> verticesOrdenado = graph.dfs();

    bool first = false;
    bool second = false;
    int numOfLixos = 0;
    int totalSizeLixos = 0;

    for(VerticeInfo verticeInfo : verticesOrdenado){
        if(verticeInfo == *(vInicial.getInfo())){
            first = true;
        }
        if(first && verticeInfo == *(vFinal.getInfo()))
            second = true;
        vector<PontoRecolha> pontosRecolha = getAllPontosRecolha(graph);
        totalSizeLixos = pontosRecolha.size();
        for(PontoRecolha pontoRecolha : pontosRecolha){
            if(verticeInfo == pontoRecolha)
                numOfLixos++;
        }
    }
    return numOfLixos == totalSizeLixos && first && second;
}

bool UseCases::addRecolhaDomestica(PontoRecolhaDomiciliario &pontoRecolhaDomiciliario, Graph<VerticeInfo> graph){

    Vertex<VerticeInfo> *vertex = graph.findVertex(&pontoRecolhaDomiciliario);
    if(checkConectividadeDomiciliario(graph,*vertex)){
        vertex->setInfo(&pontoRecolhaDomiciliario);
        return true;
    }
    return false;
}

template<typename Base, typename T>
inline bool instanceof(const T *ptr) {
    return dynamic_cast<const Base*>(ptr) != nullptr;
}

/*template<typename Base, typename T>
inline bool instanceof(const T*) {
    return std::is_base_of<Base, T>::value;
}*/

vector<vector<VerticeInfo>> UseCases::determinarRotaCamioes(PontoPartida pontoPartida, CentroReciclagem centroReciclagem, Graph<VerticeInfo> graph) {

    //1º Detetar todos os contentores que estao acima da taxa viável
    vector<PontoRecolha> pontosParaRecolher = getPontosAcimaTaxaViavel(graph);

    //2º Minimizar o número de camiões a utilizar
    vector<Camiao> camioesNecessarios = calcularCamioesNecessarios(pontosParaRecolher);

    //3º Minimizar a distancia total percorrida
    vector<vector<VerticeInfo>> verticesOrdered = minimizarDistPercorrida(graph,camioesNecessarios,pontosParaRecolher,pontoPartida,centroReciclagem);


    return verticesOrdered;
}


vector<PontoRecolha> UseCases::getPontosAcimaTaxaViavel(Graph<VerticeInfo> graph) {
    vector<PontoRecolha> pontosParaRecolher; //pontos a recolher
    vector<Vertex<VerticeInfo>*> vertices = graph.getVertexSet();

    for(int i = 0; i < vertices.size(); i++){
        Vertex<VerticeInfo> *vertice = vertices.at(i);
        VerticeInfo *info = vertice->getInfo();

        if(instanceof<PontoRecolha>(info)){
            auto* pontoRecolha = dynamic_cast<PontoRecolha*>(info);
            vector<double> taxasOcupacao = pontoRecolha->getTaxasOcupacao();
            for(int j = 0; j < taxasOcupacao.size(); j++) {
                double taxa = taxasOcupacao.at(j);
                if(taxa > taxaViavel)
                    pontosParaRecolher.push_back(*pontoRecolha);
            }
        }
    }

    return pontosParaRecolher;
}


vector<Camiao> UseCases::calcularCamioesNecessarios(vector<PontoRecolha> pontosRecolha) {

    vector<Camiao> camioes;

    vector<pair<double,TipoLixo>> lixoPorTipo = calcularLixoTotalPorTipo(pontosRecolha);

    //admitindo que todos os camioes teem a mesma capacidade
    for(int i = 0; i < lixoPorTipo.size(); i++){

        int Ncamiao = ceil(lixoPorTipo.at(i).first / capcidadeMaxCamiao);

        for(int j = 0; j < Ncamiao; j++){
            Camiao c(lixoPorTipo.at(i).second);
            camioes.push_back(c);
        }

    }

    return camioes;
}



vector<pair<double,TipoLixo>> UseCases::calcularLixoTotalPorTipo(vector<PontoRecolha> pontosRecolha) {

    vector<pair<double,TipoLixo>> lixoPorTipo;

    double lixoPapel = 0;
    double lixoPlastico = 0;
    double lixoVidro = 0;
    double lixoMetal = 0;
    double lixoOrganico = 0;
    double lixoNaoReciclavel = 0;


    for(int i = 0; i < pontosRecolha.size(); i++){ // para cada ponto de recolha


        vector<double> taxas = pontosRecolha.at(i).getTaxasOcupacao();
        vector<double> capacidadeMax = pontosRecolha.at(i).getCapacidadesMax();
        vector<TipoLixo> tipos = pontosRecolha.at(i).getTipoLixo();



        for(int j = 0; j < taxas.size(); j++){

            TipoLixo tipo = tipos.at(j);
            switch (tipo){
                case papel:
                    lixoPapel+= taxas.at(j) * capacidadeMax.at(j);
                    break;

                case plastico:
                    lixoPlastico+= taxas.at(j) * capacidadeMax.at(j);
                    break;

                case vidro:
                    lixoVidro+= taxas.at(j) * capacidadeMax.at(j);
                    break;

                case metal:
                    lixoMetal+= taxas.at(j) * capacidadeMax.at(j);
                    break;
                case organico:
                    lixoOrganico+= taxas.at(j) * capacidadeMax.at(j);
                    break;

                case naoReciclavel:
                    lixoNaoReciclavel+= taxas.at(j) * capacidadeMax.at(j);
                    break;
            }


        }

/*
        lixoPorTipo[0] = pair<double,TipoLixo> (lixoPapel,papel);
        lixoPorTipo[1] = pair<double,TipoLixo> (lixoPlastico,plastico);
        lixoPorTipo[2] = pair<double,TipoLixo> (lixoVidro,vidro);
        lixoPorTipo[3] = pair<double,TipoLixo> (lixoMetal,metal);
        lixoPorTipo[4] = pair<double,TipoLixo> (lixoOrganico,organico);
        lixoPorTipo[5] = pair<double,TipoLixo> (lixoNaoReciclavel,naoReciclavel);
*/

    }

    lixoPorTipo.push_back(pair<double,TipoLixo> (lixoPapel,papel));
    lixoPorTipo.push_back(pair<double,TipoLixo> (lixoPlastico,plastico));
    lixoPorTipo.push_back(pair<double,TipoLixo> (lixoVidro,vidro));
    lixoPorTipo.push_back(pair<double,TipoLixo> (lixoMetal,metal));
    lixoPorTipo.push_back(pair<double,TipoLixo> (lixoOrganico,organico));
    lixoPorTipo.push_back(pair<double,TipoLixo> (lixoNaoReciclavel,naoReciclavel));


    return lixoPorTipo;
}

vector<vector<VerticeInfo>>UseCases::minimizarDistPercorrida(Graph<VerticeInfo> &graph, vector<Camiao> camioesNecessarios,
                                                             vector<PontoRecolha> pontosRecolha, PontoPartida pontoPartida, CentroReciclagem centroReciclagem) {

    vector<vector<VerticeInfo>> res;

    //para cada tipo de lixo
    vector<Camiao> camiaoDoMsmTipo;
    int tipoLixoAtual = 0;
    for (int i = 0; i < nTiposLixo; i++){

        for(int j = 0; j < camioesNecessarios.size(); j++){
            if(camioesNecessarios.at(j).getTipoLixo() == tipoLixoAtual){
                camiaoDoMsmTipo.push_back(camioesNecessarios.at(j));
            }
        }


        int nCamiaoMsmTipo = camiaoDoMsmTipo.size();
        //obter o ponto de recolha mais proximo desde o pontoPartida
        VerticeInfo oldPonto = pontoPartida;
        Vertex<VerticeInfo> *debug = graph.findVertex(&pontoPartida);
        VerticeInfo verticeInfoDebug = *(debug->getInfo());

        // obter os lixo mais perto uns dos outros
        vector<VerticeInfo> pontosRecolhaMaisProxOrdenados;
        obterPontosRecolhaMaisProximo(pontosRecolha,oldPonto,tipoLixoAtual,graph,pontosRecolhaMaisProxOrdenados);

        //ultima iteracao para o centro de recolha
        pontosRecolhaMaisProxOrdenados.push_back(centroReciclagem);


        //ir buscar as edges apartir dos pontosRecolhaMaisProxOrdenados
        // edges = getEdgesFromVertexes(pontosRecolhaMaisProxOrdenados,pontosRecolhaMaisProxOrdenados ,graph);

        res.push_back(pontosRecolhaMaisProxOrdenados);



        tipoLixoAtual++; //alterar para o proximo tipo
        camiaoDoMsmTipo.clear();
    }


    return res;
}


void UseCases::obterPontosRecolhaMaisProximo(vector<PontoRecolha> pontosRecolha, VerticeInfo oldPonto, int tipoLixoAtual, Graph<VerticeInfo> graph , vector<VerticeInfo> &listToReturn) {
    Vertex<VerticeInfo> *debug = graph.findVertex(&oldPonto);
    VerticeInfo verticeInfoDebug = *(debug->getInfo());

    double minDist = DBL_MAX;
    Vertex<VerticeInfo> *bestVertex = nullptr;
    graph.dijkstraShortestPath(oldPonto);
    for(int j = 0; j < pontosRecolha.size(); j++){
        for(int k = 0; k < pontosRecolha.at(j).getTipoLixo().size(); k++){
            if(pontosRecolha.at(j).getTipoLixo().at(k) == tipoLixoAtual){ //apenas para os pontos de recolha do tipoLixoAtual


                vector<VerticeInfo> shortestPath = graph.getPath(oldPonto,pontosRecolha.at(j));

                VerticeInfo vert = shortestPath.at(shortestPath.size()-1);
                Vertex<VerticeInfo>* vertptr = graph.findVertex(&vert);
                double dist = vertptr->getDist();

/*                for(VerticeInfo verticeInfo : shortestPath){
                    //ir guardando a soma das distancias
                    Vertex<VerticeInfo>* vertex = graph.findVertex(&verticeInfo);
                    for(Edge<VerticeInfo> edge : vertex->getAdj()){
                        if(*(edge.getDest()->getInfo()) == *(vertex->getPath()->getInfo())){
                            dist+= edge.getWeight();
                        }
                    }
                }*/

                Vertex<VerticeInfo>* vertex = new Vertex<VerticeInfo>(*graph.findVertex(&pontosRecolha.at(j)));
                bool different = true;
                for(VerticeInfo verticeInfo : listToReturn){
                    if(verticeInfo == *(vertex->getInfo()) )
                        different = false;
                }
                if(different){ //encontrou o lixo mais perto e ainda nao foi adicionado a lista a retornar

                    if(dist < minDist){
                        minDist = dist;

                        bestVertex = new Vertex<VerticeInfo>(*vertex);
                    }
                    break;  // ir para outro ponto de recolha
                }

            }
        }

    }

    if(bestVertex == nullptr){
        return;
    }
    listToReturn.push_back(*(bestVertex->getInfo()));
    oldPonto = *(bestVertex->getInfo());
    if(pontosRecolha.size() > listToReturn.size())
        obterPontosRecolhaMaisProximo(pontosRecolha, oldPonto, tipoLixoAtual, graph, listToReturn);
}



vector<PontoRecolha> UseCases::getAllPontosRecolha(Graph<VerticeInfo> graph) {

    vector<PontoRecolha> pontosRecolha;

    vector<Vertex<VerticeInfo>*> vertexSet = graph.getVertexSet();
    for(Vertex<VerticeInfo>* currentVertex : vertexSet){

        VerticeInfo* verticeInfoptr = currentVertex->getInfo();
        if(instanceof<PontoRecolha>(verticeInfoptr)){
            PontoRecolha* pontoRecolha = dynamic_cast<PontoRecolha *>(verticeInfoptr);
            pontosRecolha.push_back(*pontoRecolha);
        }
    }


    return pontosRecolha;
}

vector<PontoRecolhaDomiciliario> UseCases::getAllPontosRecolhaDomestica(Graph<VerticeInfo> graph) {

    vector<PontoRecolhaDomiciliario> pontosRecolha;

    vector<Vertex<VerticeInfo>*> vertexSet = graph.getVertexSet();
    for(Vertex<VerticeInfo>* currentVertex : vertexSet){

        VerticeInfo* verticeInfoptr = currentVertex->getInfo();
        if(instanceof<PontoRecolhaDomiciliario>(verticeInfoptr)){
            PontoRecolhaDomiciliario* pontoRecolha = dynamic_cast<PontoRecolhaDomiciliario *>(verticeInfoptr);
            pontosRecolha.push_back(*pontoRecolha);
        }
    }


    return pontosRecolha;
}

vector<Edge<VerticeInfo>> UseCases::getEdgesFromVertexes(vector<VerticeInfo> verticeInfos,vector<VerticeInfo> pontosRecolha , Graph<VerticeInfo> graph) {

    vector<Edge<VerticeInfo>> edges;
    int numPonto = 0;
    for(int i = 0; i < verticeInfos.size()-1; i++){
        graph.dijkstraShortestPath(verticeInfos.at(i));
        vector<VerticeInfo> vertInfos = graph.getPath(verticeInfos.at(i), pontosRecolha.at(numPonto));
        for(VerticeInfo verticeInfo : vertInfos){
            Vertex<VerticeInfo>* vertex = graph.findVertex(&verticeInfo);
            for(Edge<VerticeInfo> edge : vertex->getAdj()){
                if(*(edge.getDest()->getInfo()) == *(vertex->getPath()->getInfo()))
                    edges.push_back(edge);
            }
        }
    }

    return edges;
}



