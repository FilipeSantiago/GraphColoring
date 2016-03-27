#include "Graph.h"

using namespace std;

/*----------------------------Basicão--------------------------------*/
void Graph::CopyGraph(Graph info){
  this->V = info.V;
  this->adj = new list<int>[V];

  for(int i = 0; i < V; i++){
    this->adj[i] = info.adj[i];
  }
  this->nodeColor = info.nodeColor;
  this->sizeColor = info.sizeColor;
  this->numColors = info.numColors;
  this->nodes = info.nodes;
}

void Graph::addEdge(int v, int w){
    adj[v].push_back(w);
    adj[w].push_back(v);
    updateDegree(v);
    updateDegree(w);
}

void Graph::updateDegree(int node){
  map<int,int>::iterator it;

  it = nodes.find(node);
  if (it != nodes.end()) nodes[node]++;
  else nodes.insert(pair<int,int>(node, 1));
}

void Graph::unpaintNode(int node){
  this->sizeColor[this->nodeColor[node]]--;
  if(this->sizeColor[this->nodeColor[node]] <= 0) this->numColors--;
  /*cout << "nó = " << node << " cor = " << nodeColor[node] << " tam da cor = " << sizeColor[nodeColor[node]] << endl
       << "no de cores = " << numColors << endl;*/
  this->nodeColor[node] = -1;
}

void Graph::paintNode(int node, int color){
  if(nodeColor[node] != -1) {
    //cout << "Nunca passa aqui" << endl;
    sizeColor[nodeColor[node]]--; //Se tinha uma cor antes, diminui o nº dessa cor.
    if(sizeColor[nodeColor[node]] == 0) numColors--;
  }
  nodeColor[node] = color; //Associa nova cor
  if(sizeColor[color] == -1 || sizeColor[color] == 0){
    sizeColor[color] = 1; //Incrementa nova cor.
    numColors++;
  }
  else sizeColor[color]++;
}

/*----------------------------Pra fazer vizinhança colorida--------------------------------*/
void Graph::getColorsNeighborhood(){
  for(int i = 0; i < V; i++){
    coloredNodes.insert(pair<int,int>(i, 0));           //Inicializa com 0, caso não tenha vizinhos coloridos
    differentColoredNodes.insert(pair<int,int>(i, 0));
    attNeighborhood(i);
  }
}

void Graph::attNeighborhood(int node){
  int colored;
  int differentColors;
  list<int>::iterator i;
  for (i = adj[node].begin(); i != adj[node].end(); ++i){
    map<int,int>::iterator it;
    //Atualiza n vizinhos coloridos
    colored = getNumberOfColoredNgb(*i);
    it = coloredNodes.find(node);
    if (it != coloredNodes.end()) coloredNodes[node] = colored;
    else coloredNodes.insert(pair<int,int>(node, colored));
    //Atualiza n vizinhos com cores diferentes
    differentColors = getNumberOfDiferentColoredNgb(*i);
    it = differentColoredNodes.find(node);
    if (it != differentColoredNodes.end()) differentColoredNodes[node] = differentColors;
    else differentColoredNodes.insert(pair<int,int>(node, differentColors));
  }
}

int Graph::getNumberOfColoredNgb(int node){
  int response = 0;
  for(int i = 0; i < adj[node].size(); i++){
    if(nodeColor[i] != -1 && nodeColor[i] != 0) response++;
  }
  return response;
}

int Graph::getNumberOfDiferentColoredNgb(int node){
  set<int> colors;
  for(int i = 0; i < adj[node].size(); i++){
    if(nodeColor[i] != -1 && nodeColor[i] != 0) colors.insert(nodeColor[i]);
  }
  return colors.size();
}

int Graph::GetColorOfNgbWithLessConflicts(int node){
  // cout << "entra aqui" << endl;
   int lessConflict = INT_MAX;
   int resp = -1;
   for(int i = 0; i < adj[node].size(); i++){
     set<int> colors;
     if(adj[i].size() <= 0) cout << "EWWWWWWWWWWWWWWWWW" << endl;
     for(int j = 0; j < adj[i].size(); j++){
       if(nodeColor[j] != -1 && nodeColor[j] != 0) colors.insert(nodeColor[j]);
     }
     if(lessConflict > colors.size()){
       lessConflict = colors.size();
       resp = nodeColor[i];
     }
  }
//  cout << "sai aqui " << resp << endl;
  return resp;
}


/*----------------------------Imprimir as paradas--------------------------------*/
void Graph::printGraphNodesColors(){
  cout << "Node color : ";
  for(int i = 0; i < V; i++){
    cout << nodeColor[i] << " ";
  }
  cout << endl;
}

void Graph::printNodeDegree(){
  cout << "Nodes Degree : ";
  map<int, int>::iterator it;
  for (it = nodes.begin(); it != nodes.end(); ++it){
    cout << it->second << " ";
  }
  cout << endl;
}

void Graph::printSizeColor(){
  cout << "Size color : ";
  for(int i = 0; i < V; i++){
    cout << sizeColor[i] << " ";
  }
  cout << endl;
}
