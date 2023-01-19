#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/rand.h"
#include "user.h"

int main(void) {

    for(int i = 0; i < 1000; i++) {
        printf(1, "%d\n", random_at_most(100));
    }
    exit();
}