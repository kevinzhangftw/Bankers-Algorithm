//
//  main.c
//  BankersAlgorithm
//
//  Created by Kai Zhang on 2017-03-23.
//  Copyright © 2017 Kai Zhang. All rights reserved.
//

#include <stdio.h>
#include <stdbool.h>

int curr[5][5]={{2,0,1,1},
    {0,1,2,1},
    {4,0,0,3},
    {0,2,1,0},
    {1,0,3,0}};

int max_claim[5][5]={{3,2,1,4},
    {0,2,5,2},
    {5,1,0,5},
    {1,5,3,0},
    {3,0,3,3}};

int avl[5];
int alloc[5] = {0, 0, 0, 0, 0};
int max_res[5] = {8, 5, 9, 7};
int running[5] = {1,1,1,1,1};
int count = 5;
int i = 0;
int j = 0;
int exec = 0;
int r = 4;
int p = 5;
bool safe = false;


int main(int argc, const char * argv[]) {
    
    printf("\nThe Claim Vector is: ");
    for (i = 0; i < r; i++)
        printf("%d ", max_res[i]);
    
    printf("\nThe Allocated Resource Table:\n");
    for (i = 0; i < p; i++) {
        for (j = 0; j < r; j++)
            printf("\t%d", curr[i][j]);
        printf("\n");
    }
    
    printf("\nThe Maximum Claim Table:\n");
    for (i = 0; i < p; i++) {
        for (j = 0; j < r; j++)
            printf("\t%d", max_claim[i][j]);
        printf("\n");
    }
    
    for (i = 0; i < p; i++)
        for (j = 0; j < r; j++)
            alloc[j] += curr[i][j];
    
    printf("\nAllocated resources: ");
    for (i = 0; i < r; i++)
        printf("%d ", alloc[i]);
    for (i = 0; i < r; i++)
        avl[i] = max_res[i] - alloc[i];
    
    printf("\nAvailable resources: ");
    for (i = 0; i < r; i++)
        printf("%d ", avl[i]);
    printf("\n");
    
    while (count != 0) {
        safe = false;
        for (i = 0; i < p; i++) {
            if (running[i]) {
                exec = 1;
                for (j = 0; j < r; j++) {
                    if (max_claim[i][j] - curr[i][j] > avl[j]) {
                        exec = 0;
                        break;
                    }
                }
                
                if (exec) {
                    printf("\nProcess%d is executing.\n", i + 1);
                    running[i] = 0;
                    count--;
                    safe = true;
                    for (j = 0; j < r; j++)
                        avl[j] += curr[i][j];
                    break;
                }
            }
        }
        
        if (!safe) {
            printf("\nThe processes are in unsafe state.");
            break;
        }
        
        if (safe)
            printf("\nThe process is in safe state.");
        
        printf("\nAvailable vector: ");
        for (i = 0; i < r; i++)
            printf("%d ", avl[i]);
    }
    
    return 0;
}
