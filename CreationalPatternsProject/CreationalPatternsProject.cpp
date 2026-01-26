#include <iostream>

#include "FactoryMethodPattern.h"
using namespace FactoryMethodNamespace;

int main()
{
    /*Client* client = new Client();
    client->ClientCode(new FactoryA());
    client->ClientCode(new FactoryB());

    client->ClientCode(new FactoryC());*/

    Army* army = new Army();
    army->AddCreator(new InfantryCreator());
    army->AddCreator(new ArcherCreator());
    army->AddCreator(new CavalryCreator());
    army->ArmyCreate(5);
    army->ArmyInfo();
}
