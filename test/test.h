//
// Created by looperX on 2019-02-14.
// static lib: /usr/local/lib/libglog.a
// headers: /usr/local/include/glog/
// g++ glog_test2.cpp -lglog -lgflags -lpthread -o glog_test



#ifndef RECIPES_TEST_H
#define RECIPES_TEST_H

#include <glog/logging.h>

int main(int argc,char* argv[])
{
    google::InitGoogleLogging(argv[0]);  // 初始化 glog
    google::ParseCommandLineFlags(&argc, &argv, true);  // 初始化 gflags
    LOG(INFO) << "Hello, GOOGLE!";  // INFO 级别的日志
    LOG(ERROR) << "ERROR, GOOGLE!";  // ERROR 级别的日志
    return 0;
}

#endif //RECIPES_TEST_H

