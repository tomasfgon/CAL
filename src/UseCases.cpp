//
// Created by neves on 21/05/2020.
//

#include "UseCases.h"
#include <math.h>
#include <float.h>

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
    vertex->setInfo(&pontoRecolha);

//return false;
return true;
}

bool UseCases::checkConectividade(Graph<VerticeInfo> graph) { //usando dfs

    vector<VerticeInfo> verticesOrdenado = graph.dfs();
    vector<Vertex< VerticeInfo> *> verticesTotais = graph.getVertexSet();


    for(int i = 0; i < graph.getNumVertex(); i++){
        if(!verticesTotais.at(i)->isVisited()){
            return false;
        }
    }

  //para o grafo transposto

    return true;
}

bool UseCases::addRecolhaDomestica(PontoRecolhaDomiciliario &pontoRecolhaDomiciliario, Graph<VerticeInfo> graph){

    //Verifica conectividade
    Graph<VerticeInfo> graphCopy = graph;
    graphCopy.addVertex(&pontoRecolhaDomiciliario);
    if(checkConectividade(graphCopy)){
        graph.addVertex(&pontoRecolhaDomiciliario);
        return true;
    }

    return false;

}


template<typename Base, typename T>
inline bool instanceof(const T*) {
    return std::is_base_of<Base, T>::value;
}

vector<Edge<VerticeInfo>> UseCases::determinarRotaCamioes(PontoPartida pontoPartida, CentroReciclagem centroReciclagem, Graph<VerticeInfo> graph) {

    //1º Detetar todos os contentores que estao acima da taxa viável
    vector<PontoRecolha> pontosParaRecolher = getPontosAcimaTaxaViavel(graph);

    //2º Minimizar o número de camiões a utilizar
    vector<Camiao> camioesNecessarios = calcularCamioesNecessarios(pontosParaRecolher);

    //3º Minimizar a distancia total percorrida
    vector<Edge<VerticeInfo>> edgesOrdered = minimizarDistPercorrida(graph,camioesNecessarios,pontosParaRecolher,pontoPartida,centroReciclagem);


    return edgesOrdered;
}


