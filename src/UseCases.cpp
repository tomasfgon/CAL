//
// Created by neves on 21/05/2020.
//

#include "UseCases.h"

bool UseCases::addPontoRecolha(PontoRecolha &pontoRecolha, Graph<VerticeInfo> &graph) {

    //Verifica conectividade
    Graph<VerticeInfo> graphCopy = graph;
    graphCopy.addVertex(pontoRecolha);
    if(checkConectividade(graphCopy)){
        graph.addVertex(pontoRecolha);
        return true;
    }

return false;
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
    graphCopy.addVertex(pontoRecolhaDomiciliario);
    if(checkConectividade(graphCopy)){
        graph.addVertex(pontoRecolhaDomiciliario);
        return true;
    }

    return false;

}
template<typename Base, typename T>
inline bool instanceof(const T*) {
    return std::is_base_of<Base, T>::value;
}

Edge<VerticeInfo> UseCases::determinarRotaCamioes(PontoPartida pontoPartida, CentroReciclagem centroReciclagem, Graph<VerticeInfo> graph) {

    //1º Detetar todos os contentores que estao acima da taxa viável
    vector<VerticeInfo> pontosParaRecolher = getPontosAcimaTaxaViavel(graph);

    //2º Minimizar o número de camiões a utilizar


    return Edge<VerticeInfo>(nullptr, nullptr, 0);
}


vector<VerticeInfo> UseCases::getPontosAcimaTaxaViavel(Graph<VerticeInfo> graph) {
    vector<VerticeInfo> pontosParaRecolher; //pontos a recolher
    vector<Vertex<VerticeInfo>*> vertices = graph.getVertexSet();

    for(int i = 0; i < vertices.size(); i++){
        Vertex<VerticeInfo> *vertice = vertices.at(i);
        VerticeInfo info = vertice->getInfo();
        VerticeInfo* infoP = &info;

        if(instanceof<PontoRecolha>(infoP)){
            PontoRecolha* pontoRecolha = static_cast<PontoRecolha *>(dynamic_cast<VerticeInfo *>(infoP));
            vector<double> taxasOcupacao = pontoRecolha->getTaxasOcupacao();
            for(int j = 0; j < taxasOcupacao.size(); j++) {
                double taxa = taxasOcupacao.at(j);
                if(taxa > taxaViavel)
                    pontosParaRecolher.push_back(*pontoRecolha);
            }
        }
        else if(instanceof<PontoRecolhaDomiciliario>(infoP)){
            PontoRecolhaDomiciliario* pontoRecolhaDomiciliario = static_cast<PontoRecolhaDomiciliario *>(dynamic_cast<VerticeInfo *>(infoP));
            double taxa = pontoRecolhaDomiciliario->getTaxaOcupacao();
            if(taxa > taxaViavel)
                pontosParaRecolher.push_back(*pontoRecolhaDomiciliario);

        }
    }

    return pontosParaRecolher;
}

vector<Camiao> UseCases::calcularCamioesNecessarios(vector<VerticeInfo>) {
    return vector<Camiao>();
}
