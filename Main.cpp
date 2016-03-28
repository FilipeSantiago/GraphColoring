#include "Graph/Graph.h"
#include "GRASP/GRASP.h"
#include "FileToGraph/FileToGraph.h"
#include "ILS/ILS.h"
#include "Log/Log.h"
#include <vector>
#include <chrono>
#include <ctime>
#include <dirent.h>

using namespace std;
using namespace std::chrono;
/*
g++ -std=c++11 *.cpp Graph/*.cpp GRASP/*.cpp FileToGraph/*.cpp ILS/*.cpp Log/*.cpp -o test
*/

int main(){
  FileToGraph makeGraph;
  Log logGenerator;

  DIR *dir;
  string file = "DSJC125.1.col";
  struct dirent *ent;
  vector<string> files;
  ILS ils;
  Info info(file);
  logGenerator.logInfo.push_back(info);
  Graph base(100);
  makeGraph.convertFileToGraph(string("Graphs/Random/")+file, &base);
  for(int i = 0; i < 20; i++){
    Graph *g1 = new Graph(base);
    GRASP *grasp = new GRASP(g1);
    auto start = std::chrono::high_resolution_clock::now();
    //grasp->doGrasp(1, -1);
    ils.doILS(g1, true, true, true);
    auto elapsed = std::chrono::high_resolution_clock::now() - start;

    long long timeElapsed = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();
    logGenerator.logInfo[0].addExecution(g1->numColors, timeElapsed);
    cout << i << " best = " << g1->numColors << " in " << timeElapsed/1000.0 << " sec" << endl;
    delete g1;
    delete grasp;
  }
  logGenerator.logToFile(file+"result.txt");

  /*




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
  */
	return 0;
}
