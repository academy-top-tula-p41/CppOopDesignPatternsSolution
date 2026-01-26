#pragma once
#include "DelegationPattern.h"
#include "ImmutableInterfacePattern.h"

void VendingSession(IVending* vending)
{
    vending->Select();
    vending->Payment();
    vending->Receipt();
}

class Examples
{
public:
	static void DelegationPatternExample()
	{
        UniversalVending* vending = new UniversalVending();

        //vending->ToBeverage();
        vending->SetVending(new BeverageVending());
        VendingSession(vending);

        //vending->ToCigarette();
        vending->SetVending(new CigaretteVending());
        VendingSession(vending);

        vending->SetVending(new BookVending());
        VendingSession(vending);
	}

    static void ImmutableInterfaceExample()
    {
        Point2D* point = new Point2D(10, 15);
        point->SetX(20);
        std::cout << point << "\n";

        IImmutablePoint2D* pointConst = new Point2D(20, 25);
        //Point2D*pointConst->SetX(50);
    }
};

