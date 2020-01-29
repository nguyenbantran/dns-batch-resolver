#include <fstream>
#include <string>
#include <iostream>
#include "dns.h"
#include "kqueue.h"

namespace fs = std::filesystem;

int main() {

    std::ifstream file("../dns.txt");
    std::string lineContent;

    dns_create_kqueue();


    int count = 0;

    while(file >> lineContent) {
        std::cout << lineContent << std::endl;
        resolver_host(lineContent);
        count++;
        if (count == 5) {
            break;
        }
    }

    process_all_event();


    return 0;
}

