# minishell


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

```

cat <a -e >b >c
ND_CMD
    words    : "cat" "-e"
    redirects: "<a" ">b" 
    redirects: NULL
    redirects: "<a" NULL
    redirects: ">b" "<a" NULL
    redirects: ">c" ">b" "<a" NULL