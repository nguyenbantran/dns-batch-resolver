//
// Created by ban.tran on 2020-01-29.
//

#include "kqueue.h"

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


static int socket_fd, epoll_fd;

int dns_create_kqueue() {

    epoll_fd = kqueue();

    std::cout << epoll_fd << std::endl;

    return 0;
}



