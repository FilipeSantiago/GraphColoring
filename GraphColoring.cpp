#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
#include <time.h>
using namespace std;

struct coloring{
	int color;
	int size;
};

// A class that represents an undirected graph
class Graph{
    int V;    // No. of vertices
    list<int> *adj;    // A dynamic array of adjacency lists
public:
    // Constructor and destructor
    Graph(int V)   { this->V = V; adj = new list<int>[V]; }
    ~Graph()       { delete [] adj; }

    // function to add an edge to graph
    void addEdge(int v, int w);

    // Prints greedy coloring of the vertices
    //void graspColoring();
    void greedyColoring();
    void ILS();
private:
	int selectNodeColorGreedy(vector<bool> available, vector<int> colorSize);
	int selectNodeColorGrasp(vector<bool> available, vector<int> colorSize, int ignore);

	vector<int> recoloring(vector<int> vertex, list<int> *adj, vector<int> colorSize);
	vector<int> neighbourhood2(vector<int> originalVertex, list<int> *adj, vector<int> colorSize);
    vector<int> shake(vector<int> originalVertex, list<int> *adj, vector<int> colorSize);

	/*
	vector<int> neighbourhood3(vector<int> originalVertex, list<int> *adj, vector<int> colorSize);
	*/
};

void Graph::addEdge(int v, int w){
    adj[v].push_back(w);
    adj[w].push_back(v);  // Note: the graph is undirected
}

// Assigns colors (starting from 0) to all vertices and prints
// the assignment of colors
void Graph::greedyColoring()
{
    vector<int> result(V);

    // Assign the first color to first vertex
    result[0]  = 0;

    // Initialize remaining V-1 vertices as unassigned
    for (int u = 1; u < V; u++){
        result[u] = -1;  // no color is assigned to u
    }


    vector<int> colorSize(V, 0);
    colorSize[0] = 1;
    /*
    		A temporary array to store the available colors. True
    	value of available[cr] would mean that the color cr is
    	avaiable to coloring this vertice.
    */
    vector<bool> available(V, true);

    // Assign colors to remaining V-1 vertices
    for (int u = 1; u < V; u++){
        // Process all adjacent vertices and flag their colors
        // as unavailable
        list<int>::iterator i;
        for (i = adj[u].begin(); i != adj[u].end(); ++i){
            if (result[*i] != -1){
                available[result[*i]] = false;
            }
        }

        // Find the first available color
        int cr = selectNodeColorGrasp(available, colorSize, -1);
 		colorSize[cr]++;
        result[u] = cr;   // Assign the found color

        // Reset the values back to false for the next iteration
        for (i = adj[u].begin(); i != adj[u].end(); ++i){
            if (result[*i] != -1){
                available[result[*i]] = true;
            }
        }
    }
 	result = neighbourhood2(result, adj, colorSize);
    // print the result
    for (int u = 0; u < V; u++)
        cout << "Vertex " << u << " --->  Color "
             << result[u] << endl;
}

vector<int> attColorSize(vector<int> vertex){
    vector<int> colorSize(vertex.size());
    for (int i = 0; i < vertex.size(); ++i){
        colorSize[vertex[i]]++;
    }
    return colorSize;
}


void Graph::ILS(){
    vector<int> result(V);
    result[0]  = 0;
    for (int u = 1; u < V; u++){
        result[u] = -1;
    }
    vector<int> colorSize(V, 0);
    colorSize[0] = 1;
    vector<bool> available(V, true);
    for (int u = 1; u < V; u++){
        list<int>::iterator i;
        for (i = adj[u].begin(); i != adj[u].end(); ++i){
            if (result[*i] != -1){
                available[result[*i]] = false;
            }
        }
        // Find the first available color
        int cr = selectNodeColorGrasp(available, colorSize, -1);
        colorSize[cr]++;
        result[u] = cr;
        for (i = adj[u].begin(); i != adj[u].end(); ++i){
            if (result[*i] != -1){
                available[result[*i]] = true;
            }
        }
    }
    //Fim da inicialização
    vector<int> best = result;
    vector<int> atualBest = result;
    for (int i = 0; i < 50; ++i){
        atualBest = recoloring(atualBest, adj, colorSize);
        colorSize = attColorSize(atualBest);
        atualBest = neighbourhood2(atualBest, adj, colorSize);
        colorSize = attColorSize(atualBest);
        best = atualBest;
        atualBest = shake(atualBest, adj, colorSize);
    }
    for (int u = 0; u < V; u++)
        cout << "Vertex " << u << " --->  Color "
             << best[u] << endl;
}

int Graph::selectNodeColorGreedy(vector<bool> available, vector<int> colorSize){
	int i;
    //Percorre e vê quais estão sendo usadas
    for(i = 0; i < V; i++){
    	if (available[i]){
            break;
        }
    }
	return i;
}

