//
// Created by Tomas Goncalves on 21/05/2020.
//


#include "fileReader.h"


using namespace std;

FileReader::FileReader(Graph<VerticeInfo> &graph, string cidade){
    string low = cidade;
    transform(low.begin(), low.end(), low.begin(), ::tolower);
    cout << "Reading Nodes..." << endl;
    if(!readNodes_simples(graph, "maps/PortugalMaps/"+cidade+"/nodes_x_y_"+low+".txt")){
        cout << "could not read Nodes file" << endl;
        return;
    }

    cout << "Reading Edges..."<<endl;
    if(!readEdges_simples(graph, "maps/PortugalMaps/"+cidade+"/edges_"+low+".txt")){
        cout << "could not read Edges file" << endl;
        return;
    }

    cout << "Reading Tags..."<<endl;
    if(!readTags(graph, "maps/TagExamples/"+cidade+"/t02_tags_"+low+".txt")){
        cout << "could not read Tags file" << endl;
        return;
    }

}

bool FileReader::readNodes_simples(Graph<VerticeInfo> &graph, string nome) {
    int numberNodes;
    string line;


    string filename = nome;
    ifstream file;


    file.open(filename);


    if (file.fail()) {
        cout << "Could not open file "<< filename << endl;
        return false;
    }

    else{
        getline(file, line);

        try{
            numberNodes = stoi(line);
        }
        catch(exception &err)
        {
            cout<<"Conversion error"<<endl;
            return false;
        }


        for(int i=0;i<numberNodes;i++){
            double x,y; int id;
            unsigned sep;

            getline(file, line);

            sep = line.find(',');
            //cout << line.substr(1,sep) << endl;

            try{
                id = stoi(line.substr(1,sep));
            }
            catch(exception &err)
            {
                cout<<"Conversion error"<<endl;
                return false;
            }


            line.erase(0,sep+1);


            sep = line.find(',');

            x = stod(line.substr(0,sep));
            line.erase(0,sep+1);
            //cout << "x: " << x << endl;

            sep = line.find(')');
            y = stod(line.substr(0,sep));
            //cout << "y: "<<y <<endl << endl;




            Coordenadas coordenadas(x,y);
            VerticeInfo *info = new VerticeInfo(coordenadas, id);
            graph.addVertex(info);
        }
        file.close();
        return true;

    }

}

bool FileReader::readEdges_simples(Graph<VerticeInfo> &graph, string nome){
    int numberEdges;
    ifstream file;
    string line;
    string filename = nome;

    file.open(filename);

    if (file.fail()) {
        cout << "Could not open file "<< filename << endl;
        return false;
    }

    else{


        getline(file, line);
        //cout << "number: " << line << endl;
        //numberEdges = stoi(line);

        for(int i=0;i<numberEdges;i++){
            int id1,id2;
            unsigned sep;
            getline(file, line);
            sep = line.find(",");
            try{
                id1 = stoi(line.substr(1, sep));
            }
            catch(exception &err)
            {
                cout<<"Conversion error"<<endl;
                return false;
            }

            //cout << "id1: " << id1 << endl;
            line.erase(0,sep+1);
            sep = line.find(')');

            try{
                id2 = stoi(line.substr(0, sep));
            }
            catch(exception &err)
            {
                cout<<"Conversion error"<<endl;
                return false;
            }



            //cout << "id2: " << id2 << endl << endl;


            Coordenadas coordenadas(0,0);
            VerticeInfo vi1(coordenadas, id1);
            VerticeInfo vi2(coordenadas, id2);

        Vertex<VerticeInfo> *v1 = graph.findVertex(&vi1);
        Vertex<VerticeInfo> *v2 = graph.findVertex(&vi2);




        double x1 = v1->getInfo()->getCoordenadas().getX();
        double y1 = v1->getInfo()->getCoordenadas().getY();
        double x2 = v2->getInfo()->getCoordenadas().getX();
        double y2 = v2->getInfo()->getCoordenadas().getY();



            double distance = sqrt(pow(x2-x1,2) + pow(y2-y1,2));
            //cout << "distance: "<<distance << endl;



        graph.addEdge(*(v1->getInfo()),*(v2->getInfo()), distance);


        }

        file.close();
        return true;
    }
}

