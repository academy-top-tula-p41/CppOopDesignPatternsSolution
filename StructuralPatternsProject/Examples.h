#define _CRT_SECURE_NO_WARNINGS

#pragma once
#include "AdapterPattern.h"
using namespace AdapterNamespace;

#include "BridgePattern.h"
using namespace BridgeNamespace;

#include "CompositePattern.h"
using namespace CompositeNamespace;

#include "DecoratorPattern.h"
using namespace DecoratorNamespace;

#include "FacadePattern.h"
using namespace FacadeNamespace;

#include "ProxyPattern.h"
using namespace ProxyNamespace;

class Examples
{
public:
	static void AdapterExamples()
	{
        Client* client = new Client();
        client->ClientCode(new ConcreteClassA(100));
        client->ClientCode(new ConcreteClassB(200));

        ServiceAdapter* adapter = new ServiceAdapter(new AdapterNamespace::Service());
        adapter->SetData(300);
        client->ClientCode(adapter);


        ArchClient* archClient = new ArchClient();
        archClient->ClientCode(new RarArchivator(), "Hello world");
        archClient->ClientCode(new ArjAdapter(new ArjArc()), "Good by world");
	}

    static void BridgeExamples()
    {
        /*BridgeClient* client = new BridgeClient();

    Implementation* implementation = new ConcreteImplementationA();
    Abstraction* abstraction = new Abstraction(implementation);

    client->ClentCode(abstraction);*/

        srand(time(nullptr));

        //Logger* logger = new SimpleThreadLogger(new ConsoleLoggerType());
        //Logger* logger = new SimpleThreadLogger(new FileLoggerType("system_logs.log"));

        Logger* logger = new ParallelThreadLogger(new ConsoleLoggerType());

        System* system = new System(logger);
        system->Work();
    }

    static void CompositeExamples()
    {
        /*CompositeClient* client = new CompositeClient();
        client->ClientCode();*/

        Army* army = new Army();
        army->CreateArmy();
        std::cout << army->GetArmy()->Info(0) << "\n";
    }
    
    static void DecoratorExamples()
    {
        /*DecoratorClient* client = new DecoratorClient();

        IComponent* component = new ConcreteComponent();
        client->ClientCode(component);

        component = new ConcreteDecoratorA(component);
        client->ClientCode(component);

        component = new ConcreteDecoratorB(component);
        client->ClientCode(component);

        component = new ConcreteDecoratorA(component);
        client->ClientCode(component);*/

        MessageClient* client = new MessageClient();

        IMessage* message = new MessanderMessage();
        message->From() = "@Bobby";
        message->To() = "@Sammy";
        message->Text() = "Hello world!";

        client->SendMessage(message);
        std::cout << "\n";

        message = new FileMessage(message, "photo.jpg");
        client->SendMessage(message);
        std::cout << "\n";

        message = new ContactMessage(message, "Leo: 8 (999) 123-45-67");
        client->SendMessage(message);
        std::cout << "\n";
    }

    static void FacadeExample()
    {
        FacadeClient* client = new FacadeClient();
        client->ClientCode(new Facade());
    }

    static void ProxyExample()
    {
        ProxyClient* client = new ProxyClient();
        //client->ClientCode(new Service());
        client->ClientCode(new Proxy(new ProxyNamespace::Service()));
    }
};

