//
// Created by looperX on 2019-03-22.
//

#ifndef RECIPES_DEMAND_H
#define RECIPES_DEMAND_H

#include <iostream>
#include <memory>
#include <string>
#include <functional>
#include <map>

#include "smart_ptr/MySmartPtr.h"
#include "ThreadPool/ThreadPool.h"

/*
 * 菱形继承问题，采用虚继承使得基类只会生成一个实例对象
 * */

class Base
{
public:
    void printme()
    {
        cout << "i'm Base class" << endl;
    }
};
using namespace std;

class Derived_01 : virtual public Base
{
};

class Derived_02 : virtual public Base
{
};

class Derived_04 : public Derived_01 , public Derived_02
{
};


int main()
{
    Derived_04 d4;
    std::cout << sizeof(d4) << std::endl;
    d4.printme();
}


#endif //RECIPES_DEMAND_H
