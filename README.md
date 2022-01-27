# minishell

minishellはbashライクの小さなシェルです。私が現在通っている42 Tokyoの課題として作成しています。

## 42 Tokyo

42 Tokyoでは、講師や授業がない状態で課題が始まります。課題として仕様が書かれたPDFが配布されますが、解答やヒントはほぼありません。その代わりに、学生に無料で開放されているキャンパスやDiscordで学生同士で交流し、知見を共有したりお互い助け合うことができます。

minishellを提出するには、下記の課題をクリアする必要があります。
- C言語の標準関数群(libc)の実装
- 入力行を1行取得するバッファリングありの入力関数(≒関数fgets)の実装
- printfの実装
- VirtualBox上でDebian環境を構築
    - パーティション設定, ユーザ・グループの管理, パスワードポリシー, sudoのセキュリティポリシー, cronなど
- シグナル(SIGUSR1,SIGUSR2)を使ったプログラム間通信
- 2つの両端キュー構造に格納された数字を短手数でソートするプログラム
- X-Window programming API(minilibx)を使用したプログラム
    - 簡単な2Dゲーム作成 or フラクタル構造の描画 or シンプルな3D描画

## 使用方法
- Ubuntu
```bash
sudo apt install libreadline-dev
make all # or make debug (DEBUG mode)
./minishell

(minishell)> # input command
```

## 機能
- プロンプト表示
- コマンド履歴機能
- `|`
- `<<`, `<`, `>>`, `>`
- `'`, `"`
- `$`
- Builtin:
    - `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`

## 構成
下記のデータの流れで作成しています。
1. input
1. lexer
1. parser
1. expander
1. exec

### input
ユーザーからの入力を受け取ります。minishellでは`readline`ライブラリを使用しました。`readline`はユーザから編集機能付きで1行受け取ります。カーソルキー受付やコマンド履歴機能を簡単に搭載できます。

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

### expander
expanderでは下記のことを行います。

1. 変数展開
1. `'`, `"`の削除
1. コマンドのパス取得

変数展開では`$var`をvar変数の値に置換します。登録されている環境変数はexportやenvで確認することができます。

変数展開後は、`'`と`"`が不要になったので削除します。

コマンドのパス取得では`ls`->`/bin/ls`の変換を行います。シェルのコマンドは基本的に実行ファイルです（ビルトインコマンドを除く）。コマンドを入力すると`$PATH`に登録されたパスを前から探索し、見つかったファイルを実行します。見つからなかった場合は標準エラー出力に`command not found`を出力します。

`minishell`をデバッグモードで実行すると、コマンド実行時にexpanderの結果を見ることができます。
```sh
(minishell)> pwd | cat -e | foo
expander::::::::::::::
    cmds   : 'pwd' 
        - builtin
    ----PIPE----
    cmds   : 'cat' '-e' 
        - path: /bin/cat (exist)
    ----PIPE----
    cmds   : 'foo'
```

### exec

ビルトインコマンドは実装する必要があります。`minishell`は次のコマンドを実装しました。
- `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`

実行ファイルの場合、`execve`関数によってコマンドを実行します。ただし、`execve`関数は呼び出し元のプロセスのスタックを実行するプログラムの内容に上書きするため、そのまま呼び出すとコマンド終了とともに`minishell`が落ちてしまいます。落ちないようにするためには、`fork`関数で子プロセスを作成し、子プロセス上で`execve`関数を呼び出せばよいです。

ここで注意点があります。
- ビルトインコマンドは子プロセスで実行しないこと
    - e.g. 子プロセスで`cd`しても親プロセスで反映されない
- ただし、`|`を含むコマンドは子プロセスで実行する
    - e.g. `cd .. | ls`の出力は`ls`の結果と同じ
