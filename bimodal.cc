//bimodal.cc
#include "includes.h"
#include "bimodal.h"

Bimodal::Bimodal(int m2)
{
    branchPredictorArray.resize(pow(2, m2));
    // cout << "arr resized: " << branchPredictorArray.size() << endl;
    noOfIndexBits = m2;
    index = 0;
    noOfPredictions = 0;
    noOfMispredictions = 0;
    
}

void Bimodal::parse(uint32_t pc)
{
    // cout << "pc: " << hex << pc << dec << endl;
    pc = pc >> 2;

    pc = pc << (32-noOfIndexBits);
    index = pc >> (32-noOfIndexBits);

    // cout << "index: " << index << endl;
    // cout << "BP: " << index << "   " << branchPredictorArray[index].counterVal << endl;    
}

bool Bimodal::predict(bool actualOutcome)
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

}

void Bimodal::updatePredictor(bool actualOutcome)
{
    if(actualOutcome == 0) branchPredictorArray[index].trainCounter(0);
    else branchPredictorArray[index].trainCounter(1);
    // cout << "BU: " << index << "   " << branchPredictorArray[index].counterVal << endl;

}

void Bimodal::printContents()
{
    cout << "FINAL BIMODAL CONTENTS" << endl;
    for(int i = 0; i<branchPredictorArray.size(); i++){
        cout << i << "\t" << branchPredictorArray[i].counterVal << endl;
    }
}


