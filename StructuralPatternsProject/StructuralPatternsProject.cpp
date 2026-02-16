#include <iostream>

#include "ProxyPattern.h"

int main()
{
	ProxyClient* client = new ProxyClient();
	//client->ClientCode(new Service());
	client->ClientCode(new Proxy(new Service()));
}