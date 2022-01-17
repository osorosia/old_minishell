#include "../minishell.h"
#include <string.h>
#include <assert.h>

void print_start(char *p) {
    printf(p);
    printf(" => ");
}

void print_end() {
    printf("\n");
}

void assert_token(t_token **tok, t_token_kind kind, char *str) {
    assert((*tok)->kind == kind);
    assert(memcmp((*tok)->str, str, (*tok)->len) == 0);
    printf("'%.*s' ", (*tok)->len, (*tok)->str);
    *tok = (*tok)->next;
}

void test1() {
    const char *p = "foo";
    print_start(p);

    t_token *tok = lexer(p);
    t_token *head = tok;

    assert_token(&tok, TK_WORD, "foo");
    assert_token(&tok, TK_EOF,  "");

    free_lexer(head);
    print_end();
}

void test2() {
    const char *p = "foo | hoge";
    print_start(p);

    t_token *tok = lexer(p);
    t_token *head = tok;

    assert_token(&tok, TK_WORD, "foo");
    assert_token(&tok, TK_OP,   "|");
    assert_token(&tok, TK_WORD, "hoge");
    assert_token(&tok, TK_EOF,  "");

    free_lexer(head);
    print_end();
    return true;
}


int main(int argc, char **argv) {
    // manual test
    if (argc == 2) {
        t_token *tok = lexer(argv[1]);
        debug_lexer(tok);
        free_lexer(tok);
        return (0);
    }

    // automatic test
    setvbuf(stdout, NULL, _IONBF, 0);
    test1(); // foo
    test2(); // foo | hoge

    printf("OK\n");
}
