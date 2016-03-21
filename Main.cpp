#include "Graph/Graph.h"
#include "GRASP/GRASP.h"
#include "ILS/ILS.h"
#include <vector>

using namespace std;

/*
g++ -std=c++11 *.cpp Graph/*.cpp GRASP/*.cpp -o test
*/

int main(){
  Graph g1(5);
  ILS ils;
  GRASP grasp;
  g1.addEdge(0, 1);
  g1.addEdge(0, 2);
  g1.addEdge(1, 2);
  g1.addEdge(1, 3);
  g1.addEdge(2, 3);
  g1.addEdge(3, 4);
  ils.doILS(&g1, true, false, false);
  g1.printGraphNodesColors();

  Graph g2(5);
  g2.addEdge(0, 1);
  g2.addEdge(0, 2);
  g2.addEdge(1, 2);
  g2.addEdge(1, 4);
  g2.addEdge(2, 4);
  g2.addEdge(4, 3);
  ils.doILS(&g2, true, false, false);
  g2.printGraphNodesColors();
	return 0;
}
