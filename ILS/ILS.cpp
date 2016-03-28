#include "ILS.h"
#include "../Graph/Graph.h"

void ILS::doILS(Graph *G, bool useRecoloring, bool useForceColor, bool useSwitchColors){
  initialize(G);
  int best = (*G).numColors;
  Graph bestG(*G);
  //Para se rodar 10x sem melhorar
  for(int i = 0; i < 20; i++){
    //cout << i << endl;
    recoloring(G);
    forceColor(G);
    changeColor(G);
    if((*G).numColors < best){
      best = (*G).numColors;
      bestG.CopyGraph(*G);
      cout << "MELHOROU " << i << " -> novo best = " << best << endl;
      i = 0;
    }
    if(G->numColors < (best+2)){
      shake1(G);
    }else{
      G->CopyGraph(bestG);
      shake1(G);
    }
  }
  G->CopyGraph(bestG);

}

void ILS::shake1(Graph* G){
  GRASP grasp(G);
  int start = grasp.pickARandomNumberBetween(0, G->V/2);
  int end   = grasp.pickARandomNumberBetween(G->V/4, G->V/3) + start;

  for(int i = start; i < end; i++){
    G->unpaintNode(i);
  }
  grasp.doGrasp(1, -1);
}

void ILS::initialize(Graph *G){
  GRASP grasp(G);
  grasp.doGrasp(1, -1);
  cout << "entrou com " << G->numColors << endl;
}

void ILS::forceColor(Graph *G){
  Graph auxG (*G);
  Graph best (*G);

  for (int color = 0; color < auxG.sizeColor.size(); ++color){
    auxG.CopyInfoGraph(*G);
    if(auxG.sizeColor[color] == -1) break;
    for (int node = 0; node < auxG.V; node++){
      vector<bool> available(auxG.V, true);
      list<int>::iterator i;
      for (i = auxG.adj[node].begin(); i != auxG.adj[node].end(); ++i){
        if (auxG.nodeColor[*i] != -1){
            available[auxG.nodeColor[*i]] = false;
        }
      }
      if(available[color]){
        auxG.paintNode(node, color);
      }
    }
    if(auxG.numColors < best.numColors){
      forceColor(&auxG);
      best.CopyGraph(auxG);
    }
  }
  (*G).CopyGraph(best);
}

void ILS::recoloring(Graph *G){
  Graph auxG (*G);
  Graph best (*G);
  GRASP grasp(&auxG);

  for (int i = 0; i < auxG.sizeColor.size(); ++i){
    auxG.CopyInfoGraph(*G);
    if(auxG.sizeColor[i] == 0) continue;
    if(auxG.sizeColor[i] == -1) break;
    for (int j = 0; j < auxG.V; ++j){
      if(auxG.nodeColor[j] == i){
        auxG.unpaintNode(j);
      }
    }
    grasp.doGrasp(1, i);

    if(auxG.numColors < best.numColors){
      recoloring(&auxG);
      best.CopyGraph(auxG);
    }
  }
  (*G).CopyGraph(best);
}

void ILS::changeColor(Graph *G){
  Graph auxG (*G);
  Graph best (*G);
  GRASP grasp(G);
  vector<int> colors;
  int realColor;
  for(int i = 0; i < auxG.V; i++){
    if(auxG.sizeColor[i] > 0 && find(colors.begin(), colors.end(), i) == colors.end()) colors.push_back(auxG.nodeColor[i]);
  }
  for (int color = 0; color < auxG.V; color++){
    if(auxG.sizeColor[color] <= 0) continue;
    for (int node = 0; node < auxG.V; ++node){
      if(auxG.nodeColor[node] == color){
        int potentialColor = getPossibleColor(&auxG, node, color);

        if(potentialColor >= 0) realColor = potentialColor;
        else realColor = auxG.GetColorOfNgbWithLessConflicts(node);

        auxG.paintNode(node, realColor);

        if(potentialColor < 0) resolveConflicts(&auxG, node, realColor, 0);

      }
      if(auxG.numColors < best.numColors){
        best.CopyGraph(auxG);
      }
    }
  }
  (*G).CopyGraph(best);
}

void ILS::resolveConflicts(Graph *G, int node, int color, int deep){
  GRASP grasp(G);
  list<int>::iterator i;
  int stop = G->V * 0.05;
  int realColor;
  if(deep < stop){
    for (i = (*G).adj[node].begin(); i != (*G).adj[node].end(); ++i){
      if ((*G).nodeColor[*i] == color){
        int potentialColor = getPossibleColor(G, *i, color);

        if(potentialColor >= 0) realColor = potentialColor;
        else realColor = G->GetColorOfNgbWithLessConflicts(*i);

        G->paintNode(*i, realColor);

        if(potentialColor < 0) resolveConflicts(G, node, realColor, ++deep);
      }
    }
  }
  for (i = (*G).adj[node].begin(); i != (*G).adj[node].end(); ++i){
    if ((*G).nodeColor[*i] == color){
        (*G).unpaintNode(*i);
    }
  }
  grasp.doGrasp(1, -1);
}

int ILS::getPossibleColor(Graph* G, int node, int avoidColor){
  GRASP grasp(G);
  vector<bool> available((*G).V, true);
  list<int>::iterator i;
  for (i = (*G).adj[node].begin(); i != (*G).adj[node].end(); ++i){
    if ((*G).nodeColor[*i] != -1){
        available[(*G).nodeColor[*i]] = false;
    }
  }
  int newColor = grasp.selectNodeColorGrasp(available, (*G).sizeColor, avoidColor, (*G).V);
  if(G->sizeColor[newColor] > 0) return newColor;
  return -1;
}
