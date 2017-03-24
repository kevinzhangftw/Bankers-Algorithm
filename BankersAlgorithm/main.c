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

int maximumResources[5][5]={{3,2,1,4},
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
void calcAllocationTotal();
void calcResourcesinNeed();

int main(int argc, const char * argv[]) {
    printTotalSystemResource();
    printCurrentlyAllocatedResouce();
    printMaximumResource();
    
    calcAllocationTotal();
    printAllocatedResources();
    
    calcResourcesinNeed();
    printResourcesinNeed();
    
    while (count != 0) {
        safe = false;
        for (i = 0; i < processes; i++) {
            if (running[i]) {
                exec = 1;
                for (j = 0; j < resources; j++) {
                    if (maximumResources[i][j] - currentAllocTable[i][j] > inNeed[j]) {
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
            printf("\t%d", maximumResources[i][j]);
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

void calcAllocationTotal(){
    for (i = 0; i < processes; i++)
        for (j = 0; j < resources; j++)
            allocationTotal[j] += currentAllocTable[i][j];
}

void calcResourcesinNeed(){
    for (i = 0; i < resources; i++)
        inNeed[i] = maxResource[i] - allocationTotal[i];
}