bool FileReader::readTags(Graph<VerticeInfo> &graph, string nome) {



    Vertex<VerticeInfo> *vertex;
    int numberTags, numberNodes;

    string TagType;
    ifstream file;
    string line;
    string filename = nome;

    file.open(filename);

    if (file.fail()) {
        cout << "Could not open file "<< filename << endl;
        return false;
    }

    else{
        getline(file, line);
        //cout << "number tags: "<<line << endl;
        numberTags = stoi(line);

        //cout << "number tags: "<< numberTags<<endl;
        for(int i=0;i<numberTags;i++){
            getline(file, TagType);
            TagType = TagType.substr(0,TagType.length()-1);

            //cout << TagType.length() << endl;
            //cout << TagType << endl;


            if(TagType.substr(0, 8) == "amenity="){
                //cout << TagType << endl;
                //cout<< TagType.substr(0,TagType.length()-1) << endl;
                //TagType.erase(0, 8);



                getline(file, line);

                try{
                    numberNodes = stoi(line);
                }
                catch(exception &err)
                {
                    cout<<"Conversion error"<<endl;
                    return false;
                }


                //cout << "Number nodes: " << numberNodes << endl<<endl;
                for(int j=0;j<numberNodes;j++){

                    getline(file, line);

                    try{
                        stoi(line);
                    }
                    catch(exception &err)
                    {
                        cout<<"Conversion error"<<endl;
                        return false;
                    }
                    //cout << line << endl;
                    Coordenadas coordenadas(0,0);
                    VerticeInfo *verticeInfo = new VerticeInfo(coordenadas, stoi(line));
                    vertex = graph.findVertex(verticeInfo);



                    if(TagType == "amenity=waste_basket"){
                        //PontoRecolhaDomiciliaria
                        //cout << "chegou" << endl;
                        vector<TipoLixo> tipos;
                        tipos = VerticeInfo::generateTiposLixo();

                        PontoRecolhaDomiciliario *p = new PontoRecolhaDomiciliario(vertex->getInfo()->getCoordenadas(), tipos, vertex->getInfo()->getId());

                        Vertex<VerticeInfo> *vertex = graph.findVertex(p);
                        vertex->setInfo(p);


                    }
                    else if(TagType == "amenity=recycling"){
                        //PontoRecolha
                        vector<TipoLixo> tipos;
                        tipos = VerticeInfo::generateTiposLixo();
                        vector<double> capMax;
                        for(int j = 0; j < tipos.size(); j++)
                            capMax.push_back(500);

                        PontoRecolha *pontoRecolha = new PontoRecolha(vertex->getInfo()->getCoordenadas(), tipos,
                                                                      capMax, vertex->getInfo()->getId());

                        vertex->setInfo(pontoRecolha);


                    }
                    else if(TagType == "amenity=waste_disposal"){
                        //CentroReciclagem
                        vector<TipoLixo> tipos;
                        tipos = VerticeInfo::generateTiposLixo();

                        CentroReciclagem *p = new CentroReciclagem(vertex->getInfo()->getCoordenadas(), tipos[0], vertex->getInfo()->getId());


                        Vertex<VerticeInfo> *vertex = graph.findVertex(p);
                        vertex->setInfo(p);

                    }
                    else if(TagType == "amenity=waste_transfer_station"){
                        //PontoPartida
                        PontoPartida *p = new PontoPartida(vertex->getInfo()->getCoordenadas(), vertex->getInfo()->getId());


                        Vertex<VerticeInfo> *vertex = graph.findVertex(p);
                        vertex->setInfo(p);


                    }

                }
            }
            else{
                getline(file, line);
                try{
                    numberNodes = stoi(line);
                }
                catch(exception &err)
                {
                    cout<<"Conversion error"<<endl;
                    return false;
                }
                for(int i=0;i<numberNodes;i++) {

                    getline(file, line);
                }
            }
        }
        file.close();
        return true;
    }
}
