//
// Created by Tomas Goncalves on 24/05/2020.
//

#include "PrintGraph.h"



GraphViewer* PrintGraph::create(Graph<VerticeInfo> &g) {

    double height = getMaxY(g) - getMinY(g);
    double width = getMaxX(g) - getMinX(g);

    int graphHeight, graphWidth;
    if(width/height < 2) {
        graphHeight = 600;
        graphWidth = (width * graphHeight) / height;
    }
    else {
        graphWidth = 1500;
        graphHeight = (height * graphWidth) / width;
    }


    auto *gv = new GraphViewer(graphWidth, graphHeight, false);
    gv->defineEdgeCurved(false);
    gv->createWindow(graphWidth, graphHeight);

    gv->defineEdgeColor("black");


    int counter=0;
    for(auto vertex: g.getVertexSet()) {

        if(instanceof<PontoRecolha>(vertex->getInfo())){
            gv->setVertexColor(vertex->getInfo()->getId(),YELLOW);
            gv->setVertexSize(vertex->getInfo()->getId(), 10);
            //cout <<"amarelo" << endl;
        }
        else if(instanceof<PontoRecolhaDomiciliario>(vertex->getInfo())){
            gv->setVertexColor(vertex->getInfo()->getId(),GREEN);
            gv->setVertexSize(vertex->getInfo()->getId(), 10);
            //cout << "vermelho" << endl;
        }
        else if(instanceof<PontoPartida>(vertex->getInfo())){
            gv->setVertexColor(vertex->getInfo()->getId(),RED);
            gv->setVertexSize(vertex->getInfo()->getId(), 10);
            //cout << "cinza" << endl;
        }
        else if(instanceof<CentroReciclagem>(vertex->getInfo())){
            gv->setVertexColor(vertex->getInfo()->getId(),MAGENTA);
            gv->setVertexSize(vertex->getInfo()->getId(), 10);
            //cout << "magenta" << endl;
        }
        else{
            gv->setVertexColor(vertex->getInfo()->getId(),BLUE);
            gv->setVertexSize(vertex->getInfo()->getId(), 5);
            //cout << "azul" << endl;
        }

        double y = (vertex->getInfo()->getCoordenadas().getY() - getMinY(g)) / height;
        double x = (vertex->getInfo()->getCoordenadas().getX() - getMinX(g)) / width;
        gv->addNode(vertex->getInfo()->getId(), (int) (x * graphWidth), (int) (y * graphHeight));





    }

    for(auto vertex: g.getVertexSet()){
        if(!vertex->isVisited()){
            for(auto j: vertex->getAdj()){
                if(!vertex->isVisited()){
                    gv->addEdge(counter++, vertex->getInfo()->getId(), j.getDest()->getInfo()->getId(), EdgeType::UNDIRECTED);
                    vertex->setVisited(true);
                }
            }
        }

    }



    gv->rearrange();
    return gv;

}
