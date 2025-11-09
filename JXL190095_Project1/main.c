#include <stdio.h>

// function prototypes from other files
void mem_write(int addr, int *data);
void load_prog(char *fname, int addr);
int clock_cycle(void);

// memory array from memory.c
extern int memory[1024][2];

// function to clear memory
void clear_mem()
{
    for (int i = 0; i < 1024; i++)
    {
        memory[i][0] = 0;
        memory[i][1] = 0;
    }
}

// function to print frist 20 memory locations
void mem_print()
{
    printf("First 20 addresses' contents:\n");
    for (int j = 0; j < 20; j++)
    {
        printf("Addr %d: [%d, %d]\n", j, memory[j][0], memory[j][1]);
    }
}

int main()
{
    // begin by clearing memory
    clear_mem();
    // load program txt into memory starting at address 4
    printf("loading program into memory :) \n");
    load_prog("fname2.txt", 4);

    // start clock cycles
    printf("Starting program :D \n");
    while (clock_cycle())
    {
        // will exit at ex = 0
    }
    // once finish print first 20 memory locations
    printf("All done!\n");
    mem_print();
    return 0;
}