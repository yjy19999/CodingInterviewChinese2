#include <cstdlib>
#include <iostream>
using namespace std;

struct NullClass
{

};

struct NullClassWithConstructor
{
    NullClassWithConstructor(){}
    ~NullClassWithConstructor(){}
};

struct NullClassWithVirtual
{
    NullClassWithVirtual(){}
    ~NullClassWithVirtual(){}
    virtual void print(){}
};

int main()
{
    NullClass nullClass;
    cout<<sizeof(nullClass)<<endl;
    NullClassWithConstructor nClassWCons;
    cout<<sizeof(nClassWCons)<<endl;
    NullClassWithVirtual nClassVirtual;
    cout<<sizeof(nClassVirtual)<<endl;  // for 64bit machine, we get 8 bytes
}