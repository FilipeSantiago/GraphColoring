#ifndef Info_H
#define Info_H

#include <sstream>
#include <climits>
#include <iostream>

using namespace std;

class Info{
  //General Info
  string graphName;
  int NoExecutions;
  //Sums
  double sumTimeOfExecutions;
  int sumResults;
  //BestStuff
  int bestResult;
  double timeOfBestResult;

public:
    // Constructor and destructor
    Info(string graphName){
      this->graphName = graphName;
      this->NoExecutions = 0;
      this->sumResults = 0;
      this->sumTimeOfExecutions = 0;
      this->bestResult = INT_MAX;
    }
    ~Info()  {  }

    void addExecution (int result, long long executionTime);
    string Tostring();
};

#endif
