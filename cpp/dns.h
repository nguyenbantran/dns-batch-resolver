//
// Created by ban.tran on 2020-01-29.
//

#ifndef CPP_DNS_H
#define CPP_DNS_H

#include <string>


int resolver_host(std::string hosts);

void receiv_and_print_info(unsigned char* buf);

#endif //CPP_DNS_H