vector<PontoRecolha> UseCases::getPontosAcimaTaxaViavel(Graph<VerticeInfo> graph) {
    vector<PontoRecolha> pontosParaRecolher; //pontos a recolher
    vector<Vertex<VerticeInfo>*> vertices = graph.getVertexSet();

    for(int i = 0; i < vertices.size(); i++){
        Vertex<VerticeInfo> *vertice = vertices.at(i);
        VerticeInfo *info = vertice->getInfo();
        VerticeInfo* infoP = &*info;

        if(instanceof<PontoRecolha>(infoP)){
            PontoRecolha* pontoRecolha = static_cast<PontoRecolha *>(dynamic_cast<VerticeInfo *>(infoP));
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

    return vector<Camiao>();
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

        lixoPorTipo.push_back(pair<double,TipoLixo> (lixoPapel,papel));
        lixoPorTipo.push_back(pair<double,TipoLixo> (lixoPlastico,plastico));
        lixoPorTipo.push_back(pair<double,TipoLixo> (lixoVidro,vidro));
        lixoPorTipo.push_back(pair<double,TipoLixo> (lixoMetal,metal));
        lixoPorTipo.push_back(pair<double,TipoLixo> (lixoOrganico,organico));
        lixoPorTipo.push_back(pair<double,TipoLixo> (lixoNaoReciclavel,naoReciclavel));




    }
    return lixoPorTipo;
}

vector<Edge<VerticeInfo>>
UseCases::minimizarDistPercorrida(Graph<VerticeInfo> &graph, vector<Camiao> camioesNecessarios,
                                  vector<PontoRecolha> pontosRecolha, PontoPartida pontoPartida, CentroReciclagem centroReciclagem) {

    vector<Edge<VerticeInfo>> edges;

    //para cada tipo de lixo
    vector<Camiao> camiaoDoMsmTipo;
    int tipoLixoAtual = 0;
    for (int i = 0; i < nTiposLixo; i++){

        for(int j = 0; camioesNecessarios.size(); j++){
            if(camioesNecessarios.at(j).getTipoLixo() == tipoLixoAtual){
                camiaoDoMsmTipo.push_back(camioesNecessarios.at(j));
            }
        }


        int nCamiaoMsmTipo = camiaoDoMsmTipo.size();
        //obter o ponto de recolha mais proximo desde o pontoPartida
        VerticeInfo oldPonto = pontoPartida;

        // obter os lixo mais perto uns dos outros
        vector<VerticeInfo> pontosRecolhaMaisProxOrdenados;
        obterPontosRecolhaMaisProximo(pontosRecolha,oldPonto,tipoLixoAtual,graph,pontosRecolhaMaisProxOrdenados);

        //ir buscar as edges apartir dos pontosRecolhaMaisProxOrdenados

        for(int j = 0; j < pontosRecolhaMaisProxOrdenados.size() - 1; j++) {
            VerticeInfo verticeInfo = pontosRecolhaMaisProxOrdenados.at(j);
            Vertex<VerticeInfo>* vertex = graph.findVertex(&verticeInfo);
            VerticeInfo verticeInfoNext = pontosRecolhaMaisProxOrdenados.at(j+1);
            Vertex<VerticeInfo>* vertexNext = graph.findVertex(&verticeInfo);

            for(Edge<VerticeInfo> edge : vertex->getAdj()){
                if(edge.getDest() == vertexNext){

                    edges.push_back(edge);
                }
            }
        }



        tipoLixoAtual++; //alterar para o proximo tipo
        camiaoDoMsmTipo.clear();
    }


    return edges;
}


void UseCases::obterPontosRecolhaMaisProximo(vector<PontoRecolha> pontosRecolha, VerticeInfo oldPonto, int tipoLixoAtual, Graph<VerticeInfo> graph , vector<VerticeInfo> &listToReturn) {

    double minDist = DBL_MAX;
    Vertex<VerticeInfo>* bestVertex;
    for(int j = 0; j < pontosRecolha.size(); j++){
        for(int k = 0; k < pontosRecolha.at(j).getTipoLixo().size(); k++){
            if(pontosRecolha.at(j).getTipoLixo().at(k) == tipoLixoAtual){ //apenas para os pontos de recolha do tipoLixoAtual

                graph.dijkstraShortestPath(oldPonto);
                vector<VerticeInfo> shortestPath = graph.getPath(oldPonto,pontosRecolha.at(j));

                double dist = 0;

                for(VerticeInfo verticeInfo : shortestPath){
                    //ir guardando a soma das distancias
                    Vertex<VerticeInfo>* vertex = graph.findVertex(&verticeInfo);
                    for(Edge<VerticeInfo> edge : vertex->getAdj()){
                        if(edge.getDest() == vertex->getPath()){
                            dist+= edge.getWeight();
                        }
                    }

                    VerticeInfo* verticeInfoptr = &verticeInfo;
                    if(instanceof<PontoRecolha>(verticeInfoptr) && find(listToReturn.begin(), listToReturn.end(), verticeInfo) != listToReturn.end()){ //encontrou o lixo mais perto e ainda nao foi adicionado a lista a retornar

                        if(dist < minDist){
                            minDist = dist;
                            *bestVertex = *vertex;
                        }
                        break;  // ir para outro ponto de recolha
                    }
                }

            }
        }
        minDist = DBL_MAX;
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

        VerticeInfo verticeInfo = *(currentVertex->getInfo());
        VerticeInfo* verticeInfoptr = &verticeInfo;
        if(instanceof<PontoRecolha>(verticeInfoptr)){
            PontoRecolha* pontoRecolha = static_cast<PontoRecolha *>(dynamic_cast<VerticeInfo *>(verticeInfoptr));
            pontosRecolha.push_back(*pontoRecolha);
        }
    }


    return pontosRecolha;
}
