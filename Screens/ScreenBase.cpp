#include "ScreenBase.h"






/*
#include <iostream>
#include <vector>
#include <memory>

// Base class
class BaseClass {
public:
    virtual void someMethod() const {
        std::cout << "BaseClass::someMethod()" << std::endl;
    }

    virtual ~BaseClass() {}
};

// Derived class 1
class DerivedClass1 : public BaseClass {
public:
    void someMethod() const override {
        std::cout << "DerivedClass1::someMethod()" << std::endl;
    }
};

// Derived class 2
class DerivedClass2 : public BaseClass {
public:
    void someMethod() const override {
        std::cout << "DerivedClass2::someMethod()" << std::endl;
    }
};

int main() {
    // Create a vector of smart pointers to the base class
    std::vector<std::unique_ptr<BaseClass>> myClassList;

    // Add instances of derived classes to the list
    myClassList.push_back(std::make_unique<DerivedClass1>());
    myClassList.push_back(std::make_unique<DerivedClass2>());

    // Call a method on each element of the list
    for (const auto& item : myClassList) {
        item->someMethod();
    }

    return 0;
}

*/
