#define _CRT_SECURE_NO_WARNINGS

#pragma once
#include "AdapterPattern.h"
using namespace AdapterNamespace;

#include "BridgePattern.h"
using namespace BridgeNamespace;

class Examples
{
public:
	static void AdapterExamples()
	{
        Client* client = new Client();
        client->ClientCode(new ConcreteClassA(100));
        client->ClientCode(new ConcreteClassB(200));

        ServiceAdapter* adapter = new ServiceAdapter(new Service());
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
};

