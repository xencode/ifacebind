/*
   Copyright (C) 2000  Daniel Ryde
   Copyright (C) 2016  Nubolabs Inc.

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.
*/

/*
   LD_PRELOAD library to make connect bind to a specific interface.
   This is specified via the enviroment variable BIND_IFACE.

   Compile on Linux with:
   gcc -nostartfiles -fpic -shared ifacebind.c -o ifacebind.so -ldl -D_GNU_SOURCE

   Example in bash to make inetd only listen to the loopback
   lo interface, thus disabling remote connections and only
   enable to/from localhost:

   BIND_IFACE="lo" LD_PRELOAD=./ifacebind.so /sbin/inetd
*/


#include <config.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <dlfcn.h>
#include <errno.h>
#include <arpa/inet.h>
#include <string.h>

int (*real_connect)(int, const struct sockaddr *, socklen_t);

char* bind_iface = NULL;
int bind_iface_len = 0;
int debug = 0;


void _init (void)
{
        const char *err;

        real_connect = dlsym(RTLD_NEXT, "connect");
        if ((err = dlerror()) != NULL) {
                fprintf (stderr, "dlsym (connect): %s\n", err);
        }

        if (bind_iface = getenv("BIND_IFACE")) {
            bind_iface_len = strlen(bind_iface);
        }

        if (getenv("DEBUG")) {
            debug = 1;
        }

}


int connect (int fd, const struct sockaddr *sk, socklen_t sl)
{
        static struct sockaddr_in *rsk_in;

        rsk_in = (struct sockaddr_in *)sk;

        if (debug) {
                fprintf(stderr, "connect: %d %s:%d\n", fd, inet_ntoa(rsk_in->sin_addr),
                        ntohs(rsk_in->sin_port));                
        }
        if (bind_iface_len > 0 
                && (rsk_in->sin_family == AF_INET
                && ntohs(rsk_in->sin_port) != 53)
                ) {
                if (setsockopt(fd, SOL_SOCKET, SO_BINDTODEVICE, bind_iface, bind_iface_len) != 0) {
                    return -1;
                }
        }
        return real_connect (fd, sk, sl);
}
