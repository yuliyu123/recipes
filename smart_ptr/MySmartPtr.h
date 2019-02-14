//
// Created by loohan on 2019/2/14.
//

#ifndef RECIPES_MYSMARTPTR_H
#define RECIPES_MYSMARTPTR_H

#include <iostream>

template <typename T> class SmartPtr;

template <typename T>
class RefPtr // 辅助ptr
{
private:
    friend class SmartPtr<T>; // 该class为SmartPtr专用， 所有成员均为private
    RefPtr(T* ptr) : ptr_(ptr) , count(1) {} // 传入指针，初始化ptr_, count为1
    ~RefPtr()
    {
        delete ptr_;
    }

    int count;
    T* ptr_;
};

template <typename T>
class SmartPtr
{
public:
    SmartPtr()
    {
        std::cout << "smart_ptr no argument" << std::endl;
    }

    SmartPtr(T* p) : refPtr_(new RefPtr<T>(p))
    {
        std::cout << "smart_ptr has one argument" << std::endl;
    }

    SmartPtr(const SmartPtr<T>& rhs)
        : refPtr_(rhs.refPtr_)
    {
        std::cout << "enter SmartPtr() copy constructor" << std::endl;
        ++refPtr_->count;
    }

    SmartPtr& operator=(const SmartPtr<T>& rhs)
    {
        std::cout << "enter SmartPtr() operator=" << std::endl;
        std::cout << "refPtr_->count " << rhs.refPtr_->count << std::endl;
        ++rhs.refPtr_->count; // 引用计数+1
        std::cout << "refPtr_->count " << rhs.refPtr_->count << std::endl;
        if (--refPtr_->count == 0) // 右值赋值给左值，如果左值的计数为0（没有引用该对象的智能指针，则删除该指针）
        {
            delete refPtr_;
        }
        refPtr_ = rhs.refPtr_;  // 右值赋值给左值
        return *this;
    }

    int use_count()
    {
        return refPtr_->count;
    }

    T* operator->()
    {
        std::cout << "smartPtr:: operator-> " << std::endl;
        return refPtr_->ptr_;
    }

    T& operator*()
    {
        std::cout << "smartPtr:: operator*() " << std::endl;
        return *(refPtr_->ptr_);
    }

    ~SmartPtr()
    {
        std::cout << "enter SmartPtr()::~SmartPtr()" << std::endl;
        if (--refPtr_->count == 0)
        {
            delete refPtr_;
        }
        else
        {
            std::cout << "refPtr_.count has: " << refPtr_->count <<  std::endl;
        }
    }

private:
    RefPtr<T>* refPtr_;
};

#endif //RECIPES_MYSMARTPTR_H



