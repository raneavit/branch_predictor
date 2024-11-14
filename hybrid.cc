//hybrid.cc
#include "includes.h"
#include "hybrid.h"

Hybrid::Hybrid(int k_in, int m1_in, int n_in, int m2_in)
{
    chooserTable.resize(pow(2, k_in));
    // cout << "Chooser table size: "<< chooserTable.size() << endl;
    for(int i = 0; i< chooserTable.size(); i++) chooserTable[i].setValue(1);
    
    myBimodalPredictor = new Bimodal(m2_in);
    myGsharePredictor = new Gshare(m1_in, n_in);
    k = k_in;

    index = 0;
    noOfPredictions = 0;
    noOfMispredictions = 0;
    
}

void Hybrid::parse(uint32_t pc)
{
    pc = pc >> 2;
    pc = pc << (32-k);
    index = pc >> (32-k);

    // cout << "CP: " << index << "   " << chooserTable[index].counterVal << endl;   
}

bool Hybrid::predict(uint32_t pc, bool actualOutcome)
{
    noOfPredictions++;
    myBimodalPredictor->parse(pc);
    bimodalPrediction = myBimodalPredictor->predict(actualOutcome);

    myGsharePredictor->parse(pc);
    gsharePrediction = myGsharePredictor->predict(actualOutcome);


    if(chooserTable[index].counterVal >= 2){
        //choose gshare
        prediction = gsharePrediction;
        if(prediction != actualOutcome) noOfMispredictions ++;
        myGsharePredictor->updatePredictor(actualOutcome);

    }
    else{
        prediction = bimodalPrediction;
        if(prediction != actualOutcome) noOfMispredictions ++;
        myBimodalPredictor->updatePredictor(actualOutcome);
        myGsharePredictor->updateBranchHistoryReg(actualOutcome);
    }

    return prediction; 

    
}

void Hybrid::updatePredictor(bool actualOutcome)
{
    if((bimodalPrediction != actualOutcome && gsharePrediction!=actualOutcome)){
        //nothing
    }
    else if(gsharePrediction == actualOutcome && bimodalPrediction != actualOutcome){
        chooserTable[index].trainCounter(1);
        // cout << "CU: " << index << "\t" << chooserTable[index].counterVal << endl;
    }
    else if(gsharePrediction != actualOutcome && bimodalPrediction == actualOutcome){
        chooserTable[index].trainCounter(0);
        // cout << "CU: " << index << "\t" << chooserTable[index].counterVal << endl;
    }
    else;

    

}

void Hybrid::printContents()
{
    cout << "FINAL CHOOSER CONTENTS" << endl;
    for(int i = 0; i<chooserTable.size(); i++){
        cout << i << "\t" << chooserTable[i].counterVal << endl;
    }

    myGsharePredictor->printContents();
    myBimodalPredictor->printContents();
}