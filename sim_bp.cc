#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sim_bp.h"
#include "bimodal.h"
#include "gshare.h"
#include "hybrid.h"

/*  argc holds the number of command line arguments
    argv[] holds the commands themselves

    Example:-
    sim bimodal 6 gcc_trace.txt
    argc = 4
    argv[0] = "sim"
    argv[1] = "bimodal"
    argv[2] = "6"
    ... and so on
*/
int main (int argc, char* argv[])
{
    FILE *FP;               // File handler
    char *trace_file;       // Variable that holds trace file name;
    bp_params params;       // look at sim_bp.h header file for the the definition of struct bp_params
    char outcome;           // Variable holds branch outcome
    unsigned long int addr; // Variable holds the address read from input file
    Bimodal* bimodalPredictor;
    Gshare* gsharePredictor;
    Hybrid* hybridPredictor;
    

    int choice;
    
    if (!(argc == 4 || argc == 5 || argc == 7))
    {
        printf("Error: Wrong number of inputs:%d\n", argc-1);
        exit(EXIT_FAILURE);
    }
    
    params.bp_name  = argv[1];
    
    // strtoul() converts char* to unsigned long. It is included in <stdlib.h>
    if(strcmp(params.bp_name, "bimodal") == 0)              // Bimodal
    {
        if(argc != 4)
        {
            printf("Error: %s wrong number of inputs:%d\n", params.bp_name, argc-1);
            exit(EXIT_FAILURE);
        }
        params.M2       = strtoul(argv[2], NULL, 10);
        trace_file      = argv[3];
        printf("COMMAND\n%s %s %lu %s\n", argv[0], params.bp_name, params.M2, trace_file);
        choice = bimodal;
    }
    else if(strcmp(params.bp_name, "gshare") == 0)          // Gshare
    {
        if(argc != 5)
        {
            printf("Error: %s wrong number of inputs:%d\n", params.bp_name, argc-1);
            exit(EXIT_FAILURE);
        }
        params.M1       = strtoul(argv[2], NULL, 10);
        params.N        = strtoul(argv[3], NULL, 10);
        trace_file      = argv[4];
        printf("COMMAND\n%s %s %lu %lu %s\n", argv[0], params.bp_name, params.M1, params.N, trace_file);
        choice = gshare;

    }
    else if(strcmp(params.bp_name, "hybrid") == 0)          // Hybrid
    {
        if(argc != 7)
        {
            printf("Error: %s wrong number of inputs:%d\n", params.bp_name, argc-1);
            exit(EXIT_FAILURE);
        }
        params.K        = strtoul(argv[2], NULL, 10);
        params.M1       = strtoul(argv[3], NULL, 10);
        params.N        = strtoul(argv[4], NULL, 10);
        params.M2       = strtoul(argv[5], NULL, 10);
        trace_file      = argv[6];
        printf("COMMAND\n%s %s %lu %lu %lu %lu %s\n", argv[0], params.bp_name, params.K, params.M1, params.N, params.M2, trace_file);
        choice = hybrid;

    }
    else
    {
        printf("Error: Wrong branch predictor name:%s\n", params.bp_name);
        exit(EXIT_FAILURE);
    }

    char str[2];

    switch(choice){
        case bimodal:
            bimodalPredictor = new Bimodal(params.M2);

            // Open trace_file in read mode
            FP = fopen(trace_file, "r");
            if(FP == NULL)
            {
            // Throw error and exit if fopen() failed
                printf("Error: Unable to open file %s\n", trace_file);
                exit(EXIT_FAILURE);
            }
            
            while(fscanf(FP, "%lx %s", &addr, str) != EOF)
            {
                
                outcome = str[0];
                if (outcome == 't'){
                    // printf("%lx %s\n", addr, "t");           // Print and test if file is read correctly
                    bimodalPredictor->parse(addr);
                    bimodalPredictor->predict(1);
                    bimodalPredictor->updatePredictor(1);
                    }

                else if(outcome == 'n'){
                    // printf("%lx %s\n", addr, "n");          // Print and test if file is read correctly
                    bimodalPredictor->parse(addr);
                    bimodalPredictor->predict(0);
                    bimodalPredictor->updatePredictor(0);
                    }
            }
            cout << "OUTPUT" << endl;
            cout << "number of predictions: " << bimodalPredictor->noOfPredictions << endl;
            cout << "number of mispredictions: " << bimodalPredictor->noOfMispredictions << endl;
            cout  << fixed << "misprediction rate: "<< setprecision(2) << ((double)bimodalPredictor->noOfMispredictions/bimodalPredictor->noOfPredictions)*100 << "%" << endl;
            bimodalPredictor->printContents();
            return 0;
            break;

        case gshare:
            gsharePredictor = new Gshare(params.M1, params.N);

            // Open trace_file in read mode
            FP = fopen(trace_file, "r");
            if(FP == NULL)
            {
            // Throw error and exit if fopen() failed
                printf("Error: Unable to open file %s\n", trace_file);
                exit(EXIT_FAILURE);
            }

            while(fscanf(FP, "%lx %s", &addr, str) != EOF)
            {
                
                outcome = str[0];
                if (outcome == 't'){
                    // printf("%lx %s\n", addr, "t");           // Print and test if file is read correctly
                    gsharePredictor->parse(addr);
                    gsharePredictor->predict(1);
                    gsharePredictor->updatePredictor(1);
                    }

                else if(outcome == 'n'){
                    // printf("%lx %s\n", addr, "n");          // Print and test if file is read correctly
                    gsharePredictor->parse(addr);
                    gsharePredictor->predict(0);
                    gsharePredictor->updatePredictor(0);
                    }
            }
            cout << "OUTPUT" << endl;
            cout << "number of predictions: " << gsharePredictor->noOfPredictions << endl;
            cout << "number of mispredictions: " << gsharePredictor->noOfMispredictions << endl;
            cout  << fixed << "misprediction rate: "<< setprecision(2) << ((double)gsharePredictor->noOfMispredictions/gsharePredictor->noOfPredictions)*100 << "%"  << endl;
            gsharePredictor->printContents();
            return 0;
            break;

        case hybrid:
            hybridPredictor = new Hybrid(params.K, params.M1, params.N, params.M2);

            // Open trace_file in read mode
            FP = fopen(trace_file, "r");
            if(FP == NULL)
            {
            // Throw error and exit if fopen() failed
                printf("Error: Unable to open file %s\n", trace_file);
                exit(EXIT_FAILURE);
            }
            
            while(fscanf(FP, "%lx %s", &addr, str) != EOF)
            {
                
                outcome = str[0];
                if (outcome == 't'){
                    // printf("%lx %s\n", addr, "t");           // Print and test if file is read correctly
                    hybridPredictor->parse(addr);
                    hybridPredictor->predict(addr, 1);
                    hybridPredictor->updatePredictor(1);
                    }

                else if(outcome == 'n'){
                    // printf("%lx %s\n", addr, "n");          // Print and test if file is read correctly
                    hybridPredictor->parse(addr);
                    hybridPredictor->predict(addr,0);
                    hybridPredictor->updatePredictor(0);
                    }
            }
            cout << "OUTPUT" << endl;
            cout << "number of predictions: " << hybridPredictor->noOfPredictions << endl;
            cout << "number of mispredictions: " << hybridPredictor->noOfMispredictions << endl;
            cout  << fixed <<  "misprediction rate: " << setprecision(2) << ((double)hybridPredictor->noOfMispredictions/hybridPredictor->noOfPredictions)*100 << "%" << endl;
            hybridPredictor->printContents();
            
            return 0;
            break;

    }
    

}
