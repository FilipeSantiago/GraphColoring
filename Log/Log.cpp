#include "Log.h"

void Log::logToFile (string fileName){
  stringstream container;
  for(int i = 0; i < logInfo.size(); i++){
    container << logInfo[i].Tostring();
    ofstream logfile;
  	try{
      cout << "??";
  		logfile.open("Execution/" + fileName);
  		logfile << container.str();
  		logfile.close();
  	}catch(exception& e){
      cout << "ERRROW";
  		return;
  	}
  }
}
