//
// Created by ban.tran on 2020-01-29.
//

#ifndef CPP_EPOLL_H
#define CPP_EPOLL_H

int dns_create_kqueue();
void add_to_kqueue(int socketd);
void process_all_event();

#endif //CPP_EPOLL_H
