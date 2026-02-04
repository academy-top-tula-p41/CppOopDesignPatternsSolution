#pragma once
#include <thread>

#include "FactoryMethodPattern.h"
using namespace FactoryMethodNamespace;

#include "AbstractFactoryPattern.h"
using namespace AbstractFactoryNamespace;

#include "BuilderPattern.h"
using namespace BuilderPattern;

#include "PrototypePattern.h"
using namespace PtototypeNamespace;

#include "SingletonPattern.h"

class Examples
{
public:
	static void FactoryMethodExamples()
	{
        /*Client* client = new Client();
        client->ClientCode(new FactoryA());
        client->ClientCode(new FactoryB());

        client->ClientCode(new FactoryC());*/

        Army* army = new Army();
        army->AddCreator(new InfantryCreator());
        army->AddCreator(new ArcherCreator());
        army->AddCreator(new CavalryCreator());
        army->ArmyCreate(5);
        army->ArmyInfo();
	}

    static void AbstractFactoryExamples()
    {
        /*AbstractFactoryNamespace::Client* client
        = new AbstractFactoryNamespace::Client();

    client->ClientCode(new Factory1());
    client->ClientCode(new Factory2());*/

        Army* romeArmy = new Army(new RomeArmyCreator(), 5, 7, 6, 4);
        Army* carthagenArmy = new Army(new CarthagenArmyCreator(), 6, 5, 7, 4);

        std::cout << romeArmy->Info();
        std::cout << carthagenArmy->Info();
    }

    static void BuilderExamples()
    {
        /*Builder* builder = new Builder();
    builder->AddName("Product 1");
    builder->AddPropertyA();
    builder->AddPropertyE();
    builder->AddPropertyB();
    builder->AddPropertyD();

    Product* product = builder->GetProduct();
    product->ShowInfo();

    builder->Reset();
    Product* product2 = builder->AddName("Product 2")
                                ->AddPropertyB()
                                ->AddPropertyD()
                                ->AddPropertyA()
                                ->GetProduct();
    product2->ShowInfo();*/

        QueryBuilder* builder = new QueryBuilder();
        Query* query = builder->Table("employees", "Employees")
            ->Select("id")
            ->Select("last_name", "Last Name")
            ->Select("first_name", "First Name")
            ->Select("salary")
            ->Where("salary > 100000")
            ->Where("YEAR(birthDate) > 2000", BoolOperation::AND)
            ->Where("city = 'Moscow'", BoolOperation::OR)
            ->OrderBy("last_name")
            ->OrderBy("salary", false)
            ->GetQuery();

        std::cout << query->QueryString();

        Query* query2 = builder->Reset("cities")->GetQuery();
        std::cout << query2->QueryString();

        std::cout << query->QueryString();
    }

    static void PrototypeExamples()
    {
        /*Prototype* v1 = new ValueObject();
    ((ValueObject*)v1)->Value() = 100;

    Prototype* v2 = v1->Clone();
    ((ValueObject*)v2)->Value() = 200;

    std::cout << ((ValueObject*)v1)->Value() << "\n";
    std::cout << ((ValueObject*)v2)->Value() << "\n";


    Prototype* r1 = new ReferenceObject(1);
    ((ReferenceObject*)r1)->Reference()[0] = 100;

    Prototype* r2 = r1->Clone();
    ((ReferenceObject*)r2)->Reference()[0] = 200;

    std::cout << ((ReferenceObject*)r1)->Reference()[0] << "\n";
    std::cout << ((ReferenceObject*)r2)->Reference()[0] << "\n";

    CopyObject c1;
    c1.Reference()[0] = 100;

    CopyObject c2;
    c2 = c1;
    c2.Reference()[0] = 200;

    std::cout << c1.Reference()[0] << "\n";
    std::cout << c2.Reference()[0] << "\n";*/

        UnitClonesStore* store = new UnitClonesStore();
        for (int i{}; i < 10; i++)
        {
            if (i & 1)
                std::cout << ((PtototypeNamespace::Unit*)store->GetUnit(UnitType::Infantry))->ToString() << "\n";
            else
                std::cout << ((PtototypeNamespace::Unit*)store->GetUnit(UnitType::Archer))->ToString() << "\n";
        }
    }

    static void SingletonExamples()
    {
        /*Singleton* s1 = Singleton::GetInstance();
    Singleton* s2 = Singleton::GetInstance();

    std::cout << s1 << " " << s2 << "\n";*/

    // Single Thread
    /*Computer* computer = new Computer();
    computer->Lounch("Windows");

    std::cout << computer->System()->Title() << "\n";

    computer->System() = OperationSystem::GetSystem("Linux");

    std::cout << computer->System()->Title() << "\n";*/

    // Multi Thread
        auto computerLaunch = [](std::string osName)
            {
                Computer* computer = new Computer();
                computer->Lounch(osName);

                std::cout << computer->System()->Title() << "\n";
            };

        std::thread comp1(computerLaunch, "Windows");
        std::thread comp2(computerLaunch, "Linux");

        comp1.join();
        comp2.join();

        std::cout << "\n";
    }
};

