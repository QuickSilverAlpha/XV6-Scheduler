#include "kernel/types.h"
#include "kernel/stat.h"
#include "user.h"



int main(void) {
    //Round Robin Test First
    int mode = schedmode(1);
    printf(1, "Mode: %d\n", mode);
    printf(1, "LOTTERY BASED SCHEDULER ACTIVE...\n");
    
    if(fork() != 0){
        if(fork() != 0){
         wait();   
        }
        else {
            printf(1, "I am child: 2\n");
            printf(1, "Highest priortiy set by Child 2: [%d]\n", nice(0));
            printf(1, "Tickets for Child 2: %d\n", rettickets());
            int num;
            for (int i = 0; i < 100; i++){
                num = num + i*0.4;
                printf(1, "(Child 2): computed result: %d\n", num);
            }
            printf(1, "Child 2 done!\n");
        }
        wait();   
    }
    else {
        printf(1, "Lowest priortiy set by Child 1: [%d]\n", nice(100));
        printf(1, "Tickets for Child 1: %d\n", rettickets());
        printf(1, "I am child: 1\n");
        int num;
        for (int i = 0; i < 100; i++){
            num = num + i*0.4;
            printf(1, "(Child 1): computed result: %d\n", num);
        }
        printf(1, "Child 1 done!\n");
    }
    exit();
}