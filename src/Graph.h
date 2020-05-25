/*
 * Graph.h
 */
#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <queue>
#include <limits>
#include <algorithm>
//#include <unordered_set>
#include "MutablePriorityQueue.h"
#include "Dados.h"
#include <iostream>

using namespace std;

template <class T> class Edge;
template <class T> class Graph;
template <class T> class Vertex;

#define INF std::numeric_limits<double>::max()

/************************* Vertex  **************************/

template <class T>
class Vertex {
    T *info;                // contents
    vector<Edge<T> > adj;  // outgoing edges
    bool visited;          // auxiliary field
    double dist = 0;
    Vertex<T> *path = nullptr;
    int queueIndex = 0; 		// required by MutablePriorityQueue

    void addEdge(Vertex<T> *dest, double w);


public:
    Vertex(T *in);
    bool operator<(Vertex<T> & vertex) const; // // required by MutablePriorityQueue
    T* getInfo() const;
    bool isVisited() const;
    double getDist() const;
    Vertex *getPath() const;
    vector<Edge<T>> getAdj() const;
    bool removeEdgeTo(Vertex<T> *d);
    friend class Graph<T>;
    friend class MutablePriorityQueue<Vertex<T>>;

    void setInfo(T *info);
    void setInfo(PontoRecolha *info);
    void setInfo(PontoRecolhaDomiciliario *info);
    void setInfo(PontoPartida *info);
    void setInfo(CentroReciclagem *info);
};


template <class T>
Vertex<T>::Vertex(T *in): info(in) {}

/*
 * Auxiliary function to add an outgoing edge to a vertex (this),
 * with a given destination vertex (d) and edge weight (w).
 */
template <class T>
void Vertex<T>::addEdge(Vertex<T> *d, double w) {
    adj.push_back(Edge<T>(this, d, w));
}

template <class T>
bool Vertex<T>::operator<(Vertex<T> & vertex) const {
    return this->dist < vertex.dist;
}

template<class T>
vector<Edge<T>> Vertex<T>::getAdj() const {
    return adj;
}

template <class T>
bool Vertex<T>::removeEdgeTo(Vertex<T> *d) {
    typename vector<Edge<T> >::iterator it= adj.begin();
    typename vector<Edge<T> >::iterator ite= adj.end();
    while (it!=ite) {
        if (it->dest == d) {
            adj.erase(it);
            return true;
        }
        else it++;
    }
    return false;
}




template <class T>
T* Vertex<T>::getInfo() const {
    return info;
}

template<class T>
void Vertex<T>::setInfo(T *info) {
    T *p = new auto(*info);
    this->info = p;
}

template<class T>
void Vertex<T>::setInfo(PontoRecolha *info) {
    T *p = new PontoRecolha(*info);
    this->info = p;
}

template<class T>
void Vertex<T>::setInfo(PontoRecolhaDomiciliario *info) {
    T *p = new PontoRecolhaDomiciliario(*info);
    this->info = p;
}

template<class T>
void Vertex<T>::setInfo(PontoPartida *info) {
    T *p = new PontoPartida(*info);
    this->info = p;
}

template<class T>
void Vertex<T>::setInfo(CentroReciclagem *info) {
    T *p = new CentroReciclagem(*info);
    this->info = p;
}

template <class T>
bool Vertex<T>::isVisited() const {
    return visited;
}

template <class T>
double Vertex<T>::getDist() const {
    return this->dist;
}

template <class T>
Vertex<T> *Vertex<T>::getPath() const {
    return this->path;
}

/********************** Edge  ****************************/

template <class T>
class Edge {
    Vertex<T> *orig; 	// Fp07
    Vertex<T> * dest;      // destination vertex
    double weight;         // edge weight

    bool selected; // Fp07

public:
    Edge(Vertex<T> *o, Vertex<T> *d, double w);
    friend class Graph<T>;
    friend class Vertex<T>;

    Vertex<T> *getOrig() const;

    Vertex<T> *getDest() const;

    // Fp07
    double getWeight() const;
};

template <class T>
Edge<T>::Edge(Vertex<T> *o, Vertex<T> *d, double w): orig(o), dest(d), weight(w) {}

template <class T>
double Edge<T>::getWeight() const {
    return weight;
}

template<class T>
Vertex<T> *Edge<T>::getOrig() const {
    return orig;
}

template<class T>
Vertex<T> *Edge<T>::getDest() const {
    return dest;
}


/*************************** Graph  **************************/

template <class T>
class Graph {
    vector<Vertex<T> *> vertexSet;    // vertex set

    // Fp05
    Vertex<T> * initSingleSource(const T &orig);
    bool relax(Vertex<T> *v, Vertex<T> *w, double weight);
    double ** W = nullptr;   // dist
    int **P = nullptr;   // path
    int findVertexIdx(const T *in) const;

