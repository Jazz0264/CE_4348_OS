#include <stdio.h>

// function prototypes from memory.c
int *mem_read(int addr);
void mem_write(int addr, int *data);

// function prototypes from disk.c
int load_prog(char *fname, int addr);
void load_programs(char fname[]);

// function prototypes from cpu.c
int clock_cycle(void);

// function prototypes from scheduler.c
int schedule(int cycle_num, int process_status);

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
    printf("loading programs into memory :) \n");
    load_programs("program_list.txt");

    // initialize clock cycles, and status
    printf("Starting clock cycles :D \n");
    int cycle_num = 0;
    // process status
    int process_status = 1;
    // schedule status
    int schedule_status = 1;

    while (schedule_status == 1){
        // run a clock cycle
        process_status = clock_cycle();
        // increment cycle count
        cycle_num = cycle_num + 1;
        // iimmediately call scheduler
        schedule_status = schedule(cycle_num, process_status);
    }

    // once finish print first 20 memory locations
    printf("All done!\n");
    mem_print();
    return 0;
}