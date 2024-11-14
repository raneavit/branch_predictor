// gshare.h
#include "includes.h"
#include "smithCounter.h"

#ifndef gshare_H
#define gshare_H

class Gshare
{
  uint32_t branchHistoryReg;
  vector<SmithCounter> branchPredictorArray;
  int m1;
  int n;
  int index;
  bool prediction; //0 - not taken, 1 - taken

public:  
  int noOfPredictions;
  int noOfMispredictions;

  Gshare(int m1, int n);
  void parse(uint32_t pc);
  bool predict(bool actualOutcome);
  void updatePredictor(bool actualOutcome);
  void updateBranchHistoryReg(bool actualOutcome);
  void printContents();
};

#endif