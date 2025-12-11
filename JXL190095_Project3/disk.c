// this program loads and translates programs into memory for operation
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// function prototypes from memory.c
int *mem_read(int addr);
void mem_write(int addr, int *data);

// function prototypes from scheduler.c
void new_process(int base, int size);
int current_pid(void);

// struct of opcodes for jump table
typedef struct
{
    // instruction string
    const char *str;
    // int equivalent
    int opcode;
    // arguments if = 1
    int arg;
} instruction_t;

// look up table for instructions
instruction_t instructions[] = {
    {"exit", 0, 0},
    {"load_const", 1, 1},
    {"move_from_mbr", 2, 0},
    {"move_from_mar", 3, 0},
    {"move_to_mbr", 4, 0},
    {"move_to_mar", 5, 0},
    {"load_at_addr", 6, 0},
    {"write_at_addr", 7, 0},
    {"add", 8, 0},
    {"multiply", 9, 0},
    {"and", 10, 0},
    {"or", 11, 0},
    {"ifgo", 12, 1},
    {"sleep", 13, 0},
    {NULL, -1, 0} // end
};

// translate the given instruciton into its opcode
int *translate(char *instruction)
{
    static int opcode[2] = {0, 0};

    // return null if empty line
    if (!instruction)
        return NULL;
    // ignore comments or blacnk lines
    if (*instruction == '\0' || (instruction[0] == '/' && instruction[1] == '/'))
    {
        return NULL;
    }
    // parse into instruction
    char instr[64];
    int arg = 0;
    // formatted scan
    int num_parsed = sscanf(instruction, "%63s %d", instr, &arg);

    // look for opcode in table
    for (int i = 0; instructions[i].str != NULL; i++)
    {
        // if our string matches an entry then set opcode and arg
        if (strcmp(instr, instructions[i].str) == 0)
        {
            opcode[0] = instructions[i].opcode;
            opcode[1] = (instructions[i].arg == 1 && num_parsed == 2) ? arg : 0;
            return opcode;
        }
    }
    // if we reach here the instruction was not found
    return NULL;
}

// updated load program function
int load_prog(char *fname, int addr)
{
    // open the file
    FILE *f = fopen(fname, "r");
    // error check for file open
    if (!f)
    {
        fprintf(stderr, "Error opening file %s\n", fname);
        perror(fname);
        exit(EXIT_FAILURE);
        return 0;
    }
    // buffer for reading lines
    char line[256];
    // current address to load into
    int cur_addr = addr;

    // read each line from file
    while (fgets(line, sizeof(line), f))
    {
        // translate line into opcode
        int *opcode = translate(line);
        if (!opcode)
            continue; // skip invalid lines
        // write into memory after translation
        mem_write(cur_addr, opcode);
        // increment address
        cur_addr = cur_addr + 1;

        // stop after 1024 addresses
        if (cur_addr >= 1024)
        {
            fprintf(stderr, "Memory limit reached while loading program\n");
            break;
        }
    }
    // close the file
    fclose(f);

    // return number of instructions loaded
    return cur_addr - addr;
}

// loads a list of programs from a file
void load_programs(char fname[]){
    // open the file
    FILE *f = fopen(fname, "r");
    // error check for file open
    if (!f)
    {
        fprintf(stderr, "Error opening list file %s\n", fname);
        perror(fname);
        exit(EXIT_FAILURE);
    }
    // buffer for reading lines, program name and base address
    char line[256];
    char prog_name[128];
    int base_addr;

    // read each line from file
    while (fgets(line, sizeof(line), f)){
        // parse program name and base address
        if (sscanf(line, "%d %127s", &base_addr, prog_name ) != 2){
            fprintf(stderr, "Invalid line in program list: %s\n", line);
            continue;
        }
        // load the program into memory
        int size = load_prog(prog_name, base_addr);
        // create a new process for the loaded program
        new_process(base_addr, size);
    }
    // close the file
    fclose(f);
}