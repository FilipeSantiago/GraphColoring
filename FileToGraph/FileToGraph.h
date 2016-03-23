#ifndef FileToGraph_H
#define FileToGraph_H

#include "../Graph/Graph.h"
#include <set>
#include <vector>
#include <fstream>
#include <cstring>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <chrono>


using namespace std;

class FileToGraph{

public:
    // Constructor and destructor
    FileToGraph()   {  }
    ~FileToGraph()       { }

    void convertFileToGraph(string fileName, Graph* modify);
};

#endif
