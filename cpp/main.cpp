#include <fstream>
#include <string>
#include <iostream>
#include "dns.h"

namespace fs = std::filesystem;

int main() {

    std::ifstream file("../dns.txt");
    std::string lineContent;

    resolver_host("facebook.com");

    return 0;

    while(file >> lineContent) {
        std::cout << lineContent << std::endl;
    }

    return 0;
}

