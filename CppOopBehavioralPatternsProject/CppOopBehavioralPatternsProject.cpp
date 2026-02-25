#include <iostream>

#include "ChainOfResponsibility.h"
using namespace ChainNamespace;

int main()
{
    /*IHandler* handlerA = new ConcreteHandlerA();
    IHandler* handlerB = new ConcreteHandlerB();
    IHandler* handlerC = new ConcreteHandlerC();

    handlerA->SetNext(handlerB);
    handlerA->SetNext(handlerC);

    ChainClient* client = new ChainClient();
    client->ClientCode(handlerA);*/

    //PaymentHandler* payChain = new SberPaymentHandler();
    //payChain->Push(new TbankPaymentHandler());
    //payChain->Push(new WUPaymentHandler());

    //PayRequest* request = new PayRequest(1000);
    //payChain->PayHandler(request);
    //std::cout << "\n";

    ////request->SetPayCheck(PayType::TBank);
    //request->SetPayCheck(PayType::WesternUnion);
    //payChain->PayHandler(request);
    //std::cout << "\n";
}
