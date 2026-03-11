#include <iostream>

#include "StrategyPattern.h"

int main()
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
    std::cout << serializer->Serialize(obj);
    std::cout << "\n";

    serializer->SetSerializer(new JsonSerializer());
    std::string json = serializer->Serialize(obj);
    std::cout << json << "\n";
    auto jsonObject = serializer->Deserialize(json);

    for (int i{}; i < jsonObject->Size(); i++)
        std::cout << jsonObject->At(i).first << " " << jsonObject->At(i).second << "\n";
    std::cout << "\n";

}
