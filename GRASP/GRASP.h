#ifndef GRASP_H
#define GRASP_H

#include "../Graph/Graph.h"
#include <string>
#include "boost/random.hpp"
#include "boost/generator_iterator.hpp"

using namespace std;

struct coloring{
	int color;
	int size;
};

class GRASP{

	multimap<int,int>degreeOrder;
	Graph *G;
public:
    // Constructor and destructor
    GRASP(Graph *Graph){
			this->G = Graph;
			degreeOrder = degreeAskey((*G).nodes);
		}
    ~GRASP()
		{
			degreeOrder.clear();
		}

    void doGrasp(int type, int avoidColor);
		void chooseColor(int node, int avoidColor);
		int pickARandomNumberBetween(int, int);
		int selectNodeColorGrasp(vector<bool> available, vector<int> colorSize, int ignore, int V);

private:
		void FirstFit(int avoidColor);
		void LDO(int avoidColor);
		void SDO(int avoidColor);
		void IDO(int avoidColor);

		multimap<int, int> attDifferentColoredNeighborhood(map<int, int> differentColoredNodes, int node);
		multimap<int, int> attColoredNeighborhood(map<int, int> differentColoredNodes, int node);

    int getColorSize(int, int, int);
		multimap<int, int> degreeAskey(map<int, int> nodes);
};

/*
  Se a cor não for nova cria uma roleta para ela, se for nova
criamos uma roleta para ela com o tamanho de 1 quinto do tamanho
atual da roleta +1, para evitar 0 caso a roleta seja menor que 5.

Cria roleta com peso, quanto mais nós preenchidos tem uma
cor mais chances ela tem de preencher um novo nó.
*/

#endif
