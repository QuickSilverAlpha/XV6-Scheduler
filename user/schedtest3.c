#include "kernel/syscall.h"
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user.h"

int is_prime(long prime_no, int child_no){
    long i, num = prime_no, temp = 0; 

    // iterate up to n/2.

    for (i = 2; i <= num / 2; i++)
    {

        // check if num is divisible by any number.
        printf(1, "Child %d cpu count: %d\n", child_no, retcpucount());

        if (num % i == 0)
        {

            temp++;

            break;

        }

    } 

    // check for the value of temp and num. 

    if (temp == 0 && num != 1)

    {

        printf(1, "%d is a Prime number!\n", num);

    }

    else

    {

        printf(1, "%d is not a Prime number!\n", num);

    }
    return 0;
}

int main(void) {
    //Lotter sched Test with 5 children, each determining a number if its prime or not. 
    int mode = schedmode(1);
    printf(1, "Mode: %d\n", mode);
    printf(1, "LOTTERY BASED SCHEDULER ACTIVE...\n");
    
    if(fork() != 0){

        
        if(fork() != 0){


            if(fork() != 0){


                
                if(fork() != 0){



                    
                    if(fork() != 0){
                        wait();   
                    }

                    else {
                        printf(1, "I am child: 5\n");
                        printf(1, "Highest priortiy set by Child 5: [%d]\n", nice(0));
                        printf(1, "Tickets for Child 5: %d\n", rettickets());
                        is_prime(179424673, 5);
                        // printf(1, "Child 5 cpu count: %d\n", retcpucount());
                        printf(1, "Child 5 done!\n");
                    }
                    wait();
                }

                else {
                    printf(1, "I am child: 4\n");
                    is_prime(179424673, 4);
                    // printf(1, "Child 4 cpu count: %d\n", retcpucount());
                    printf(1, "Child 4 done!\n");
                }
                wait();


            }

            else {
                printf(1, "I am child: 3\n");
                printf(1, "Lowest priortiy set by Child 3: [%d]\n", nice(101));
                //printf(1, "Tickets for Child 3: %d\n", rettickets());
                is_prime(179424673, 3);
                printf(1, "Child 3 cpu count: %d\n", retcpucount());
                printf(1, "Child 3 done!\n");
            }
            wait();
               
        }

        else {
            printf(1, "I am child: 2\n");
            is_prime(179424673, 2);
            //printf(1, "Child 2 cpu count: %d\n", retcpucount());
            printf(1, "Child 2 done!\n");
        }
        wait();

    }

    else {
        printf(1, "I am child: 1\n");
        is_prime(179424673, 1);
        //printf(1, "Child 1 cpu count: %d\n", retcpucount());
        printf(1, "Child 1 done!\n");
    }
    exit();


}