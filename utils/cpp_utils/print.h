//
// Created by looperX on 2019-03-21.
//

#ifndef RECIPES_PRINT_VAR_H
#define RECIPES_PRINT_VAR_H

#include <iostream>
#include <string>
#include <functional>

using namespace std;


// print single var
template <typename T>
void print_var(T& var)
{
    std::cout << var << std::endl;
}

/*
 * print all elements of any kind of container
 * */
template <typename Type, typename ...Args>
void print_container(Type type, Args... args)
{

}


#endif //RECIPES_PRINT_VAR_H
