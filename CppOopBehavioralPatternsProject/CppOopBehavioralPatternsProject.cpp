#include <iostream>

#include "MementoPattern.h"

int main()
{
    srand(time(nullptr));

    /*MementoClient* client = new MementoClient();
    client->ClientCode();*/

    Player* player = new Player();
    PlayerHistory* history = new PlayerHistory();

    int rounds{ 5 };

    for (int i{}; i < rounds; i++)
    {
        player->PlayRound();
        std::cout << "Player play. State: " << player->State() << "\n";
        history->Push(player->Save());
    }

    history->History();

    player->Load(history->Pop());
    std::cout << "Player load game. State: " << player->State() << "\n";

    player->Load(history->Pop());
    std::cout << "Player load game. State: " << player->State() << "\n";

    player->Load(history->Pop());
    std::cout << "Player load game. State: " << player->State() << "\n";

    for (int i{}; i < rounds; i++)
    {
        player->PlayRound();
        std::cout << "Player play. State: " << player->State() << "\n";
        history->Push(player->Save());
    }

    history->History();
}
