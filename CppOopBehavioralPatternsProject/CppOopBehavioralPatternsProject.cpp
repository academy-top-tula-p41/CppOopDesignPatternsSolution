#include <iostream>

#include "ChainOfResponsibility.h"
using namespace ChainNamespace;

int main()
{
    IHandler* handlerA = new ConcreteHandlerA();
    IHandler* handlerB = new ConcreteHandlerB();
    IHandler* handlerC = new ConcreteHandlerC();

    handlerA->SetNext(handlerB)
            ->SetNext(handlerC);

    ChainClient* client = new ChainClient();
    client->ClientCode(handlerB);
}
