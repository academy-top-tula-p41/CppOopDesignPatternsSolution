#pragma once
#include <iostream>
#include <string>
#include <vector>

namespace AbstractFactoryNamespace
{
	class Product
	{
	public:
		virtual ~Product() = default;
		virtual std::string ProductOperation() = 0;
	};


	class ProductA : public Product
	{
	public:
		virtual std::string ProductAOperation() = 0;
	};

	class ProductB : public Product
	{
	public:
		virtual std::string ProductBOperation() = 0;
	};
	

	class ProductA1 : public ProductA
	{
	public:
		std::string ProductOperation() override
		{
			return "General Operation with Product A1";
		}

		std::string ProductAOperation() override
		{
			return "Special A Operation with Product A1";
		}
	};

	class ProductA2 : public ProductA
	{
	public:
		std::string ProductOperation() override
		{
			return "General Operation with Product A2";
		}

		std::string ProductAOperation() override
		{
			return "Special A Operation with Product A2";
		}
	};


	class ProductB1 : public ProductB
	{
	public:
		std::string ProductOperation() override
		{
			return "General Operation with Product B1";
		}

		std::string ProductBOperation() override
		{
			return "Special B Operation with Product B1";
		}
	};

	class ProductB2 : public ProductB
	{
	public:
		std::string ProductOperation() override
		{
			return "General Operation with Product B2";
		}

		std::string ProductBOperation() override
		{
			return "Special B Operation with Product B2";
		}
	};


	class AbstractFactory
	{
	public:
		virtual ~AbstractFactory() = default;

		virtual ProductA* CreateProductA() = 0;
		virtual ProductB* CreateProductB() = 0;
	};


	class Factory1 : public AbstractFactory
	{
	public:
		ProductA* CreateProductA() override
		{
			return new ProductA1();
		}

		ProductB* CreateProductB() override
		{
			return new ProductB1();
		}
	};

	class Factory2 : public AbstractFactory
	{
	public:
		ProductA* CreateProductA() override
		{
			return new ProductA2();
		}

		ProductB* CreateProductB() override
		{
			return new ProductB2();
		}
	};


	class Client
	{
	public:
		void ClientCode(AbstractFactory* factory)
		{
			ProductA* productA = factory->CreateProductA();
			ProductB* productB = factory->CreateProductB();

			std::cout << productA->ProductOperation() << "\n";
			std::cout << productA->ProductAOperation() << "\n";

			std::cout << productB->ProductOperation() << "\n";
			std::cout << productB->ProductBOperation() << "\n";
		}
	};

	
	/////////

	// Base Abstract Unit
	class Unit
	{
	protected:
		int attack;
		int defence;

		std::string name;
	public:
		virtual ~Unit() = default;
		Unit(std::string name, int attack = 0, int defence = 0)
			: name{ name }, attack{ attack }, defence{ defence }{ }

		virtual std::string ToString() = 0;
	};

	// Types Classes Units
	class Infantry : public Unit
	{
	public:
		Infantry() : Unit("Infantry", 6, 5){}
	};

	class Archer : public Unit
	{
	public:
		Archer() : Unit("Archer", 7, 4) {}
	};

	class Cavalry : public Unit
	{
	public:
		Cavalry() : Unit("Cavalry", 10, 6) {}
	};

	class Special : public Unit
	{
	public:
		Special(std::string name = "", int attack = 0, int defence = 0)
			: Unit(name, attack, defence){ }
	};


	// Rome Units
	class RomeInfantry : public Infantry
	{
	public:
		RomeInfantry()
		{
			this->name = "Rome " + this->name;
		}

		std::string ToString() override
		{
			return this->name +
				" | Attack: " + std::to_string(this->attack) +
				", Defence: " + std::to_string(this->defence);
		}
	};

	class RomeArcher : public Archer
	{
	public:
		RomeArcher()
		{
			this->name = "Rome " + this->name;
		}

		std::string ToString() override
		{
			return this->name +
				" | Attack: " + std::to_string(this->attack) +
				", Defence: " + std::to_string(this->defence);
		}
	};

