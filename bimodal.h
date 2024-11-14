// bimodal.h
#include "includes.h"
#include "smithCounter.h"

#ifndef bimodal_H
#define bimodal_H

class Bimodal
{
  vector<SmithCounter> branchPredictorArray;
  int noOfIndexBits;
  int index;
  bool prediction; //0 - not taken, 1 - taken

public:
  int noOfPredictions;
  int noOfMispredictions;  
  
  Bimodal(int m2);
  void parse(uint32_t pc);
  bool predict(bool actualOutcome);
  void updatePredictor(bool actualOutcome);
  void printContents();
};

#endif