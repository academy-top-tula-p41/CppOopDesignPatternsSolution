#pragma once
#include "DelegationPattern.h"

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
};

