#include "../libft.h"
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>

#define CASE(s) printf("\n%s:", s)
#define OK() printf("o")
#define KO() printf("x")

void assert_bool(bool expected, bool actual) {
    if (actual == expected) OK();
    else KO();
}

void assert_char_p(char *expected, char *actual) {
    if (!strcmp(expected, actual)) OK();
    else KO();
}

int main() {
    printf("------start------");
    CASE("ft_isnumber");
    assert_bool(true, ft_isnumber("12"));
    assert_bool(true, ft_isnumber("-12"));
    assert_bool(true, ft_isnumber("+12"));
    assert_bool(true, ft_isnumber("0"));
    assert_bool(true, ft_isnumber("+0"));
    assert_bool(true, ft_isnumber("-0"));
    assert_bool(true, ft_isnumber("012"));
    assert_bool(true, ft_isnumber("0012"));
    assert_bool(true, ft_isnumber("-0012"));
    assert_bool(true, ft_isnumber("+0012"));
    assert_bool(false, ft_isnumber("--122"));
    assert_bool(false, ft_isnumber("++122"));
    assert_bool(false, ft_isnumber("-"));
    assert_bool(false, ft_isnumber("+"));
    CASE("get_next_line");
    int fd = open("test.txt", O_RDONLY);
    char *expected[] = {
        "aaaaaaaa\n","bbbbbbb\n","cccccc\n","ddddd\n","eeee\n","fff\n","gg\n","h\n",
    };
    for (int i = 0; i < sizeof(expected)/sizeof(expected[0]); i++) {
        char *line = get_next_line(fd);
        assert_char_p(expected[i], line);
        if (line == NULL) break;
        free(line);
    }
    printf("\n-------end-------\n");
}
