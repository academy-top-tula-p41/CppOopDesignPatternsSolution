#include <iostream>

#include "PrototypePattern.h"
using namespace PtototypeNamespace;

int main()
{
    Prototype* v1 = new ValueObject();
    ((ValueObject*)v1)->Value() = 100;

    Prototype* v2 = v1->Clone();
    ((ValueObject*)v2)->Value() = 200;

    std::cout << ((ValueObject*)v1)->Value() << "\n";
    std::cout << ((ValueObject*)v2)->Value() << "\n";


    Prototype* r1 = new ReferenceObject(1);
    ((ReferenceObject*)r1)->Reference()[0] = 100;

    Prototype* r2 = r1->Clone();
    ((ReferenceObject*)r2)->Reference()[0] = 200;

    std::cout << ((ReferenceObject*)r1)->Reference()[0] << "\n";
    std::cout << ((ReferenceObject*)r2)->Reference()[0] << "\n";

    CopyObject c1;
    c1.Reference()[0] = 100;

    CopyObject c2;
    c2 = c1;
    c2.Reference()[0] = 200;

    std::cout << c1.Reference()[0] << "\n";
    std::cout << c2.Reference()[0] << "\n";
}
