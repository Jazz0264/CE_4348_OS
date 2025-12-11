Project 1 - Computer Simulator

Files:

-memory.c
-cpu.c
-disk.c
-main.c
-scheduler.c

## memory.c

    memory.c is the acting program for the RAM of the simple computer
    it holds a 2 dimensional 1024 x 2 integer array that is used to represent
    the RAM, it holds the operation codes of the instruction at position 0 and the
    operand at postion 1.

## cpu.c

    this acts as the CPU of the computer and executes any arithmatic and logic
    operations needed from the chosen opcode in memory by using a switch case and the
    translated program is stored in memory.

    context_switch() was added for project 2 to support saving and loading register
    states of PCBs

## disk.c

    this acts as the program storage and translator for the computer. it will
    begin a filestream to read from a txt file in the same directory and 
    translate formatted instructions into its opcode integer equivalents into memory
    using a jumptable. Will throw an error if file is not found within directory.

    load_programs() was added for project 2, looks for a "program_list.txt" file
    within the same directory containing the program names of other programs that
    are to be searched in the same directory

## main.c

    the program driver that begins the program execution of the computer. Clears the
    memory.c array at start of the program and later prints the first 20 addresses
    at program termination. The program text files MUST be within the same directory
    as the executable or will not run correctly.

    for project 2 the main.c program also keeps track of the process and scheduler states
    as well as clock cycles for the scheduling algorithm.

    Is hard coded to search for the program list "program_list.txt" within the same directory
    and can be changed in line 46

## scheduler.c

    this program was implemented for project 2 and handles the round robin scheduling
    and the creation of process control blocks of the programs within the program_list.txt 
    file with a time quantum of 10 clock cycles.

    the time quantum can be changed at line 49 to some other constant.

## Compiling

    the program was compiled using 

    "gcc memory.c cpu.c disk.c main.c scheduler.c -o main"

    and executed with 

    "./main"

    all programs should be compiled while in the same directory