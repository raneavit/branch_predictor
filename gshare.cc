//gshare.cc
#include "includes.h"
#include "gshare.h"

Gshare::Gshare(int m1_in, int n_in)
{
    branchPredictorArray.resize(pow(2, m1_in));
    // cout << "arr resized: " << branchPredictorArray.size() << endl;
    m1 = m1_in;
    n = n_in;
    index = 0;
    branchHistoryReg = 0;
    noOfPredictions = 0;
    noOfMispredictions = 0;
    
}

void Gshare::parse(uint32_t pc)
{
    // cout << "pc: " << hex << pc << dec << endl;
    int temp1 = 0, temp2 = 0;
    pc = pc >> 2;

    pc = pc << (32-m1);
    temp1 = pc >> (32-m1);

    if(n > 0){
        temp2 = branchHistoryReg << (m1-n);
        index = temp1 ^ temp2;
    }
    else index = temp1;
    
    // cout << "parsed index: " << index << endl;
    // cout << "GP: " << index << "   "<< branchPredictorArray[index].counterVal << endl; 
}

bool Gshare::predict(bool actualOutcome)
{
    noOfPredictions++;

    if(branchPredictorArray[index].counterVal >= 2){
        //predict branch taken
        prediction = 1;
        if(prediction != actualOutcome) noOfMispredictions ++;
        return 1;
    }
    else{
        prediction = 0;
        if(prediction != actualOutcome) noOfMispredictions ++;
        return 0;
    }

    // cout << "predicted" << endl; 

    
}

void Gshare::updatePredictor(bool actualOutcome)
{
    if(actualOutcome == 0){
        branchPredictorArray[index].trainCounter(0);
        updateBranchHistoryReg(0);   
        }

    else{
        branchPredictorArray[index].trainCounter(1);
        updateBranchHistoryReg(1);
        }
    
    // cout << "GU: " << index << "   " << branchPredictorArray[index].counterVal << endl;
    
    // cout << "updated predictor" << endl;

}

void Gshare::updateBranchHistoryReg(bool actualOutcome)
{
    if(actualOutcome == 0){
        branchHistoryReg = branchHistoryReg >> 1;   
        }

    else{
        branchHistoryReg = branchHistoryReg >> 1;
        branchHistoryReg = branchHistoryReg | (1 << (n-1));
        }
    
    // cout << "updated bhr" << branchHistoryReg << endl;

}

void Gshare::printContents()
{
    cout << "FINAL GSHARE CONTENTS" << endl;
    for(int i = 0; i<branchPredictorArray.size(); i++){
        cout << i << "\t" << branchPredictorArray[i].counterVal << endl;
    }
}