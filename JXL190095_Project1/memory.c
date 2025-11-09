#include <stdio.h>

// 2 dimensional array to represent memory blocks
int memory[1024][2];

//read from memory at address addr and returns pointer
int *mem_read(int addr) {
    //error checking in case of invalid address
    if (addr < 0 || addr >= 1024) {
        fprintf(stderr, "Error: Address out of bounds\n");
        return NULL;
    }
    return memory[addr];
}

//write the given data into memory at address addr
void mem_write(int addr, int* data) {
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