// smithCounter.cc
#include "includes.h"
#include "smithCounter.h"

SmithCounter::SmithCounter()
{
    counterVal = 2;
}

int SmithCounter::trainCounter(bool actualOutcome)
{
  if(actualOutcome == 0){
    //Not taken
        if(counterVal!=0){
            counterVal = counterVal - 1;
        }
        else counterVal = 0;
    }
  
  else{
    //Taken
        if(counterVal!=3){
        counterVal = counterVal + 1;
    }
    else counterVal = 3;
    }
}

int SmithCounter::setValue(int val)
{
  counterVal = val;
}