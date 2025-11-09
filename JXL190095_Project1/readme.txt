Project 1 - Computer Simulator

Files:

-memory.c
-cpu.c
-disk.c
-main.c

## memory.c

    memory.c is the acting program for the RAM of the simple computer
    it holds a 2 dimensional 1024 x 2 integer array that is used to represent
    the RAM, it holds the operation codes of the instruction at position 0 and the
    operand at postion 1.

## cpu.c

    this acts as the CPU of the computer and executes any arithmatic and logic
    operations needed from the chosen opcode in memory by using a switch case and the
    translated program is stored in memory.

## disk.c

    this acts as the program storage and translator for the computer. it will
    begin a filestream to read from a txt file in the same directory and 
    translate formatted instructions into its opcode integer equivalents into memory
    using a jumptable. Will throw an error if file is not found within directory.

## main.c

    the program driver that begins the program execution of the computer. Clears the
    memory.c array at start of the program and later prints the first 20 addresses
    at program termination. The program text files MUST be within the same directory
    as the executable or will not run correctly.

    The txt file it searches for is hard coded and named "fname.txt". You may change it by
    modifying the string in line 37 of the main.c program.

## Compiling

    the program was compiled using 

    "gcc memory.c cpu.c disk.c main.c -o main"

    and executed with 

    "./main"

    all programs should be compiled while in the same directory