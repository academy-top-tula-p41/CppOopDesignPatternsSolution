#include <iostream>

#include "CommandPattern.h"

int main()
{
    CommandClient* client = new CommandClient();
    client->ClientCode();
}
