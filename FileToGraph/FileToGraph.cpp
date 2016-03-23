#include "FileToGraph.h"

using namespace std;

void FileToGraph::convertFileToGraph(string fileName, Graph* modify){
  ifstream ifs(fileName);
  stringstream contents;
	contents << ifs.rdbuf();

	string letter;
  string trash;
  int nodes, edges, node1, node2;
  int j = 0;
  while(contents >> letter){
    if(letter == "c"){
      getline(contents, trash);
    }else if(letter == "p"){
      contents >> trash >> nodes >> edges;
      Graph aux(nodes);
      modify->CopyGraph(aux);
    }else if(letter == "e"){
      contents >> node1 >> node2;
      modify->addEdge(node1-1, node2-1);
    }
  }
}
