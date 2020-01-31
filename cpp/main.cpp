#include <fstream>
#include <string>
#include <iostream>
#include <sys/time.h>
#include "dns.h"
#include "kqueue.h"

#include <chrono>
#include <thread>
#include <map>
#include <vector>

namespace fs = std::filesystem;

static long int get_current_time() {
    struct timeval tp;
    gettimeofday(&tp, NULL);
    long int ms = tp.tv_sec * 1000 + tp.tv_usec / 1000;
    return ms;
}

void foo() {
    std::cout << "begin event processing thread ..." << std::endl;
    process_all_event();
}

static int remain_to_process(std::map<std::string, int> map) {
    int count2 = 0;
    int count1 = 0;
    std::map<std::string, int>::iterator it = map.begin();
    while(it != map.end()) {
        if (it->second == 2) {
            count2++;
        }
        if (it->second == 1) {
            count1++;
        }
        it++;
    }

    if (count2 < 1000 && (count1 + count2 > 0)) {
        return 1;
    }

    return 0;
}

extern std::map<std::string, int> mapOfWords;

int main() {

    long int begin = get_current_time();

    std::ifstream file("../dns.txt");
    std::string lineContent;

    dns_create_kqueue();

    while(file >> lineContent) {
        // convert string to back to lower case
        std::for_each(lineContent.begin(), lineContent.end(), [](char & c) {
            c = ::tolower(c);
        });
        mapOfWords.insert(std::make_pair(lineContent, 1));
    }

    std::thread th1(foo);

    while (remain_to_process(mapOfWords)) {
        // Iterate through all elements in std::map
        std::map<std::string, int>::iterator it = mapOfWords.begin();
        int count = 0;
        std::vector<std::string> vec1;
        while(it != mapOfWords.end())
        {
            if (it->second == 1 || it->second == 2) {
                count++;
                if (count < 200) {
                    vec1.push_back(it->first);
                } else {
                    break;
                }

            }
            it++;

        }
        for(int i = 0; i < vec1.size(); i++) {
            resolver_host(vec1[i]);
            mapOfWords[vec1[i]] = 2;
        }

        std::this_thread::sleep_for(std::chrono::nanoseconds(100 * 1000 * 1000));
    }


    std::cout << mapOfWords.size() << std::endl;


    long int end = get_current_time();

    std::cout << "Total running time: " <<(end - begin) << " ms" << std::endl;

    return 0;
}

