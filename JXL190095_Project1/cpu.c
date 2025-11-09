#include <stdio.h>

// function prototypes from memory.c
int *mem_read(int addr);
void mem_write(int addr, int *data);

// The CPU registers
// holds the address of current program (we start at 4 per instructions)
int Base = 4;
// program counter: address of next instruction
int PC = 0;
// stores op code
int IR0 = 0;
// stores operand
int IR1 = 0;
// stores result of operation
int AC = 0;
// holds address of memory to be accessed
int MAR = 0;
// holds content of memory location pointed by MAR
int MBR = 0;
// flag to indicate if exit instruction has been encountered
int ex = 0;

// return true memory address
int mem_address(int l_addr)
{
    return Base + l_addr;
}

// fetch instruction from memory
void fetch_instruction(int addr)
{
    // calculate the actual memory address
    int next = mem_address(addr);
    // return a pointer to the instruction at next address
    int *op = mem_read(next);
    // error check for null pointer
    if (op == NULL)
    {
        printf("Failed to fetch instruction at address %d\n", next);
        // default to exit
        IR0 = 0;
        IR1 = 0;
        return;
    }
    // load instruction into IR
    IR0 = op[0]; // opcode
    IR1 = op[1]; // operand
}

// executer the instructions in the IRO and IR1 registers
void execute_instruction()
{
    // disk.c will handle operation translation so IR0 is an int
    switch (IR0)
    {
    // exit instruction
    case 0:
        ex = 1;
        break;
    // load int(operand) into AC
    case 1:
        AC = IR1;
        break;
    // move int from MBR into AC
    case 2:
        AC = MBR;
        break;
    // move int from MAR into AC
    case 3:
        AC = MAR;
        break;
    // move int from AC into MBR
    case 4:
        MBR = AC;
        break;
    // move int from AC into MAE
    case 5:
        MAR = AC;
        break;
    // load int into MBR from address in MAR
    case 6:
     {   // retrieve pointer to memory location
        int *addr = mem_read(MAR);
        // check pointer
        if (addr)
        {
            // load MBR with operand at that address
            MBR = addr[1];
        }
        // default to 0 if addr is null
        else
            MBR = 0;
        break;
    }
    // write int at MBR to address in MAR
    case 7:
    {
        int tmp[2] = {0, MBR};
        mem_write(MAR, tmp);
        break;
    }
    // add int at MBR to AC
    case 8:
        AC = AC + MBR;
        break;
    // mulitply int at MBR with AC -> AC
    case 9:
        AC = AC * MBR;
        break;
    // perform logical AND between MBR and AC -> AC
    case 10:
        AC = (AC != 0) && (MBR != 0);
        break;
    // logical OR between MBR and AC -> AC
    case 11:
        AC = (AC != 0) || (MBR != 0);
        break;
    // ifgo when AC != 0 then PC = addr - 1F
    case 12:
        if (AC != 0)
        {
            // IR1 will hold the address to jump to
            PC = IR1 - 1;
        }
        break;
    // sleep. do nothing
    case 13:
        break;
    // default prints unknown opcode
    default:
        printf("Unknown opcode: %d\n", IR0);
        break;
    }
}

int clock_cycle()
{
    // fethch the next instruction
    fetch_instruction(PC);
    // excecute based on opcode
    execute_instruction();
    // increment PC
    PC = PC + 1;
    // return 1 if no exit code seen
    if (ex)
        return 0;
    else
        return 1;
}