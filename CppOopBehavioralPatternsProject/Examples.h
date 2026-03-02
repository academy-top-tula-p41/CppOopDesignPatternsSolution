#pragma once
#include "ChainOfResponsibility.h"
using namespace ChainNamespace;

#include "CommandPattern.h"

class Examples
{
public:
	static void ChainExamples()
	{
        IHandler* handlerA = new ConcreteHandlerA();
        IHandler* handlerB = new ConcreteHandlerB();
        IHandler* handlerC = new ConcreteHandlerC();

        handlerA->SetNext(handlerB);
        handlerA->SetNext(handlerC);

        ChainClient* client = new ChainClient();
        client->ClientCode(handlerA);

        PaymentHandler* payChain = new SberPaymentHandler();
        payChain->Push(new TbankPaymentHandler());
        payChain->Push(new WUPaymentHandler());

        PayRequest* request = new PayRequest(1000);
        payChain->PayHandler(request);
        std::cout << "\n";

        //request->SetPayCheck(PayType::TBank);
        request->SetPayCheck(PayType::WesternUnion);
        payChain->PayHandler(request);
        std::cout << "\n";
	}

    static void CommandExamples()
    {
        /*CommandClient* client = new CommandClient();
    client->ClientCode();*/

        Television* tv = new Television();
        Controller* pult = new Controller(
            new PowerOnTvCommand(tv),
            new PowerOffTvCommand(tv),
            new SoundUpTvCommand(tv),
            new SoundDownTvCommand(tv));

        pult->ButtonPower();
        pult->ButtonSoundPlus();
        pult->ButtonSoundPlus();
        pult->ButtonSoundPlus();
        pult->ButtonSoundMinus();
        //pult->ButtonPower();

        ControllerMobileApp* app = new ControllerMobileApp(
            new PowerOnTvCommand(tv),
            new PowerOffTvCommand(tv),
            new SoundUpTvCommand(tv),
            new SoundDownTvCommand(tv));

        //app->PowerOnMenuItem();
        app->SoundPlusMenuItem();
        app->PowerOffMenuItem();
    }

};

