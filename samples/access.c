#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char **argv, char **arge) {
    printf("access: ./a.out => OK(%d==0)\n", access("./a.out", X_OK));
    printf("access: a.out => OK(%d==0)\n", access("a.out", X_OK));
}
