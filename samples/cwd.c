#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define SIZE 512

int main(int argc, char **argv, char **arge) {
    char pathname[SIZE];

    memset(pathname, 0, SIZE);
 
    printf("getcwd:%s\n", getcwd(pathname, SIZE));
    chdir("..");
    printf("getcwd:%s\n", getcwd(pathname, SIZE));
    chdir("temp");
    printf("getcwd:%s\n", getcwd(pathname, SIZE));
}
