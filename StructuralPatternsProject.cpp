#include <iostream>

#include "AdapterPattern.h"
using namespace AdapterNamespace;

int main()
{
    Client* client = new Client();
    client->ClientCode(new ConcreteClassA(100));
    client->ClientCode(new ConcreteClassB(200));
}
