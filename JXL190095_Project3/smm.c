#include <stdio.h>
#include <stdlib.h>
#include "smm.h"

// Allocation table: PID, base, size
// a size of 0 indicates free hole
int all_table[256][3];

// Link list struct
typedef struct holes {
    int base;
    int size;
    struct holes* next;
} hole_t;

// create allocation entry in table, 0 for no hole found, 1 if found
int allocate(int pid, int size) {

}

// deallocate memory for given PID
// same base address and size, set size to 0 in allocation table
void deallocate(int pid) {

}

