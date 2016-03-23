#ifndef Log_H
#define Log_H

#include "../Graph/Graph.h"

using namespace std;

class Log{

  int executions;
  int sumTimeOfExecutions;

  int bestResult;
  int AverageResult;
public:
    // Constructor and destructor
    Log()   {  }
    ~Log()  {  }

    void getNewDate(int timeOfExecution, int result);
    void logToFile (string graphName);
};

#endif
