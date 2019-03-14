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

using StructNotifier = std::function<void(const MyStruct&)>;

void setStruct(MyStruct testStruct, const StructNotifier& notifier)
{
    MyStruct context;
    context.file = testStruct.file;
    context.path = testStruct.path;
    notifier(context);
}

void printStructVal(MyStruct ctx)
{
    std::cout << "file is: " << ctx.file << "\n" << "path is: " << ctx.path << std::endl;
}

int main()
{
    MyStruct myStruct;
    myStruct.file = "file _01";
    myStruct.path = "path _02";

    const auto& cb_2 = std::bind(setStruct, std::placeholders::_1, std::placeholders::_2);
    const auto& handler = [&](MyStruct struct_02)  // 匿名函数捕捉实参
    {
        printStructVal(struct_02);
    };
    cb_2(myStruct, handler);  // 逻辑：绑定cb_2-> 声明lambda函数，捕获setStruct中notifier的MyStruct参数-> 使用MyStruct参数参数
}

