#include "kernel/types.h"
#include "kernel/stat.h"
#include "user.h"


int main(void) {

    
    int out = nice(5);
    printf(1, "%d \n", out);

    int out2 = nice(-5);
    printf(1, "%d \n", out2);

    int out3 = nice(0);
    printf(1, "%d \n", out3);

    int out4 = nice(2147483647);
    printf(1, "%d \n", out4);

    int out5 = nice(4294967295);
    printf(1, "%d \n", out5);

    //Attempting to pass a character to the argument of nice() results in a compilation error

    //Attempting to pass a number >4,294,967,295 to the argument of nice() results in a compilation error

    exit();
}