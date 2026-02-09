#pragma once
#include "AdapterPattern.h"
using namespace AdapterNamespace;

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
};