    void dfsVisit(Vertex<T> *v, vector<T> &res) const;

public:
    Vertex<T> *findVertex(const T *in) const;
    bool addVertex( T *in) ;
    bool addEdge(const T &sourc, const T &dest, double w);
    int getNumVertex() const;
    vector<Vertex<T> *> getVertexSet() const;

    // Fp05 - single source
    void dijkstraShortestPath(const T &s);
    void unweightedShortestPath(const T &s);
    void bellmanFordShortestPath(const T &s);
    vector<T> getPath(const T &origin, const T &dest) const;

    // Fp05 - all pairs
    void floydWarshallShortestPath();
    vector<T> getfloydWarshallPath(const T &origin, const T &dest) const;
    ~Graph();

    // Fp07 - minimum spanning tree
    bool addBidirectionalEdge(const T &sourc, const T &dest, double w);
    vector<Vertex<T>*> calculatePrim();
    vector<Vertex<T>*> calculateKruskal();

    vector<T> dfs() const;
    Graph<T> getTranspose();

};




template <class T>
int Graph<T>::getNumVertex() const {
    return vertexSet.size();
}
/*
// Function that returns reverse (or transpose) of this graph
template <class T>
Graph<T> Graph<T>::getTranspose()
{
    Graph<T> graph = Graph();
    vector<Vertex<T>*> vertexSetCurrent= getVertexSet();
    for (int v = 0; v < getNumVertex(); v++)
    {

        // Recur for all the vertices adjacent to this vertex
        Vertex<T> vertex = *(vertexSetCurrent.at(v));
        vector<Edge<T>> adj = vertex.getAdj();
        for(int i = 0; i != adj.size(); ++i)
        {
            graph.addEdge(,);
        }
    }
    return graph;
}*/

template <class T>
vector<Vertex<T> *> Graph<T>::getVertexSet() const {
    return vertexSet;
}

/*
 * Auxiliary function to find a vertex with a given content.
 */
template <class T>
Vertex<T> * Graph<T>::findVertex(const T *in) const {
    for (Vertex<T> *v : vertexSet)
        if (*(v->getInfo()) == *in)
            return v;
    return nullptr;
}

/*
 * Finds the index of the vertex with a given content.
 */
template <class T>
int Graph<T>::findVertexIdx(const T *in) const {
    /*for (unsigned i = 0; i < vertexSet.size(); i++)
        if (vertexSet.at(i) == *in)
            return i;*/
    return -1;
}
/*
 *  Adds a vertex with a given content or *info (in) to a graph (this).
 *  Returns true if successful, and false if a vertex with that content already exists.
 */
template <class T>
bool Graph<T>::addVertex( T *in) {
    if (findVertex(in) != nullptr)
        return false;
    vertexSet.push_back(new Vertex<T>(in));
    return true;
}

/*
 * Adds an edge to a graph (this), given the contents of the source and
 * destination vertices and the edge weight (w).
 * Returns true if successful, and false if the source or destination vertex does not exist.
 */
template <class T>
bool Graph<T>::addEdge(const T &sourc, const T &dest, double w) {
    auto v1 = findVertex(&sourc);
    auto v2 = findVertex(&dest);
    if (v1 == nullptr || v2 == nullptr)
        return false;
    v1->addEdge(v2, w);
    return true;
}


/**************** Single Source Shortest Path algorithms ************/

/**
 * Initializes single source shortest path data (path, dist).
 * Receives the content of the source vertex and returns a pointer to the source vertex.
 * Used by all single-source shortest path algorithms.
 */
template<class T>
Vertex<T> * Graph<T>::initSingleSource(const T &origin) {
    for(auto v : vertexSet) {
        v->dist = INF;
        v->path = nullptr;
    }
    auto s = findVertex(&origin);
    s->dist = 0;
    return s;
}

/**
 * Analyzes an edge in single source shortest path algorithm.
 * Returns true if the target vertex was relaxed (dist, path).
 * Used by all single-source shortest path algorithms.
 */
template<class T>
inline bool Graph<T>::relax(Vertex<T> *v, Vertex<T> *w, double weight) {
    if (v->dist + weight < w->dist) {
        w->dist = v->dist + weight;
        w->path = v;
        return true;
    }
    else
        return false;
}

template<class T>
void Graph<T>::dijkstraShortestPath(const T &origin) {
    auto s = initSingleSource(origin);
    MutablePriorityQueue<Vertex<T>> q;
    q.insert(s);
    while( ! q.empty() ) {
        auto v = q.extractMin();
        for(auto e : v->adj) {
            auto oldDist = e.dest->dist;
            if (relax(v, e.dest, e.weight)) {
                if (oldDist == INF)
                    q.insert(e.dest);
                else
                    q.decreaseKey(e.dest);
            }
        }
    }
}

