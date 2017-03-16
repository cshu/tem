#include <iostream>

int main()
{
struct Z {
    virtual void foo () { std::cout << "Z::foo" << std::endl; }
};

struct A : public Z{
    void foo () { std::cout << "A::foo" << std::endl; }
};

struct B : public A {
    void foo () { std::cout << "B::foo" << std::endl; }
};

B b;
b.foo();
A *a = &b;
a->foo();//NOTE this prints B::foo! you might think this is shadowing, but it's not! virtualness of a function is propagated implicitly!
}
