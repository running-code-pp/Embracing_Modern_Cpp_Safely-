
#include <iostream>
#include <type_traits>

/*
  假定有变量x
  decltype(x) 和 decltype((x)) 不一致的问题
  数解释为变量；后者则将其解释为表达式。

  c++中的官方定义:
  如果x是一个变量名或者直接访问成员obj.x，那么推导结果和 x类型一致
  如果x是一个表达式,而且这个表达式代表的是一个左值，那么推导类型为x的引用类型
  如果x是一个将亡值(xvalue) 那么推导类型为x的右值引用
  如果x是一个临时值(prvalue，比如字面量、函数返回的临时对象、算术表达式结果)，那么推导类型就是x普通类型
*/

int main()
{
    int x = 42;

    // 检查 decltype(x) 和 decltype((x)) 的类型是否相同
    std::cout << std::boolalpha;
    std::cout << "decltype(x) == int?           "
              << std::is_same_v<decltype(x), int> << '\n';

    std::cout << "decltype((x)) == int?         "
              << std::is_same_v<decltype((x)), int> << '\n';

    std::cout << "decltype((x)) == int&?        "
              << std::is_same_v<decltype((x)), int &> << '\n';

    // 进一步验证：能否对 decltype((x)) 类型赋值？
    decltype((x)) ref = x;                               // 等价于 int& ref = x;
    ref = 100;                                           // 修改 x
    std::cout << "x after modifying ref: " << x << '\n'; // 输出 100

    return 0;
}

/*
decltype(x) == int?           true
decltype((x)) == int?         false
decltype((x)) == int&?        true
x after modifying ref: 100
root@iv-yea3ni8sg05i3z5a7a5s:~/code/cpp/Embr
*/