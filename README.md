# threading techniques collection
バイトコード・中間コードインタプリタ実装の核となる、
各種命令ディスパッチ手法のサンプル集とベンチマーク。

元ネタは
[Gforth](http://www.gnu.org/software/gforth/)
の主要開発者の一人Anton Ertl先生の
[Speed of various interpreter dispatch techniques V2](http://www.complang.tuwien.ac.at/forth/threading)
。

## 使い方
i386アーキテクチャをサポートするUNIX系OS上でGNU makeを用意してから
    $ make bench
でベンチマークを実行。
