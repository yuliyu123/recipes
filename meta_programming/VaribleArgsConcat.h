//
// Created by looperX on 2019-05-31.
//
// https://cloud.tencent.com/developer/article/1347059

#ifndef RECIPES_VARIBLEARGSCONCAT_H
#define RECIPES_VARIBLEARGSCONCAT_H

#include <iostream>
#include <memory>
#include <string>
#include <ostream>
#include <sstream>
#include <functional>
#include <map>
#include <stdio.h>
#include <stdio.h>
#include <string>

#include "boost/optional.hpp"
#include "smart_ptr/MySmartPtr.h"
//#include "ThreadPool/ThreadPool.h"

using namespace std;
boost::optional<std::string> feedback;

template <typename T = string, typename Arg>
auto func(Arg arg) -> decltype(arg)
{
    return arg;
}

template<class F, class... Args> void expand(const F& f, Args&&...args)
{
    initializer_list<int>{(f(std::forward<Args>(args)),0)...};
}

template<typename... Args>
auto generalPrint(Args&&... args)
{
    std::ostringstream oss;
    auto func = [&](std::string input)
    {
        oss << input;
    };
    // 初始化列表表达式，因为使用逗号表达式，这里赋值为0，即创建为一个全为0的list
    // 这里的执行顺序：先执行std::forward<Args>(args) -> 到逗号表达式取逗号后0，依次类推执行完整个args
    initializer_list<int>{(func(std::forward<Args>(args)),0)...};
    feedback = oss.str();
    return feedback;
}

template<typename... Args>
auto generalPrint_02(Args&&... args)
{
    std::ostringstream oss;
    // 初始化列表表达式，因为使用逗号表达式，这里赋值为0，即创建为一个全为0的list
    // 这里的执行顺序：先执行std::forward<Args>(args) -> 到逗号表达式取逗号后0，依次类推执行完整个args
    initializer_list<int>{([&]{
        oss << args;
    }(),0)...};
    feedback = oss.str();
    return feedback;
}

int main()
{
//    generalPrint("hello, ", " i'm ", "an error, number is ", std::to_string(5));
    generalPrint_02("hello, ", " i'm ", "an error, number is ", 500);
    cout << "output: " + feedback.get() << endl;

    int a = 1, b = 2, c = 3, d = 4;
    d = (a = b, c);  // 逗号表达式，先执行a = b, 再是取逗号后面的值即c, 再赋值给a
    cout << d << endl;
}


#endif //RECIPES_VARIBLEARGSCONCAT_H
