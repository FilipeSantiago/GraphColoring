#ifndef Log_H
#define Log_H

#include "../Graph/Graph.h"
#include "Info.h"
#include <fstream>
#include <iomanip>
#include <sstream>

using namespace std;

class Log{

public:
  vector<Info> logInfo;
    // Constructor and destructor
    Log()   {  }
    ~Log()  {  }

    void logToFile (string fileName);
};

#endif
