// smithCounter.h
#ifndef smithCounter_H
#define smithCounter_H

class SmithCounter
{
  
public: 
  int counterVal;

  SmithCounter();
  int trainCounter(bool actualOutcome);
  int setValue(int val);
};

#endif