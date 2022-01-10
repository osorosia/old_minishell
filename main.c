#include "minishell.h"

int main() {
    char *prompt = "minishell>";
    
    using_history();
    read_history(".my_history"); // [ToDo]historyファイルが無いときの動作の検証
    while (1) {
        char *str = readline(prompt);
        t_token *tok = tokenize(str);
        debug_tokenize(tok);
        // printf("%s\n", str);
        add_history(str);
    }
    write_history(".my_history");
}

// build:
//   gcc read.c -L/usr/include -lreadline
