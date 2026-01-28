#include <iostream>

#include "AbstractFactoryPattern.h"
using namespace AbstractFactoryNamespace;

int main()
{
    /*AbstractFactoryNamespace::Client* client
        = new AbstractFactoryNamespace::Client();
    
    client->ClientCode(new Factory1());
    client->ClientCode(new Factory2());*/

    Army* romeArmy = new Army(new RomeArmyCreator(), 5, 7, 6, 4);
    Army* carthagenArmy = new Army(new CarthagenArmyCreator(), 6, 5, 7, 4);

    std::cout << romeArmy->Info();
    std::cout << carthagenArmy->Info();
}
