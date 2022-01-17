#include "../minishell.h"
#include <assert.h>

void test() {
    t_token *tok = lexer("aaa");
}

int main(int argc, char **argv) {
    // automatic test
    setvbuf(stdout, NULL, _IONBF, 0);
    test();

    printf("parser: OK\n");
}
