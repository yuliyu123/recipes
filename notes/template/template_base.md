全特化；
template <> // 无模板参数, 类特化
class dog
{
    void play(const int hours, const int nums); // const int作为模板参数编译期处理
}

template <> // 函数特化
bool max(const int lhs, const int rhs)
{
    return lhs > rhs ? lhs : rhs;
}

偏特化：
template <typename T>
class dog
{
    void play(const int hours, T nums); // 个别参数特化，作为编译器处理const int hours
};

reference:
https://cloud.tencent.com/developer/article/1347877

