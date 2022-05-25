#include <iostream>

#include "injector/injector.hpp"

class Base
{
public:
    virtual void print() = 0;

    virtual ~Base() = default;
};

class Derived : public Base
{
public:
    void print() override
    {
        std::cout << 20;
    }
};

class Service
{
public:
    Service(std::shared_ptr<Base> ptr)
        : m_Ptr(ptr)
    {
    }

    void foo()
    {
        m_Ptr->print();
    }


private:
    std::shared_ptr<Base> m_Ptr;
};

int main()
{
    injector::Injector inj;

    inj.add_singleton<Base, Derived>();
//    inj.add_singleton<Service>();

    try {
        auto s = inj.get<Service>();
        s->foo();
    } catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
}