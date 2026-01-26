#pragma once
#include <iostream>
#include <string>
#include <vector>

namespace FactoryMethodNamespace
{
	class Product
	{
	public:
		virtual ~Product() = default;
		virtual void ProductOperation() = 0;
	};

	class Factory
	{
	public:
		virtual ~Factory() = default;
		virtual Product* CreateProduct() = 0; // Factory method
	};

	class ProductA : public Product
	{
	public:
		void ProductOperation() override
		{
			std::cout << "Operation product A\n";
		}
	};

	class ProductB : public Product
	{
	public:
		void ProductOperation() override
		{
			std::cout << "Operation product B\n";
		}
	};

	class FactoryA : public Factory
	{
	public:
		Product* CreateProduct() override
		{
			return new ProductA();
		}
	};

	class FactoryB : public Factory
	{
	public:
		Product* CreateProduct() override
		{
			return new ProductB();
		}
	};

	class Client
	{
	public:
		void ClientCode(Factory* factory)
		{
			Product* product = factory->CreateProduct();
			product->ProductOperation();
		}
	};

	class ProductC : public Product
	{
	public:
		void ProductOperation() override
		{
			std::cout << "Operation product C\n";
		}
	};

	class FactoryC : public Factory
	{
	public:
		Product* CreateProduct() override
		{
			return new ProductC();
		}
	};


	// Strategy Game
	class Unit
	{
	protected:
		int attack;
		int defence;

		std::string name;
	public:
		virtual ~Unit() = default;

		Unit(std::string name = "", int attack = 0, int defence = 0)
			: name{ name }, attack{ attack }, defence{ defence }{}

		virtual std::string Info() = 0;
	};

	class UnitCreator
	{
	public:
		virtual ~UnitCreator() = default;

		virtual Unit* Create() = 0;
	};

	class Infantry : public Unit
	{
	public:
		Infantry() : Unit("Infantry", 4, 6) {}

		std::string Info() override
		{
			return "(" + this->name + " | " +
				"Attack: " + std::to_string(this->attack) +
				" Defence: " + std::to_string(this->defence) +
				")";
		}
	};

	class InfantryCreator : public UnitCreator
	{
	public:
		Unit* Create() override
		{
			return new Infantry();
		}
	};

	class Archer : public Unit
	{
	public:
		Archer() : Unit("Archer", 7, 4) {}

		std::string Info() override
		{
			return "{" + this->name + " | " +
				"Attack: " + std::to_string(this->attack) +
				" Defence: " + std::to_string(this->defence) +
				"}";
		}
	};

	class ArcherCreator : public UnitCreator
	{
	public:
		Unit* Create() override
		{
			return new Archer();
		}
	};

	class Cavalry : public Unit
	{
	public:
		Cavalry() : Unit("Cavalry", 9, 7) {}

		std::string Info() override
		{
			return "[" + this->name + " | " +
				"Attack: " + std::to_string(this->attack) +
				" Defence: " + std::to_string(this->defence) +
				"]";
		}
	};

	class CavalryCreator : public UnitCreator
	{
	public:
		Unit* Create() override
		{
			return new Cavalry();
		}
	};

	// Client
	class Army
	{
		std::vector<Unit*> units;
		std::vector<UnitCreator*> creators;
	public:
		void AddCreator(UnitCreator* creator)
		{
			creators.push_back(creator);
		}

		void ArmyCreate(int count)
		{
			for (int i{}; i < creators.size(); i++)
			{
				for (int u{}; u < count; u++)
					units.push_back(creators[i]->Create());
			}
		}

		void ArmyInfo()
		{
			for (auto unit : units)
				std::cout << unit->Info() << "\n";
		}
	};

}
