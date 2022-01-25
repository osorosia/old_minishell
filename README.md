# minishell

minishellはbashライクの小さなシェルです。私が現在通っている42 Tokyoの課題として作成しています。

## 使用方法
- Ubuntu
```
$ sudo apt install libreadline-dev
$ make all
$ ./minishell

(minishell)> # input command
```

## 構成
`[input]->[lexer]->[parser]->[expander]->[command exec]`のデータの流れで作成しました。

### input
ユーザーからの入力を受け取ります。minishellでは`readline`ライブラリを使用しました。`readline`はユーザから編集機能付きで1行受け取ります。カーソルキー受付やコマンド履歴機能を簡単に実装することができます。

```c
#include <readline/readline.h>
#include <readline/history.h>

char *readline (char *prompt);
```

### lexer
ユーザから受け取った文字列に対して字句解析を行います。字句解析では単語と演算子の2種類に分類します。minishellでは`for`や`if`などが存在しないので、予約語は分類する必要がありません。

- 単語：e.g. `ls`, `-l`, `a'b'c`, `" a "`, ...
- 演算子： `<`, `<<`, `>`, `>>`, `|`

`'`や`"`については、囲まれている箇所も含めて単語と扱うようにしました。これは字句解析ではスペース文字をデリミタとして解析しますが、`'`や`"`で囲まれた箇所はスペース文字を字句の一部として解析する必要があるためです。

```c
typedef enum e_token_kind {
    TK_WORD, // 単語
    TK_OP,   // 演算子
    TK_EOF,  // 入力の終端
} t_token_kind;
```
`minishell`をデバッグモードで実行すると、コマンド実行時に字句解析の結果を見ることができます。
```sh
(minishell)> ls -l
lexer::::::::::::::
    {kind:TK_WORD, str:ls}
    {kind:TK_WORD, str:-l}
    {kind:TK_EOF , str:}
```

### parser
lexerの結果を、再帰下降構文解析と呼ばれる方法で構文解析します。最初にBNF(Backus-Naur form)を拡張したEBNF(Extended BNF)の生成規則を作成します。

```ebnf
parser    = pipe_cmd EOF
pipe_cmd  = command ("|" command)*
command   = word (word | redir_in | redir_out)*
redir_in  = ("<" | "<<") word 
redir_out = (">" | ">>") word
word      = (e.g.) "ls", "-l", "file", ...
EOF       = ε
```

次に、生成規則の左辺を関数にします。
```cpp
t_node *parser(t_token *tok);
t_node *pipe_cmd(t_token **tok);
t_node *command(t_token **tok);
t_node *redir_in(t_token **tok);
t_node *redir_out(t_token **tok);
t_node *word(t_token **tok);
```
再帰下降構文解析とは、上記のような1つの生成規則を1つの関数にマップするという構文解析の手法です。
（[低レイヤを知りたい人のためのCコンパイラ作成入門](https://www.sigbus.info/compilerbook)を多大に参考にさせていただきました）

`minishell`をデバッグモードで実行すると、コマンド実行時に構文解析の結果を見ることができます。
```sh
(minishell)> ls -l | cat > file
parser::::::::::::::
    cmds   : 'ls' '-l' 
    ----PIPE----
    cmds   : 'cat' 
    red_out: 'file' # 標準出力のリダイレクト
```

## 42 Tokyo

42 Tokyoでは、講師や授業がない状態で課題が始まります。課題として仕様が書かれたPDFが配布されますが、解答やヒントはほぼありません。その代わりに、学生に無料で開放されているキャンパスやDiscordで学生同士で交流し、知見を共有したりお互い助け合うことができます。

minishellを提出するには、下記の課題をクリアする必要があります。
- C言語の標準関数群(libc)の実装
- 入力行を1行取得するアンバッファドな入力関数(≒関数fgets)の実装
- printfの実装
- VirtualBox上でDebian環境を構築
    - パーティション設定, ユーザ・グループの管理, パスワードポリシー, sudoのセキュリティポリシー, cronなど
- シグナル(SIGUSR1,SIGUSR2)を使ったプログラム間通信
- 2つの両端キュー構造に格納された数字を短手数でソートするプログラム
- X-Window programming API(minilibx)を使用したプログラム
    - 簡単な2Dゲーム作成 or フラクタル構造の描画 or シンプルな3D描画
