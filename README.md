# minishell

minishellはbashライクの小さなシェルです。私が現在通っている42 Tokyoの課題として作成しています。

## 42 Tokyo

42 Tokyoでは、講師や授業がない状態で課題が始まります。課題として仕様が書かれたPDFが配布されますが、解答やヒントはほぼありません。その代わりに、学生に無料で開放されているキャンパスやDiscordで学生同士で交流し、知見を共有したりお互い助け合うことができます。

minishellを提出するには、下記の課題をクリアする必要があります。
- C言語の標準関数(libc)の実装
- 関数呼び出しごとにFDから文字列を1行ずつ取得する関数の実装（read, malloc, freeのみ使用）
- printfの実装
- VirtualBox上でDebian環境を構築
    - パーティション設定, ユーザ・グループの管理, パスワードポリシー, sudoのセキュリティポリシー, cronなど
- シグナル(SIGUSR1,SIGUSR2)を使ったプログラム間通信
- 2つの両端キュー構造に格納された数字を短手数でソートするプログラム
- X-Window programming API(minilibx)を使用したプログラム
    - 簡単な2Dゲーム作成 or フラクタル構造の描画 or シンプルな3D描画

## 使用方法
- Ubuntu
```
$ sudo apt install libreadline-dev
$ make all
$ ./minishell

(minishell)> # input command
```

## 構成
`[lexer]->[parser]->[expander]->[command exec]`のデータの流れで作成した。

