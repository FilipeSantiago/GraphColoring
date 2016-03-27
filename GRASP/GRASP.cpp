#include "GRASP.h"

//Grafo, tipo de GRASP, se o grafo está "incolor"
void GRASP::doGrasp(int type, int avoidColor){
  switch (type) {
    case 1:
      LDO(avoidColor);
      break;
    case 2:
      SDO(avoidColor);
      break;
    case 3:
      IDO(avoidColor);
      break;
    default:
      FirstFit(avoidColor);
  }
}

void GRASP::FirstFit(int avoidColor){
  for (int node = 0; node < (*G).V; node++){
    if((*G).nodeColor[node] == -1){
      chooseColor(node, avoidColor);
    }
  }
}

void GRASP::LDO(int avoidColor){
  multimap<int, int>::iterator it;
  for (it = prev(degreeOrder.end()); it != prev(degreeOrder.begin()); --it){
    int node = it->second;
    if((*G).nodeColor[node] == -1){
      chooseColor(node, avoidColor);
    }
  }
}

void GRASP::SDO(int avoidColor){
  (*G).getColorsNeighborhood();
  map<int,int> coloredNodes = (*G).differentColoredNodes;
  multimap<int,int>degreeOrder = degreeAskey(coloredNodes);
  multimap<int, int>::iterator it;
  while (degreeOrder.size() > 0){
    it = prev(degreeOrder.end());
    int node = it->second;
    if((*G).nodeColor[node] == -1){
      chooseColor(node, avoidColor);
      coloredNodes.erase(coloredNodes.find(node));
      degreeOrder = attDifferentColoredNeighborhood(coloredNodes,node);
    }else{
      coloredNodes.erase(coloredNodes.find(node));
    }
  }
}

multimap<int, int> GRASP::attDifferentColoredNeighborhood(map<int, int> differentColoredNodes, int node){
  int colored;
  int differentColors;
  list<int>::iterator i;
  map<int,int>::iterator it;
  for (i = (*G).adj[node].begin(); i != (*G).adj[node].end(); ++i){
    differentColors = (*G).getNumberOfDiferentColoredNgb(*i);
    it = differentColoredNodes.find(node);
    if (it != differentColoredNodes.end()) differentColoredNodes[node] = differentColors;
  }
  return degreeAskey(differentColoredNodes);
}

void GRASP::IDO(int avoidColor){
  (*G).getColorsNeighborhood();
  map<int,int> coloredNodes = (*G).differentColoredNodes;
  multimap<int,int>degreeOrder = degreeAskey(coloredNodes);
  map<int, int>::iterator it;
  while (degreeOrder.size() > 0){
    it = prev(degreeOrder.end());
    int node = it->second;
    if((*G).nodeColor[node] == -1){
      chooseColor(node, avoidColor);
      coloredNodes.erase(coloredNodes.find(node));
      degreeOrder = attColoredNeighborhood(coloredNodes,node);
    }else{
      coloredNodes.erase(coloredNodes.find(node));
    }
  }
}

multimap<int, int> GRASP::attColoredNeighborhood(map<int, int> coloredNodes, int node){
  int colored;
  list<int>::iterator i;
  map<int,int>::iterator it;
  for (i = (*G).adj[node].begin(); i != (*G).adj[node].end(); ++i){
    colored = (*G).getNumberOfColoredNgb(*i);
    it = coloredNodes.find(node);
    if (it != coloredNodes.end()) coloredNodes[node] = colored;
  }
  return degreeAskey(coloredNodes);
}


int GRASP::selectNodeColorGrasp(vector<bool> available, vector<int> colorSize,
                                int ignore, int GraphSize){
	vector<coloring> possibleColors;
    int sumColorsSize = 0, j = 0, newColor = -1, firstNumber = 0;
    for (int k = 0; k < GraphSize; k++){//Cores possíveis
      int i = k;
      coloring build;
    	if(i != ignore){
	    	if (available[i] && j < 3){
          if(j > 0){
            firstNumber = possibleColors[j-1].size;
          }
	    		build.color = i;
          build.size = GRASP::getColorSize(colorSize[i], firstNumber, j);
          possibleColors.push_back(build);
          j++;
          if(colorSize[i] <= 0) break;
        }else if(j >= 3) break;
      }
    }
    int pos = GRASP::pickARandomNumberBetween(0, possibleColors[possibleColors.size() - 1].size);
  	for (int i = 0; i <= j; ++i)
  		if(possibleColors[i].size >= pos) return possibleColors[i].color;
}

int GRASP::getColorSize(int colorSize, int firstNumber, int j){
  //range para sorteio da cor será firstNumber ~ lastNumber.
  int lastNumber = 1; //Valor mínimo para o tamanho
  if(colorSize > 0){ //Se a cor não é nova
    lastNumber += colorSize;
    if(j > 0) lastNumber += firstNumber;
  }else{
    lastNumber += (lastNumber/5);
    if(j > 0) lastNumber += firstNumber;
  }
  return lastNumber;
}

int GRASP::pickARandomNumberBetween(int begin, int end){
  typedef boost::mt19937 RNGType;
  RNGType rng;
  rng.seed(std::random_device()());
  boost::uniform_int<> begin_to_end( begin, end );
  boost::variate_generator< RNGType, boost::uniform_int<> >
                dice(rng, begin_to_end);
  return dice();
}

multimap<int, int> GRASP::degreeAskey(map<int, int> nodes){
  multimap<int, int> response;
  map<int, int>::iterator it;
  for (it = nodes.begin(); it != nodes.end(); ++it){
    response.insert(pair<int, int>(it->second, it->first));
  }
  return response;
}

void GRASP::chooseColor(int node, int avoidColor){
  vector<bool> available((*G).V, true);
  list<int>::iterator i;
  for (i = (*G).adj[node].begin(); i != (*G).adj[node].end(); ++i){
    if ((*G).nodeColor[*i] != -1){
        available[(*G).nodeColor[*i]] = false;
    }
  }
  int newColor = GRASP::selectNodeColorGrasp(available, (*G).sizeColor, avoidColor, (*G).V);
  (*G).paintNode(node, newColor);
}
