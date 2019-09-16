//
// Created by looperX on 2019-06-24.
//
#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <map>
#include <map>
#include <algorithm>
#include <utility>

#include "timer/timercpp.h"

using namespace std;

std::mutex m;
std::condition_variable cv;
std::string data;
bool ready = false;
bool processed = false;

typedef map<string, string> ConnMap;
typedef pair<string, string> ConnPair;

int main()
{
    ConnMap connMap;
//    connMap["one"] = "one";
    connMap["two"] = "two";
    connMap["three"] = "three";

    string name = "two";
    std::find_if(connMap.begin(),connMap.end(), [&](ConnPair pair)
    {
        if (pair.first == name)
        {
            std::cout << "found" << std::endl;
            return connMap.erase(name);
        }
    });

    std::cout << connMap.size() << std::endl;
    std::cout << connMap["one"] << std::endl;
}

