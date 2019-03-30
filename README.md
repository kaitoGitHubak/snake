# snake
簡単なスネークゲームです。  
画面サイズなどはコード内の変数を変更して調節してください。
## 操作
q･･･終了  
十字キーで方向を変更  
壁または体に当たったら終了
## 動作環境
glutを使用して描画を行います。glutや必要なソフトをインストールしてください。  
私はlinuxを使用しているのでlinuxに関するインストール方法を掲載します。
~~~
(Vine)
$ sudo apt-get install freeglut freeglut-devel
(Debian, Ubuntu)
$ sudo apt-get install freeglut3 freeglut3-dev
(RedHat, Fedra)
$ sudo yum install freeglut
$ sudo yum install freeglut-devel
~~~
それでも動かない場合は以下をインストールしてください。
~~~
sudo apt-get install libxmu-dev libxi-dev
~~~

## 実行方法
リポジトリ内にあるshellscriptフィルによってコンパイルします。  
gccglに実行権限を与えてください。その後scriptファイルを使ってコンパイルしてください。  
~~~
$./gccgl main.cpp
$./a.out
~~~
