#ifndef Graph_H
#define Graph_H
#include <iostream>
#include <list>
#include <vector>
#include <map>
#include <set>
#include <string>

using namespace std;

class Graph{

public:
    int V;                                   // No. de vértives
    int numColors;                           // No. de cores
    vector<int> nodeColor;                   // Cor do vértice
    vector<int> sizeColor;                   // Quantidade de cada cor possível. (Max = V, 1 cor por nó)
    map<int, int> nodes;                     // posição do nó e seu grau
    map<int, int> coloredNodes;              // posição do nó e seu grau com vizinhos coloridos
    map<int, int> differentColoredNodes;     // posição do nó e seu grau com vizinhos coloridos com cores diferentes
    list<int> *adj;
    // Constructor and destructor

    Graph(int V)   {
      this->numColors = 0;
      this->V = V;
      adj = new list<int>[V];
      nodeColor = vector<int>(V, -1);
      sizeColor = vector<int>(V, -1);
    }

    ~Graph()       { delete [] adj; }


    Graph(Graph &Copy)   {
      this->V = Copy.V;
      this->adj = new list<int>[V];

      for(int i = 0; i < V; i++){
        this->adj[i] = Copy.adj[i];
      }
      this->nodeColor = Copy.nodeColor;
      this->sizeColor = Copy.sizeColor;
      this->numColors = Copy.numColors;
      this->nodes = Copy.nodes;
    }

    //Basicão
    void CopyGraph(Graph info);
    void unpaintNode(int node);
    void paintNode(int node, int color);
    void addEdge(int v, int w);

    //Para fazer vizinhanças que levam em conta coisas coloridas
    void getColorsNeighborhood();
    void attNeighborhood(int node);
    int getNumberOfColoredNgb(int node);
    int getNumberOfDiferentColoredNgb(int node);

    //test functions
    void printNodeDegree();
    void printGraphNodesColors();
    void printSizeColor();

  private:
    void updateDegree(int node);
};

#endif
