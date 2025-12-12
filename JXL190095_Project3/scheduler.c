#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//struct definition from cpu.c
typedef struct {
    int Base;
    int PC;
    int IR0;
    int IR1;
    int AC;
    int MAR;
    int MBR;
    int ex;
} register_struct;

// function prototypes from cpu.c
register_struct context_switch(register_struct new_vals);

// process control block struct
typedef struct {
    // process id
    int pid;
    // process size
    int size;
    // base register
    int base_reg;
    // include CPU registers for context switching
    register_struct regs;
} PCB;

//prototype for next process function
void next_process(void);

// process table (array) for PCBs
PCB process_table[1024];

// define our nodes for the ready queue
typedef struct node {
    PCB* pcb;
    struct node* next;
} node_t;

// define the tail and the head of the queue
node_t* head = NULL;
node_t* tail = NULL;

// time quantum for each process
const int QUANTUM = 10;

// intialize acting process
PCB *acting_process = NULL;
// PID label
int pid_label = 0;

// round robin scheduler function
int schedule(int cycle_num, int process_status) {
    // if there is no active process return 0
    if (acting_process == NULL) {
        return 0;
    }

    // check process status
    if (process_status == 0) { // process should be removed
        // remove process from front of queue
        node_t* temp = head;
        head = head->next;
        // if queue is now empty, set tail to null
        if (head == NULL) {
            tail = NULL;
            // set acting process to null
            acting_process = NULL;
        } else {
            // set acting process to next process in queue
            acting_process = head->pcb;
        }
        // free previous head node
        free(temp);
        
        // perform context switch if there is a new acting process
        if (acting_process != NULL) {
            context_switch(acting_process->regs);
        }
        else {
            return 0; // no more processes to schedule
        }
        }
    // if process does not need to be removed, check if time quantum expired
    else if (cycle_num >= QUANTUM && (cycle_num % QUANTUM) == 0) {
        // if only one process, continue
        if(head == tail){
            return 1;
        }

        // move process from front to back of queue
        // we can call next_process function to do this
        next_process();

        register_struct old_regs = context_switch(acting_process->regs);
        // save old registers into PCB
        tail->pcb->regs = old_regs;
        
    }
    //continue processes
    return 1;
}

// takes process at fron of the queue and adds it to the back
void next_process() {
    // check if queue is empty or has just one process
    if (head->next == NULL || head == NULL) {
        // do nothing
        return;
    }
    // store current head
    node_t* temp = head;
    // move head to next process
    head = head->next;
    // temp will be new tail
    temp->next = NULL;
    tail->next = temp;
    tail = temp;

    // update acting process
    acting_process = head->pcb;
}

// creates a new process and adds it tot the process talbe as well as adds it at the end of the ready queue
void new_process(int base, int size) {
    //check if process table is full
    if (pid_label >= 1024){
        fprintf(stderr, "Error: Process table full\n");
        return;
    }
    // create a new PCB at pid label address
    PCB *new_pcb = &process_table[pid_label];
    new_pcb->pid = pid_label;
    // given size and base address
    new_pcb->size = size;
    new_pcb->base_reg = base;

    // initialize registers
    // all but base address can initialized to 0
    new_pcb->regs.Base = base;
    new_pcb->regs.PC = 0;
    new_pcb->regs.IR0 = 0;
    new_pcb->regs.IR1 = 0;
    new_pcb->regs.AC = 0;
    new_pcb->regs.MAR = 0;
    new_pcb->regs.MBR = 0;
    new_pcb->regs.ex = 0;

    // allocate a new node for the process
    // malloc is used to store the node in the heap
    node_t* new_node = (node_t*)malloc(sizeof(node_t));

    // set node of pcb to created node 
    new_node->pcb = new_pcb;
    // next pointer to null
    new_node->next = NULL;

    // add PCB to the end of the queue
    if (tail == NULL) { // queue is empty
        head = new_node;
        tail = new_node;
    } else { // queue is not empty so add to end
        tail->next = new_node;
        tail = new_node;
    }

    // if the acting process is null, set it to the new process
    if (acting_process == NULL) {
        acting_process = new_pcb;
        //and load its registers into the CPU
        context_switch(acting_process->regs);
    }
    // increment pid label for next process
    pid_label++;
}

/* New functions for project 3*/

// remove process from ready queue given its PID
void remove_process(int pid) {
    // if queue is empty return
    if (head == NULL) {
        return;
    }

    //get current and previous nodes
    node_t* current = head;
    node_t* previous = NULL;

    // traverse the queue to find the process with given PID
    while (current != NULL) {
        // if the current node's PCB has the matching PID
        if (current->pcb->pid == pid) {
            // if it's the head node
            if (previous == NULL) {
                head = current->next;
                // if head is now null, set tail to null
                if (head == NULL) {
                    tail = NULL;
                }
            } else {
                previous->next = current->next;
                // if we removed the tail, update tail pointer
                if (current == tail) {
                    tail = previous;
                }
            }
                // if the removed process was the acting process clear acting process
                if (acting_process->pid == current->pid) {
                    acting_process = NULL;
                }
                // free the removed node
                free(current);
                return;
            }
            // move to next node
            previous = current;
            current = current->next;
        }        
    }
// return PID of current acting process
int current_pid() {
    // check for active process
    if (acting_process == NULL) {
        // return -1 if no active process
        return -1; 
    }
    //else return pid of acting process
    return acting_process->pid;
}

// return PID of next process
int next_pid() {
    return pid_label;
}