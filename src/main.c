#include "shared.h"
#include <unistd.h>

int main()
{
    Environment Env = initEnv();
    printEnv(Env);
    while (1) {
        step(&Env);
        printEnv(Env);
        sleep(1);
    }

    return 0;
}
