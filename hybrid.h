// hybrid.h
#include "includes.h"
#include "smithCounter.h"
#include "bimodal.h"
#include "gshare.h"

#ifndef hybrid_H
#define hybrid_H

class Hybrid
{
  vector<SmithCounter> chooserTable;
  Bimodal* myBimodalPredictor;
  Gshare* myGsharePredictor;
  int k;
  int m1;
  int n;
  int m2;
  int index;
  bool bimodalPrediction;
  bool gsharePrediction;
  bool prediction; //0 - not taken, 1 - taken

public:
  int noOfPredictions;
  int noOfMispredictions;
    
  Hybrid(int k_in, int m1_in, int n_in, int m2_in);
  void parse(uint32_t pc);
  bool predict(uint32_t pc, bool actualOutcome);
  void updatePredictor(bool actualOutcome);
  void printContents();
};

#endif