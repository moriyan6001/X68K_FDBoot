# X68K_FDBoot
X68000のフロッピーディスクからHuman68Kを使わずにプログラムを起動する実験プログラム一式です。実機未確認です。ネット上で配布されているHAS, HLK, HCVは含まれていません。

## ファイル構成

- IPL_TB.s ... TINY BASICを起動するためのフロッピーディスク用IPL
- TBI68K.ASM  ... X68000用に書き換えたTINY BASIC
- m.bat ... ディスクに書き込むバイナリを生成する
- X68000_TinyBasic.xdf ... TINY BASICが起動するディスクイメージ

## 関連記事

https://zenn.dev/morian/articles/ab313ec56c4c4f
