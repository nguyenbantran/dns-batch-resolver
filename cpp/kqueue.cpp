//
// Created by ban.tran on 2020-01-29.
//

#include "kqueue.h"
#include "dns.h"

#include <sys/socket.h>
#include <sys/un.h>
#include <sys/event.h>
#include <netdb.h>
#include <assert.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>

#include <iostream>


static int kq;
static int input = 0;

int dns_create_kqueue() {

    kq = kqueue();

    std::cout << kq << std::endl;

    return 0;
}

void add_to_kqueue(int s) {
    if (true) {
        int flags = fcntl(s, F_GETFL, 0);
        assert(flags >= 0);
        fcntl(s, F_SETFL, flags | O_NONBLOCK);
    }

    struct kevent evSet;
    // Listen on the new socket
    EV_SET(&evSet, s, EVFILT_READ, EV_ADD, 0, 0, NULL);
    kevent(kq, &evSet, 1, NULL, 0, NULL);
    printf("\nGot connection: %d\n", input);
    input++;
}

int count = 0;

void process_all_event() {

    struct kevent evList[32];
    while (1) {
        // returns number of events
        int nev = kevent(kq, NULL, 0, evList, 32, NULL);
//        printf("kqueue got %d events\n", nev);

        for (int i = 0; i < nev; i++) {
            int fd = (int)evList[i].ident;

            if (evList[i].flags & EV_EOF) {
                printf("Disconnect\n");
                close(fd);
                // Socket is automatically removed from the kq by the kernel.
            }  else if (evList[i].filter == EVFILT_READ) {
                // Read from socket.
                char buf[1024];
                size_t bytes_read = recv(fd, buf, sizeof(buf), 0);
                printf("read %zu bytes\n", bytes_read);

                receiv_and_print_info((unsigned char*) buf);
                count ++;
                if (count == input) {
                    return;
                }


            } else if (evList[i].filter == EVFILT_WRITE) {
//                printf("Ok to write more!\n");


            }
        }
    }
}