	class RomeCavalry : public Cavalry
	{
	public:
		RomeCavalry()
		{
			this->name = "Rome " + this->name;
		}

		std::string ToString() override
		{
			return this->name +
				" | Attack: " + std::to_string(this->attack) +
				", Defence: " + std::to_string(this->defence);
		}
	};

	class RomeChariot : public Special
	{
	public:
		RomeChariot() : Special("Chariot", 15, 8)
		{
			this->name = "Rome " + this->name;
		}

		std::string ToString() override
		{
			return this->name +
				" | Attack: " + std::to_string(this->attack) +
				", Defence: " + std::to_string(this->defence);
		}
	};



	// Carthagen Units
	class CarthagenInfantry : public Infantry
	{
	public:
		CarthagenInfantry()
		{
			this->name = "Carthagen " + this->name;
		}

		std::string ToString() override
		{
			return this->name +
				" | Attack: " + std::to_string(this->attack) +
				", Defence: " + std::to_string(this->defence);
		}
	};

	class CarthagenArcher : public Archer
	{
	public:
		CarthagenArcher()
		{
			this->name = "Carthagen " + this->name;
		}

		std::string ToString() override
		{
			return this->name +
				" | Attack: " + std::to_string(this->attack) +
				", Defence: " + std::to_string(this->defence);
		}
	};

	class CarthagenCavalry : public Cavalry
	{
	public:
		CarthagenCavalry()
		{
			this->name = "Carthagen " + this->name;
		}

		std::string ToString() override
		{
			return this->name +
				" | Attack: " + std::to_string(this->attack) +
				", Defence: " + std::to_string(this->defence);
		}
	};

	class CarthagenElephant : public Special
	{
	public:
		CarthagenElephant() : Special("Elephant", 13, 10)
		{
			this->name = "Carthagen " + this->name;
		}

		std::string ToString() override
		{
			return this->name +
				" | Attack: " + std::to_string(this->attack) +
				", Defence: " + std::to_string(this->defence);
		}
	};

	// Abstract Units Factory
	class ArmyCreator
	{
	public:
		virtual ~ArmyCreator() = default;

		virtual Infantry* CreateInfantry() = 0;
		virtual Archer* CreateArcher() = 0;
		virtual Cavalry* CreateCavalry() = 0;
		virtual Special* CreateSpecial() = 0;
	};

	// Rome Army Creator
	class RomeArmyCreator : public ArmyCreator
	{
	public:
		Infantry* CreateInfantry() override { return new RomeInfantry(); }
		Archer* CreateArcher() override { return new RomeArcher(); }
		Cavalry* CreateCavalry() override { return new RomeCavalry(); }
		Special* CreateSpecial() override { return new RomeChariot(); }
	};

	// Carthagen Army Creator
	class CarthagenArmyCreator : public ArmyCreator
	{
	public:
		Infantry* CreateInfantry() override { return new CarthagenInfantry(); }
		Archer* CreateArcher() override { return new CarthagenArcher(); }
		Cavalry* CreateCavalry() override { return new CarthagenCavalry(); }
		Special* CreateSpecial() override { return new CarthagenElephant(); }
	};

	// Client
	class Army
	{
		std::vector<Unit*> army;

		ArmyCreator* creator;
	public:
		Army(ArmyCreator* creator,
			int infantriesSize,
			int archersSize,
			int cavalriesSize,
			int specialsSize)
			: creator{ creator } 
		{
			for (int i{}; i < infantriesSize; i++)
				army.push_back(creator->CreateInfantry());

			for (int i{}; i < archersSize; i++)
				army.push_back(creator->CreateArcher());

			for (int i{}; i < cavalriesSize; i++)
				army.push_back(creator->CreateCavalry());

			for (int i{}; i < specialsSize; i++)
				army.push_back(creator->CreateSpecial());
		}
			
		
		~Army()
		{
			for (auto unit : army)
				delete unit;
		}

		std::string Info()
		{
			std::string result{ "Army:\n" };
			for (auto unit : army)
				result += "\t" + unit->ToString() + "\n";
			result += "\n";
			
			return result;
		}
	};
}
