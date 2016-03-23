#include "ILS.h"
#include "../Graph/Graph.h"

void ILS::doILS(Graph *G, bool useRecoloring, bool useForceColor, bool useSwitchColors){
  initialize(G);
  int best = (*G).numColors;

  //Para se rodar 100x sem melhorar
  for(int i = 0; i < 100; i++){
    recoloring(G);
    forceColor(G);
    changeColor(G);
    if((*G).numColors < best){
      best = (*G).numColors;
      i = 0;
    }
  }
}

void ILS::initialize(Graph *G){
  GRASP grasp;
  grasp.doGrasp(G, 2, -1);
}

void ILS::forceColor(Graph *G){
  Graph auxG (*G);
  Graph best (*G);

  for (int color = 0; color < auxG.sizeColor.size(); ++color){
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
      best.CopyGraph(auxG);
    }
  }
  (*G).CopyGraph(best);
}

void ILS::recoloring(Graph *G){
  Graph auxG (*G);
  Graph best (*G);
  GRASP grasp;

  for (int i = 0; i < auxG.sizeColor.size(); ++i){
    if(auxG.sizeColor[i] == 0) continue;
    if(auxG.sizeColor[i] == -1) break;
    for (int j = 0; j < auxG.V; ++j){
      if(auxG.nodeColor[j] == i){
        auxG.unpaintNode(j);
      }
    }
    grasp.doGrasp(&auxG, -1, i);

    if(auxG.numColors < best.numColors){
      best.CopyGraph(auxG);
    }
  }
  (*G).CopyGraph(best);
}

void ILS::changeColor(Graph *G){
  Graph auxG (*G);
  Graph best (*G);

  for (int node = 0; node < auxG.V; node++){
    for (int color = 0; color < auxG.sizeColor.size(); ++color){
      auxG.paintNode(node, color);          //Força cor no nó
      resolveConflicts(&auxG, node, color); //"Conserta" vizinhos, para ficarem consistentes
      if(auxG.numColors < best.numColors){
        best.CopyGraph(auxG);
      }
    }
  }
  (*G).CopyGraph(best);
}

void ILS::resolveConflicts(Graph *G, int node, int color){
  GRASP grasp;

  list<int>::iterator i;
  for (i = (*G).adj[node].begin(); i != (*G).adj[node].end(); ++i){
    if ((*G).nodeColor[*i] == color){
        (*G).unpaintNode(*i);
        grasp.doGrasp(G, -1, color);
        //resolveConflicts(G, *i, color);
    }
  }
}
