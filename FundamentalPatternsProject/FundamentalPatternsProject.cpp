#include <iostream>

#include "ImmutableInterfacePattern.h"
#include "Examples.h"

int main()
{
    Point2D* point = new Point2D(10, 15);
    point->SetX(20);
    std::cout << point << "\n";

    IImmutablePoint2D* pointConst = new Point2D(20, 25);
    //pointConst->Set(50);
}
