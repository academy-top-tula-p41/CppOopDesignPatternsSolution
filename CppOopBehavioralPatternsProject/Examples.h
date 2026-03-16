#pragma once
#include "ChainOfResponsibility.h"
using namespace ChainNamespace;

#include "CommandPattern.h"
#include "MediatorPattern.h"
#include "MementoPattern.h"
#include "StrategyPattern.h"
#include "StatePattern.h"

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

    static void MediatorExamples()
    {
        /*MediatorClient* client = new MediatorClient();
    client->ClientCode();*/

        Company* company = new Company();
        company->ClientCode();
    }

    static void MementoExamplesx()
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

    static void StrategyExamples()
    {
        /*StrategyClient* client = new StrategyClient();
    client->ClientCode();*/

        DynamicObject* obj = new DynamicObject();
        obj->AddProperty("name", "Bobby");
        obj->AddProperty("city", "Moscow");
        obj->AddProperty("aaa", "Bbbbb");

        for (int i{}; i < obj->Size(); i++)
            std::cout << obj->At(i).first << " " << obj->At(i).second << "\n";
        std::cout << "\n";

        obj->ChangeProperty("city", "Kazan");
        obj->ChangeProperty("company", "Yandex");
        obj->RemoveProperty("aaa");

        for (int i{}; i < obj->Size(); i++)
            std::cout << obj->At(i).first << " " << obj->At(i).second << "\n";
        std::cout << "\n";

        UniversalSerializer* serializer = new UniversalSerializer(new XmlSerializer());
        std::string xml = serializer->Serialize(obj);
        std::cout << xml << "\n";
        auto xmlObject = serializer->Deserialize(xml);
        for (int i{}; i < xmlObject->Size(); i++)
            std::cout << xmlObject->At(i).first << " " << xmlObject->At(i).second << "\n";
        std::cout << "\n";


        serializer->SetSerializer(new JsonSerializer());
        std::string json = serializer->Serialize(obj);
        std::cout << json << "\n";
        auto jsonObject = serializer->Deserialize(json);

        for (int i{}; i < jsonObject->Size(); i++)
            std::cout << jsonObject->At(i).first << " " << jsonObject->At(i).second << "\n";
        std::cout << "\n";
    }

    static void StateExamples()
    {
        /*StateClient* client = new StateClient();
    client->ClientCode();*/

        WaterClient* waterClient = new WaterClient();
        waterClient->Experiment();
    }

};

