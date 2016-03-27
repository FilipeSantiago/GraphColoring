#include "Info.h"

void Info::addExecution (int result, long long executionTime){
  this->NoExecutions++;
  if(result < this->bestResult) {
    this->bestResult = result;
    this->timeOfBestResult = executionTime;
  }
  this->sumResults += result;
  //cout << this->sumTimeOfExecutions << " " << executionTime << endl;
  this->sumTimeOfExecutions += executionTime;
  //cout << this->sumTimeOfExecutions << endl;
}

string Info::Tostring(){
  stringstream container;
  container << this->graphName << " "
            << this->NoExecutions << " "
            << this-> bestResult << " "
            << this->timeOfBestResult << " "
            << (this->sumResults/(float)this->NoExecutions) << " "
            << (this->sumTimeOfExecutions/(float)this->NoExecutions) << endl;
  return container.str();
}
