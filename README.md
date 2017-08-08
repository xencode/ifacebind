# ifacebind
An LD_PRELOAD library to force a network connection to bind to a specific interface

## Installation

Compile on Linux with:
```
./configure
make
sudo make install
```

The desired interface is specified via the enviroment variable BIND_IFACE.

The format of the command is:

BIND_IFACE="interface" LD_PRELOAD=./ifacebind.so <application path>

An example in bash to make the application 'inetd' only listen to the loopback lo interface, thus disabling remote connections and only allow connections to/from localhost:

BIND_IFACE="lo" LD_PRELOAD=./ifacebind.so /sbin/inetd
