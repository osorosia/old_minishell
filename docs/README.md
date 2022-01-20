## EBNF
```ebnf
parser    = pipe
pipe      = command ("|" command)*
command   = word (word | redir_in | redir_out)*
redir_in  = ("<" | "<<") word 
redir_out = (">" | ">>") word
word      = (e.g.) "ls", "-l", "file", ...
```

## memo

```
echo aaa > a | cat
>
(aが作成される)

echo aaaa > a bbbb > b cccc
>
(a, bが作成される, a='', b='aaaa bbbb cccc')

・リダイレクトのタイミングが違う
awk '{printf "%sccc\n", $1}' >> aaa
cat >> a

# TODO
ls | cat << main.c
cat <a -e >b >c

```

