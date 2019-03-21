//
// Created by looperX on 2019-01-25.
//

#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <mutex>
#include "thread_01.h"

class StringPtr
{
public:
    StringPtr() = default;
    StringPtr(const char* initvalue)
    {
        std::cout << sizeof(initvalue) << std::endl;
        data_ = new char[strlen(initvalue) + 1];
        std::cout << sizeof(data_) << std::endl;
        std::cout << strlen(data_) << std::endl;
        strcpy(data_, initvalue);
        std::cout << strlen(data_) << std::endl;
    }

    StringPtr(const StringPtr& rhs)
    {
        std::cout << "here invoke copy contructor" << std::endl;
    }

    StringPtr& operator=(const StringPtr& rhs)
    {
        std::cout << "here invoke operator = " << std::endl;
        return *this;
    }

private:
    char* data_;
};

class MyClass
{
public:
    MyClass() = default;

    void sayHello()
    {
        std::cout << "hello my class" << std::endl;
    }

    ~MyClass()
    {
        std::cout << "bye my class" << std::endl;
    }
};

std::shared_ptr<MyClass> myClassPtr = std::make_shared<MyClass>();
std::shared_ptr<MyClass> myClassPtr_03 = std::make_shared<MyClass>();

void testMyClass()
{
    myClassPtr->sayHello();
}

static void staticTestMyClass()
{
    myClassPtr->sayHello();
}

int i = 0;
//std::mutex mtx;

void threadFunc(std::shared_ptr<MyClass> pl) // use count + 1
{
    // 声明为局部静态变量，位于去全局静态区，离开函数作用域后销毁。静态区变量只有一个， 达到互斥锁效果
    static std::mutex mtx;
    std::lock_guard<std::mutex> lk(mtx); // 管理mutex
    std::shared_ptr<MyClass> p2 = pl; // use count + 1
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "MyClass's use count: " << p2.use_count() << std::endl;
    {
        ++i;
        std::cout << "test threadFunc(), i is " << i << std::endl;
//        std::cout << "MyClass's use count: " << p2.use_count() << std::endl;
    }
}

//int main()
//{
//    std::shared_ptr<MyClass> myClassPtr_02 = std::make_shared<MyClass>(); // use count = 1
//    std::cout << myClassPtr_02.use_count() << std::endl;
//    myClassPtr_02->sayHello();
////    myClassPtr_02.get();
//    myClassPtr_02->sayHello();
//
//    // 实例化了三个智能指针指向MyClass, 加上传参的一个以及最初实例化的一个共5个
//    std::thread t1(threadFunc, myClassPtr_02), t2(threadFunc, myClassPtr_02), t3(threadFunc, myClassPtr_02);
////    myClassPtr_02.reset(); // 释放所有权， use count - 1
//    t1.join(); // 等待线程执行完threadFunc， 然后t1的shared_ptr释放， use count - 1
//    t2.join(); // 同上
//    t3.join(); // 同上
//
//    std::cout << "MyClass's use count: " << myClassPtr_02.use_count() << std::endl; // use count = 1
//    return 0;
//}

/* 多线程、锁和shared_ptr的作用域名
 * result:
1
hello my class
hello my class
MyClass's use count: 5
test threadFunc(), i is 1
MyClass's use count: 4
test threadFunc(), i is 2
MyClass's use count: 3
test threadFunc(), i is 3
bye my class
bye my class
bye my class
 *
 * */
