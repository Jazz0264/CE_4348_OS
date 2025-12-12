#include <stdio.h>
#include "smm.h"


// 2 dimensional array to represent memory blocks
int memory[1024][2];

// func prototypes from scheduler.c
int current_pid();
void remove_process(int pid);

/* modified to check to check with SMM if reading is allowed*/

//read from memory at address addr and returns pointer
int *mem_read(int addr) {
    int pid = current_pid();
    // check if address is allowed for current process
    if (!is_allowed_address(pid, addr)) {
        fprintf("Memory violation: Process %d not allowed to access address %d\n", pid, addr);
        deallocate(pid);
        remove_process(pid);
        return NULL;
    }
    //error checking in case of invalid address
    if (addr < 0 || addr >= 1024) {
        fprintf(stderr, "Error: Address out of bounds\n");
        return NULL;
    }
    return memory[addr];
}


/* now modified to check with SMM if address is allowed*/

//write the given data into memory at address addr
void mem_write(int addr, int* data) {
    // modified for project 3
    int pid = current_pid();
    // check if address is allowed for current process
    if (!is_allowed_address(pid, addr)) {
        fprintf("Memory violation: Process %d not allowed to access address %d\n", pid, addr);
        deallocate(pid);
        remove_process(pid);
        return;
    }


    //error checking in case of invalid address
    if (addr < 0 || addr >= 1024) {
        fprintf(stderr, "Error: Address out of bounds\n");
        return;
    }
    if (data == NULL) {
        fprintf(stderr, "Error: Data pointer is NULL\n");
        return;
    }
    //the opcode 
    memory[addr][0] = data[0];
    //the operand
    memory[addr][1] = data[1];
}