#include <iostream>
#include <vector>
#include "smartPtr.h"

class Base
{
public:
    virtual ~Base()
    {
        std::cout << "class Base" << std::endl;
    }
};

class Derived1 : public Base
{
public:
    ~Derived1()
    {
        std::cout << "class Derived1" << std::endl;
    }
};

class Derived2 : public Base
{
public:
    ~Derived2()
    {
        std::cout << "class Derived2" << std::endl;
    }
};

int main()
{
    smartPtr<int> foo(new int(123));
    std::cout << *foo << std::endl;

    smartPtr<int> *hpa(new smartPtr<int>(new int(42)));
    smartPtr<int> *hpb = new smartPtr<int>(*hpa);
    smartPtr<int>  hpd = *hpa;

    std::cout << hpa->getPtrPointer() << std::endl;
    std::cout << hpa->getPtrCounter() << " " << hpb->getPtrCounter() << " "<< hpd.getPtrCounter() << std::endl;
    delete hpa;
    std::cout << hpd.getPtrCounter() << std::endl;
    delete hpb;
    std::cout << hpd.getPtrCounter() << std::endl;

    std::vector<smartPtr<Base> > obj;
    obj.push_back(new Derived1);
    obj.push_back(new Derived2);

    std::vector<smartPtr<Base> > obj2;
    obj2.push_back(obj[0]);

    if (obj2[0])
        std::cout << "Cast Derived1 to Base successd" << std::endl;
    else
        std::cout << "Cast Derived1 to Base failed" << std::endl;

    smartPtr<Derived1> d1 = new Derived1;
    smartPtr<Base> b = d1;
    smartPtr<Derived2> d2 = b.Cast<Derived2>();

    if (d2)
        std::cout << "Cast Derived1 to Derived2 successd" << std::endl;
    else
        std::cout << "Cast Derived1 to Derived2 failed" << std::endl;

    return 0;
}