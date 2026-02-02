#pragma once

#include "FactoryMethodPattern.h"
using namespace FactoryMethodNamespace;

#include "AbstractFactoryPattern.h"
using namespace AbstractFactoryNamespace;

#include "BuilderPattern.h"
using namespace BuilderPattern;

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
};

