#include <iostream>
#include <stdexcept>
#include <vector>

class GoodMoveable
{
public:
    GoodMoveable(const std::string &data) : bigData_(data) {}
    GoodMoveable(const GoodMoveable &other) : bigData_(other.bigData_) {}
    GoodMoveable(GoodMoveable &&other) noexcept : bigData_(std::move(other.bigData_)) {}

    std::string bigData_;
};

class BadMoveable
{
public:
    BadMoveable(const std::string &data) : bigData_(data) {}
    BadMoveable(const BadMoveable &other) : bigData_(other.bigData_) {}
    BadMoveable(BadMoveable &&other) : bigData_(std::move(other.bigData_)) {}

    std::string bigData_;
};

void func(std::vector<int> &&initData)
{
    std::cout << "address of initData:" << initData.data() << std::endl;
    std::vector<int> data1(initData);
    std::cout << "address of data1:" << data1.data() << std::endl;
    std::vector<int> data2(std::move(initData));
    std::cout << "address of data2:" << data2.data() << std::endl;
}

int main()
{
    // TEST NOEXCEPT & MOVE
    {
        std::cout << "############test move with noexcept declare############" << std::endl;
        std::vector<GoodMoveable> vec1;
        vec1.reserve(2);
        std::cout << "capacity of vec1:" << vec1.capacity() << std::endl;

        GoodMoveable g1(" this is a long string to avoid SSO, yes !");
        GoodMoveable g2("another very long string to avoid SSO, absolutely!");
        std::cout << "adress of g1.bigData_:" << (void *)g1.bigData_.data() << std::endl;
        std::cout << "adress of g2.bigData_:" << (void *)g2.bigData_.data() << std::endl;

        vec1.push_back(std::move(g1));
        std::cout << "capacity of vec1:" << vec1.capacity() << std::endl;

        vec1.push_back(std::move(g2));
        std::cout << "capacity of vec1:" << vec1.capacity() << std::endl;

        std::cout << "adress of vec1[0].bigData_:" << (void *)vec1[0].bigData_.data() << std::endl;
        std::cout << "adress of vec1[1].bigData_:" << (void *)vec1[1].bigData_.data() << std::endl;
        // 扩容
        vec1.reserve(3);
        std::cout << "capacity of vec1:" << vec1.capacity() << std::endl;

        std::cout << "adress of vec1[0].bigData_:" << (void *)vec1[0].bigData_.data() << std::endl;
        std::cout << "adress of vec1[1].bigData_:" << (void *)vec1[1].bigData_.data() << std::endl;

        std::cout << std::endl
                  << "############test move without noexcept declare############" << std::endl;
        std::vector<BadMoveable> vec2;
        vec2.reserve(2);
        std::cout << "capacity of vec2:" << vec2.capacity() << std::endl;

        BadMoveable b1(" this is a long string to avoid SSO, yes !");
        BadMoveable b2("another very long string to avoid SSO, absolutely!");
        std::cout << "adress of b1.bigData_:" << (void *)b1.bigData_.data() << std::endl;
        std::cout << "adress of b2.bigData_:" << (void *)b2.bigData_.data() << std::endl;

        vec2.push_back(std::move(b1));
        std::cout << "capacity of vec2:" << vec2.capacity() << std::endl;
        vec2.push_back(std::move(b2));
        std::cout << "capacity of vec2:" << vec2.capacity() << std::endl;
        std::cout << "adress of vec2[0].bigData_:" << (void *)vec2[0].bigData_.data() << std::endl;
        std::cout << "adress of vec2[1].bigData_:" << (void *)vec2[1].bigData_.data() << std::endl;
        // 扩容
        vec2.reserve(3);
        std::cout << "capacity of vec2:" << vec2.capacity() << std::endl;
        std::cout << "adress of vec2[0].bigData_:" << (void *)vec2[0].bigData_.data() << std::endl;
        std::cout << "adress of vec2[1].bigData_:" << (void *)vec2[1].bigData_.data() << std::endl;
    }

    // test rvalue reference with name
    {
        std::cout << std::endl
                  << "############test rvalue reference with name############" << std::endl;
        std::vector<int> vec{1, 2, 3};
        std::cout << "addressof vec:" << vec.data() << std::endl;
        func(std::move(vec));
    }
    return 0;
}

/*

############test move with noexcept declare############
capacity of vec1:2
adress of g1.bigData_:0x559a49026350
adress of g2.bigData_:0x559a49026390
capacity of vec1:2
capacity of vec1:2
adress of vec1[0].bigData_:0x559a49026350
adress of vec1[1].bigData_:0x559a49026390
capacity of vec1:3
adress of vec1[0].bigData_:0x559a49026350
adress of vec1[1].bigData_:0x559a49026390

############test move without noexcept declare############
capacity of vec2:2
adress of b1.bigData_:0x559a49026440
adress of b2.bigData_:0x559a49026480
capacity of vec2:2
capacity of vec2:2
adress of vec2[0].bigData_:0x559a49026440
adress of vec2[1].bigData_:0x559a49026480
capacity of vec2:3
adress of vec2[0].bigData_:0x559a49026310
adress of vec2[1].bigData_:0x559a49026530

*/