int Graph::selectNodeColorGrasp(vector<bool> available, vector<int> colorSize, int ignore){
	//sort(colorSize.begin(), colorSize.end(), decrescentOrder);
	int i;
	vector<coloring> possibleColors(3);
	coloring build;
    int sumColorsSize = 0;
    int j = 0, newColor = -1;
    for(i = 0; i < V; i++){
    	if(i != ignore){
	    	if (available[i] && j < 3){
	    		/*
						Se a cor não for nova cria uma roleta para ela, se for nova
					criamos uma roleta para ela com o tamanho de 1 quinto do tamanho
					atual da roleta +1, caso a roleta seja menor que 5.
				*/
	    		build.color = i;
	    		if(colorSize[i] > 0){
	    			build.size = colorSize[i];
	    			if(j > 0) build.size += possibleColors[j-1].size;
	    			possibleColors[j++] = build;
	    			sumColorsSize += colorSize[i];
	    		}else{
	    			if(sumColorsSize > 0) build.size = (sumColorsSize/5);
	    			if(j == 0) build.size++;
	    			sumColorsSize += build.size;
	    			if(j > 0) build.size += possibleColors[j-1].size;
	    			possibleColors[j] = build;
	    			break;
	    		}
	        }else if(j >= 3) break;
	 	}
    }
    srand(time(NULL));
    int pos = rand()%sumColorsSize;
	for (int i = 0; i <= j; ++i)
		if(possibleColors[i].size > pos) return possibleColors[i].color;
}

int countColor(vector<int> colorSize){
	int resp = 0;
	int count = 0;
	for (int i = 0; i < colorSize.size(); ++i){
		if(colorSize[i] > 0) resp++;
		else count++;
		if(count == 3) break;
	}
	return resp;
}

vector<int> Graph::recoloring(vector<int> originalVertex, list<int> *adj, vector<int> colorSize){
	int vertexTam = originalVertex.size();
	int numColors = countColor(colorSize);
	int newNumColors;

	vector<int> vertex = originalVertex;
	vector<int> best = originalVertex;
	vector<int> colorSizeAux = colorSize;


	for (int i = 0; i < colorSize.size(); ++i){
		if(colorSize[i] == 0) continue;
		colorSizeAux[i] = 0;
		for (int j = 0; j < vertexTam; ++j){
			if(vertex[j] == i){
				vertex[j] = -1;
			}
		}
		for (int u = 0; u < vertexTam; ++u){
			if(vertex[u] == -1){
				list<int>::iterator k;
				vector<bool> available(vertexTam, true);
		        for (k = adj[u].begin(); k != adj[u].end(); ++k){
		            if (vertex[*k] != -1){
		                available[vertex[*k]] = false;
		            }
		        }
		        int color = selectNodeColorGrasp(available, colorSizeAux, i);
		        vertex[u] = color;
		        colorSizeAux[color]++;
			}
		}
		newNumColors = countColor(colorSizeAux);
		if(newNumColors < numColors){
    			best = vertex;
			numColors = newNumColors;
		}
		vertex = originalVertex;
		colorSizeAux = colorSize;
	}
	return best;
}

vector<int> Graph::neighbourhood2(vector<int> originalVertex, list<int> *adj, vector<int> colorSize){
	vector<int> vertex = originalVertex;
	vector<int> best = originalVertex;
	vector<int> colorSizeAux = colorSize;

    int vertexTam = originalVertex.size();
	int numColors = countColor(colorSizeAux);
	int numColorsIt;

	for (int i = 0; i < vertexTam; ++i){
		list<int>::iterator k;
		vector<bool> available(vertexTam, true);
        for (k = adj[i].begin(); k != adj[i].end(); ++k){
            if (vertex[*k] != -1){
                available[vertex[*k]] = false;
            }
        }
        for (int j = 0; j < colorSizeAux.size(); ++j){
        	if(colorSizeAux[j] > 0 && available[j]){
        		vertex[i] = j;
        		colorSizeAux[j]--;
        		numColorsIt = countColor(colorSizeAux);
        		if(numColors > numColorsIt){
        			best = vertex;
        			numColors = numColorsIt;
        		}
        	}
        }
        colorSizeAux = colorSize;
	}
	return best;
}

vector<int> Graph::shake(vector<int> vertex, list<int> *adj, vector<int> colorSize){
    int vertexTam = vertex.size();
    srand(time(NULL));
    int posI = rand()%(vertexTam/2);
    srand(time(NULL));
    int posF = rand()%(vertexTam/3) + posI;
    for (int i = posI; i < posF; ++i){
        vertex[i] = -1;
        colorSize[vertex[i]]--;
    }
    for (int u = 0; u < vertexTam; ++u){
        if(vertex[u] == -1){
            list<int>::iterator k;
            vector<bool> available(vertexTam, true);
            for (k = adj[u].begin(); k != adj[u].end(); ++k){
                if (vertex[*k] != -1){
                    available[vertex[*k]] = false;
                }
            }
            int color = selectNodeColorGrasp(available, colorSize, -1);
            vertex[u] = color;
            colorSize[color]++;
        }
    }
    return vertex;
}

int main(){
    Graph g1(5);
    g1.addEdge(0, 1);
    g1.addEdge(0, 2);
    g1.addEdge(1, 2);
    g1.addEdge(1, 3);
    g1.addEdge(2, 3);
    g1.addEdge(3, 4);
    cout << "Coloring of graph 1 \n";
    g1.ILS();

    Graph g2(5);
    g2.addEdge(0, 1);
    g2.addEdge(0, 2);
    g2.addEdge(1, 2);
    g2.addEdge(1, 4);
    g2.addEdge(2, 4);
    g2.addEdge(4, 3);
    cout << "\nColoring of graph 2 \n";
    g2.ILS();

    return 0;
}