template<class T>
vector<T> Graph<T>::getPath(const T &origin, const T &dest) const{
    vector<T> res;
    Vertex<T> *v = findVertex(&dest);
    if (v == nullptr || v->dist == INF) // missing or disconnected
        return res;
    for ( ; v != nullptr; v = v->path)
        res.push_back(*(v->getInfo()));
    reverse(res.begin(), res.end());
    return res;
}

template<class T>
void Graph<T>::unweightedShortestPath(const T &orig) {
    auto s = initSingleSource(orig);
    queue< Vertex<T>* > q;
    q.push(s);
    while( ! q.empty() ) {
        auto v = q.front();
        q.pop();
        for(auto e: v->adj)
            if (relax(v, e.dest, 1))
                q.push(e.dest);
    }
}

template<class T>
void Graph<T>::bellmanFordShortestPath(const T &orig) {
    initSingleSource(orig);
    for (unsigned i = 1; i < vertexSet.size(); i++)
        for (auto v: vertexSet)
            for (auto e: v->adj)
                relax(v, e.dest, e.weight);
    for (auto v: vertexSet)
        for (auto e: v->adj)
            if (relax(v, e.dest, e.weight))
                cout << "Negative cycle!" << endl;
}


/**************** All Pairs Shortest Path  ***************/

template <class T>
void deleteMatrix(T **m, int n) {
    if (m != nullptr) {
        for (int i = 0; i < n; i++)
            if (m[i] != nullptr)
                delete [] m[i];
        delete [] m;
    }
}



template <class T>
Graph<T>::~Graph() {
    deleteMatrix(W, vertexSet.size());
    deleteMatrix(P, vertexSet.size());
}

template<class T>
void Graph<T>::floydWarshallShortestPath() {
/*    unsigned n = vertexSet.size();
    deleteMatrix(W, n);
    deleteMatrix(P, n);
    W = new double *[n];
    P = new int *[n];
    for (unsigned i = 0; i < n; i++) {
        W[i] = new double[n];
        P[i] = new int[n];
        for (unsigned j = 0; j < n; j++) {
            W[i][j] = i == j? 0 : INF;
            P[i][j] = -1;
        }
        for (auto e : vertexSet[i]->adj) {
            int j = findVertexIdx(e.dest->);
            W[i][j]  = e.weight;
            P[i][j]  = i;
        }
    }

    for(unsigned k = 0; k < n; k++)
        for(unsigned i = 0; i < n; i++)
            for(unsigned j = 0; j < n; j++) {
                if(W[i][k] == INF || W[k][j] == INF)
                    continue; // avoid overflow
                int val = W[i][k] + W[k][j];
                if (val < W[i][j]) {
                    W[i][j] = val;
                    P[i][j] = P[k][j];
                }
            }*/
}


template<class T>
vector<T> Graph<T>::getfloydWarshallPath(const T &orig, const T &dest) const{
    vector<T> res;
    /*int i = findVertexIdx(orig);
    int j = findVertexIdx(dest);
    if (i == -1 || j == -1 || W[i][j] == INF) // missing or disconnected
        return res;
    for ( ; j != -1; j = P[i][j])
        res.push_back(vertexSet[j]->*info);
    reverse(res.begin(), res.end());*/
    return res;
}

/**************** Minimum Spanning Tree  ***************/
template <class T>
bool Graph<T>::addBidirectionalEdge(const T &sourc, const T &dest, double w) {
    // TODO
    return false;
}



template <class T>
vector<Vertex<T>* > Graph<T>::calculatePrim() {
    // TODO
    return vertexSet;
}



template <class T>
vector<Vertex<T>*> Graph<T>::calculateKruskal() {
    // TODO
    return vertexSet;
}

/*******************Pesquisa de Vertices**************/

/*
 * Performs a depth-first search (dfs) in a graph (this).
 * Returns a vector with the contents of the vertices by dfs order.
 * Follows the algorithm described in theoretical classes.
 */
template <class T>
vector<T> Graph<T>::dfs() const {
    vector<T> res;
    for (auto v : vertexSet)
        v->visited = false;
    for (auto v : vertexSet)
        if (! v->visited)
            dfsVisit(v, res);
    return res;
}

/*
 * Auxiliary function that visits a vertex (v) and its adjacent, recursively.
 * Updates a parameter with the list of visited node contents.
 */
template <class T>
void Graph<T>::dfsVisit(Vertex<T> *v, vector<T> & res) const {
    v->visited = true;
    res.push_back(*(v->getInfo()));
    for (auto & e : v->adj) {
        auto w = e.dest;
        if ( ! w->visited)
            dfsVisit(w, res);
    }
}


#endif /* GRAPH_H_ */