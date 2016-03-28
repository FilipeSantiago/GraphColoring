#ifndef ILS_H
#define ILS_H

#include "../Graph/Graph.h"
#include "../GRASP/GRASP.h"
#include <string>
#include <iostream>
#include <list>
#include <vector>
#include <string>
#include <algorithm>
#include "boost/random.hpp"
#include "boost/generator_iterator.hpp"

using namespace std;

class ILS{

public:
    void doILS(Graph *G, bool recoloring, bool forceColor, bool switchColors);

private:
    void shake1(Graph* G);
    void recoloring (Graph *G);
    void forceColor (Graph *G);
    void initialize (Graph *G);
    void changeColor(Graph *G);
    void resolveConflicts(Graph *G,int node, int color, int deep);
    int  getPossibleColor(Graph* G, int node, int avoidColor);

};

#endif
