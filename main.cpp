#include <iostream>
#include <memory>

#include "smart_ptr/MySmartPtr.h"

struct MyClass
{
public:
    int x = 1;
    float y = 2.0;
};

int main()
{
    MyClass* class_01 = new MyClass;
    SmartPtr<MyClass> smartPtr_04(class_01);
    std::cout << "myclass->x: " << smartPtr_04->x << std::endl;
    std::cout << "myclass->y: " << smartPtr_04->y << std::endl;

    int* p = new int(100);
    {
        SmartPtr<int> smartPtr_01(p);
        std::cout << smartPtr_01.use_count() << std::endl;
        {
            SmartPtr<int> smartPtr_02(smartPtr_01);
            std::cout << smartPtr_02.use_count() << std::endl;
            {
                SmartPtr<int> smartPtr_03(smartPtr_02);
                smartPtr_03 = smartPtr_01;
                std::cout << smartPtr_03.use_count() << std::endl;
            }
        }
        std::cout << smartPtr_01.use_count() << std::endl;
        std::cout << *p << std::endl;
    }

    // count 为0, p原来指向的内存块上面的值被delete掉，为任意值
    std::cout << *p << std::endl;
    return 0;
}
