/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 06:16:07 by rnishimo          #+#    #+#             */
/*   Updated: 2022/01/20 12:17:15 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
    char *p = "foo";
    print_start(p);

    t_token *tok = lexer(p);
    t_token *head = tok;

    assert_token(&tok, TK_WORD, "foo");
    assert_token(&tok, TK_EOF,  "");

    free_lexer(head);
    print_end();
}

void test_pipe() {
    char *p = "foo0|foo1 | foo2 || foo3";
    print_start(p);

    t_token *tok = lexer(p);
    t_token *head = tok;

    assert_token(&tok, TK_WORD, "foo0");
    assert_token(&tok, TK_OP,   "|");
    assert_token(&tok, TK_WORD, "foo1");
    assert_token(&tok, TK_OP,   "|");
    assert_token(&tok, TK_WORD, "foo2");
    assert_token(&tok, TK_OP,   "|");
    assert_token(&tok, TK_OP,   "|");
    assert_token(&tok, TK_WORD, "foo3");
    assert_token(&tok, TK_EOF,  "");

    free_lexer(head);
    print_end();
}

void test_redirect() {
    char *p = "foo0>foo1>>foo2<foo3<<foo4<<<foo5>>>foo6";
    print_start(p);

    t_token *tok = lexer(p);
    t_token *head = tok;

    assert_token(&tok, TK_WORD, "foo0");
    assert_token(&tok, TK_OP,   ">");
    assert_token(&tok, TK_WORD, "foo1");
    assert_token(&tok, TK_OP,   ">>");
    assert_token(&tok, TK_WORD, "foo2");
    assert_token(&tok, TK_OP,   "<");
    assert_token(&tok, TK_WORD, "foo3");
    assert_token(&tok, TK_OP,   "<<");
    assert_token(&tok, TK_WORD, "foo4");
    assert_token(&tok, TK_OP,   "<<");
    assert_token(&tok, TK_OP,   "<");
    assert_token(&tok, TK_WORD, "foo5");
    assert_token(&tok, TK_OP,   ">>");
    assert_token(&tok, TK_OP,   ">");
    assert_token(&tok, TK_WORD, "foo6");
    assert_token(&tok, TK_EOF,  "");

    free_lexer(head);
    print_end();
}

void test_quote() {
    char *p = "'foo0' \"foo1\" ''foo2'' \"\"foo3\"\"";
    print_start(p);

    t_token *tok = lexer(p);
    t_token *head = tok;

    assert_token(&tok, TK_OP,   "'");
    assert_token(&tok, TK_WORD, "foo0");
    assert_token(&tok, TK_OP,   "'");

    assert_token(&tok, TK_OP,   "\"");
    assert_token(&tok, TK_WORD, "foo1");
    assert_token(&tok, TK_OP,   "\"");

    assert_token(&tok, TK_OP,   "'");
    assert_token(&tok, TK_OP,   "'");
    assert_token(&tok, TK_WORD, "foo2");
    assert_token(&tok, TK_OP,   "'");
    assert_token(&tok, TK_OP,   "'");

    assert_token(&tok, TK_OP,   "\"");
    assert_token(&tok, TK_OP,   "\"");
    assert_token(&tok, TK_WORD, "foo3");
    assert_token(&tok, TK_OP,   "\"");
    assert_token(&tok, TK_OP,   "\"");

    assert_token(&tok, TK_EOF,  "");

    free_lexer(head);
    print_end();
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
    printf("lexer=================================\n");
    test1();            // foo
    test_pipe();        // foo0|foo1 | foo2 || foo3
    test_redirect();    // foo0>foo1>>foo2<foo3<<foo4<<<foo5>>>foo6
    test_quote();       // 'foo0' "foo1" ''foo2'' ""foo3""

    printf("lexer OK==============================\n");
}
