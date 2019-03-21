//
// Created by looperX on 2019-03-21.
//

#ifndef RECIPES_CALLLBACK_H
#define RECIPES_CALLLBACK_H

#include <iostream>
#include <memory>
#include <string>
#include <functional>
#include <map>

#include "smart_ptr/MySmartPtr.h"
#include "ThreadPool/ThreadPool.h"

using namespace std;

struct MyStruct
{
    std::string file;
    std::string path;
};

using MyStructPtr = std::shared_ptr<MyStruct>;
using StructNotifier = std::function<void(const MyStructPtr&)>;

void setStruct(MyStruct testStruct, const StructNotifier& notifier)
{
    MyStruct context;
    context.file = testStruct.file;
    context.path = testStruct.path;
    std::shared_ptr<MyStruct> ctxPtr = std::make_shared<MyStruct>(context);
    notifier(ctxPtr);
}

void printStructVal(MyStructPtr ctxPtr)
{
    std::cout << "file is: " << ctxPtr->file << "\n" << "path is: " << ctxPtr->path << std::endl;
}
//
//int main()
//{
//    MyStruct myStruct;
//    myStruct.file = "file _01";
//    myStruct.path = "path _02";
//
//    const auto& cb_2 = std::bind(setStruct, std::placeholders::_1, std::placeholders::_2);
//    const auto& handler = [&](MyStructPtr structPtr)  // 匿名函数捕捉实参
//    {
//        printStructVal(structPtr);
//    };
//    cb_2(myStruct, handler);  // 逻辑：声明cb_2，绑定setStruct-> 声明lambda函数，捕获setStruct中notifier的MyStructPtr参数->使用MyStructPtr参数
//}



#endif //RECIPES_CALLLBACK_H
