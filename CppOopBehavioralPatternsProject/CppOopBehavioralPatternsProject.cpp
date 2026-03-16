#include <iostream>

#include "ObserverPattern.h"

int main()
{
    std::srand(time(nullptr));

    ObserverClient* client = new ObserverClient();
    client->ClientCode();
}
