//
//  main.c
//  BankersAlgorithm
//
//  Created by Kai Zhang on 2017-03-23.
//  Copyright © 2017 Kai Zhang. All rights reserved.
//

#include <stdio.h>
#include <stdbool.h>

int currentAllocTable[5][5]={{2,0,1,1},
    {0,1,2,1},
    {4,0,0,3},
    {0,2,1,0},
    {1,0,3,0}};

int max_claim[5][5]={{3,2,1,4},
    {0,2,5,2},
    {5,1,0,5},
    {1,5,3,0},
    {3,0,3,3}};

int inNeed[5];
int allocationTotal[5] = {0, 0, 0, 0, 0};
int maxResource[5] = {8, 5, 9, 7};
int running[5] = {1,1,1,1,1};
int count = 5;
int i = 0;
int j = 0;
int exec = 0;
int resources = 4;
int processes = 5;
bool safe = false;

void printTotalSystemResource();
void printCurrentlyAllocatedResouce();
void printMaximumResource();
void printAllocatedResources();
void printResourcesinNeed();

int main(int argc, const char * argv[]) {
    printTotalSystemResource();
    printCurrentlyAllocatedResouce();
    printMaximumResource();
    
    for (i = 0; i < processes; i++)
        for (j = 0; j < resources; j++)
            allocationTotal[j] += currentAllocTable[i][j];
    
    printAllocatedResources();
    
    for (i = 0; i < resources; i++)
        inNeed[i] = maxResource[i] - allocationTotal[i];
    
    printResourcesinNeed();
    
    while (count != 0) {
        safe = false;
        for (i = 0; i < processes; i++) {
            if (running[i]) {
                exec = 1;
                for (j = 0; j < resources; j++) {
                    if (max_claim[i][j] - currentAllocTable[i][j] > inNeed[j]) {
                        exec = 0;
                        break;
                    }
                }
                
                if (exec) {
                    printf("\nProcess%d is executing.\n", i + 1);
                    running[i] = 0;
                    count--;
                    safe = true;
                    for (j = 0; j < resources; j++)
                        inNeed[j] += currentAllocTable[i][j];
                    break;
                }
            }
        }
        
        if (!safe) {
            printf("\nThe processes are in unsafe state.");
            break;
        }else{
            printf("\nThe process is in safe state.");
        }
        
        printResourcesinNeed();
    }
    
    return 0;
}


void printTotalSystemResource(){
    printf("\nThe total system resource is: ");
    for (i = 0; i < resources; i++)
        printf("%d ", maxResource[i]);
    
}

void printCurrentlyAllocatedResouce(){
    printf("\nCurrently Allocated Resource:\n");
    for (i = 0; i < processes; i++) {
        for (j = 0; j < resources; j++)
            printf("\t%d", currentAllocTable[i][j]);
        printf("\n");
    }
}

void printMaximumResource(){
    printf("\nMaximum Resource:\n");
    for (i = 0; i < processes; i++) {
        for (j = 0; j < resources; j++)
            printf("\t%d", max_claim[i][j]);
        printf("\n");
    }
}

void printAllocatedResources(){
    printf("\nAllocated resources: ");
    for (i = 0; i < resources; i++)
        printf("%d ", allocationTotal[i]);
    
}

void printResourcesinNeed(){
    printf("\nResources in need: ");
    for (i = 0; i < resources; i++)
        printf("%d ", inNeed[i]);
    printf("\n");
}
