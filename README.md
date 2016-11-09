# ifacebind
An LD_PRELOAD library to force a network connection to bind to a specific interface

## Installation

Compile on Linux with:
```
./configure
make
sudo make install
```

This is specified via the enviroment variable BIND_IFACE.


Example in bash to make inetd only listen to the loopback
lo interface, thus disabling remote connections and only
enable to/from localhost:

BIND_IFACE="lo" LD_PRELOAD=./ifacebind.so /sbin/inetd
