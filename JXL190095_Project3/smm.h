#ifndef SMM_H
#define SMM_H

// SMM Function Prototypes
int allocate(int pid, int size);
void deallocate(int pid);
int is_allowed_address(int pid, int addr);
int get_base_address(int pid);
void init_smm(); // Helper to set up initial memory hole
int get_holes_created(); // Helper to retrieve the counter

#endif