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

public:
    // Constructor and destructor
    GRASP()   {  }
    ~GRASP()       { }

    void doGrasp(Graph *G, int type, int avoidColor);

private:
		void FirstFit(Graph *G, int avoidColor);
		void LDO(Graph *G, int avoidColor);
		void SDO(Graph *G, int avoidColor);
		void IDO(Graph *G, int avoidColor);

		int selectNodeColorGrasp(vector<bool> available, vector<int> colorSize, int ignore, int V);
    int getColorSize(int, int, int);
    int pickARandomNumberBetween(int, int);
		void chooseColor(Graph *G, int node, int avoidColor);
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
