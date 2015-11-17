

Build:

`export PKG_CONFIG_PATH=$HOME/tools/libbitcoin/lib/pkgconfig:$PKG_CONFIG_PATH`


`clang++ $(pkg-config --cflags --libs libbitcoin) -std=c++11 -o ex4-2 ex4-2.cpp`
