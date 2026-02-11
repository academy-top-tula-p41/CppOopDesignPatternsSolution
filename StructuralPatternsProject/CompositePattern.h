#pragma once
#include <iostream>
#include <vector>
#include <string>

namespace CompositeNamespace
{
	class IComponent
	{
	protected:
		IComponent* parent;
	public:
		virtual ~IComponent() = default;
		
		IComponent*& Parent() { return this->parent; }

		virtual std::string Execute(int level) = 0;
	};

	class Leaf : public IComponent
	{
	public:
		std::string Execute(int level) override
		{
			std::string tabs{ "" };
			for (int i{}; i < level; i++)
				tabs += "\t";
			return tabs + "Leaf";
		}
	};

	class Composite : public IComponent
	{
	protected:
		std::vector<IComponent*> components;
	public:
		std::string Execute(int level) override
		{
			std::string result{ "" };

			std::string tabs{ "" };
			for (int i{}; i < level; i++)
				tabs += "\t";

			for (auto item : components)
				result += item->Execute(level + 1) + "\n";

			return tabs + "Composite [\n" + result + tabs + "]";
		}

		void Add(IComponent* component)
		{
			component->Parent() = this;
			this->components.push_back(component);
		}

		void Remove(IComponent* component)
		{
			auto it = std::ranges::find(components, component);
			components.erase(it);
		}
	};

	class CompositeClient
	{
	public:
		void ClientCode()
		{
			IComponent* box1 = new Composite();
			IComponent* leaf1 = new Leaf();
			IComponent* leaf2 = new Leaf();
			((Composite*)box1)->Add(leaf1);
			((Composite*)box1)->Add(leaf2);

			IComponent* box2 = new Composite();
			IComponent* leaf3 = new Leaf();
			((Composite*)box2)->Add(leaf3);
			((Composite*)box2)->Add(box1);

			std::cout << box2->Execute(0) << "\n";
		}
	};


	// Units Army
	class Unit
	{
	protected:
		int attack{};
		int defence{};
		std::string name;

		std::string Tabs(int level)
		{
			std::string tabs{ "" };
			for (int i{}; i < level; i++)
				tabs += "\t";
			return tabs;
		}
	public:
		Unit(std::string name, int attack, int defence)
			: name{ name }, attack{ attack }, defence{ defence}{ }

		virtual int Attack() = 0;
		virtual int Defence() = 0;
		virtual std::string Info(int level) = 0;
	};

	class Factory
	{
	protected:
		int Rnd(int begin, int end)
		{
			return begin + rand() % (end - begin + 1);
		}
	public:
		virtual Unit* Create(int attack_begin, int attack_end,
			int defence_begin, int defence_end) = 0;
		
	};

	class Infantry : public Unit
	{
	public:
		Infantry(int attack, int defence)
			: Unit("Infantry", attack, defence){ }

		int Attack() override { return this->attack; }
		int Defence() override { return this->defence; }

		std::string Info(int level) override
		{
			return this->Tabs(level) +
				this->name +
				"[" + std::to_string(this->attack) +
				", " + std::to_string(this->defence) + "]\n";
		}
	};

	class InfantryFactory : public Factory
	{
	public:
		Unit* Create(int attack_begin, int attack_end,
			int defence_begin, int defence_end)
		{
			int attack = this->Rnd(attack_begin, attack_end);
			int defence = this->Rnd(defence_begin, defence_end);

			return new Infantry(attack, defence);
		}
		
	};

	class Archer : public Unit
	{
	public:
		Archer(int attack, int defence)
			: Unit("Archer", attack, defence) {
		}

		int Attack() override { return this->attack; }
		int Defence() override { return this->defence; }

		std::string Info(int level) override
		{
			return this->Tabs(level) +
				this->name +
				"[" + std::to_string(this->attack) +
				", " + std::to_string(this->defence) + "]\n";
		}
	};

	class ArcherFactory : public Factory
	{
	public:
		Unit* Create(int attack_begin, int attack_end,
			int defence_begin, int defence_end)
		{
			int attack = this->Rnd(attack_begin, attack_end);
			int defence = this->Rnd(defence_begin, defence_end);

			return new Archer(attack, defence);
		}

	};

	class Cavalry : public Unit
	{
	public:
		Cavalry(int attack, int defence)
			: Unit("Cavalry", attack, defence) {
		}

		int Attack() override { return this->attack; }
		int Defence() override { return this->defence; }

		std::string Info(int level) override
		{
			return this->Tabs(level) +
				this->name +
				"[" + std::to_string(this->attack) +
				", " + std::to_string(this->defence) + "]\n";
		}
	};

	class CavalryFactory : public Factory
	{
	public:
		Unit* Create(int attack_begin, int attack_end,
			int defence_begin, int defence_end)
		{
			int attack = this->Rnd(attack_begin, attack_end);
			int defence = this->Rnd(defence_begin, defence_end);

			return new Cavalry(attack, defence);
		}

	};

	class MilitaryUnit : public Unit
	{
		std::vector<Unit*> units;
	public:
		MilitaryUnit(std::string name) : Unit(name, 0, 0){}
		
		int Attack() override
		{
			int attack{};
			for (auto unit : units)
				attack += unit->Attack();
			return attack;
		}

		int Defence() override
		{
			int defence{};
			for (auto unit : units)
				defence += unit->Defence();
			return defence;
		}

		std::string Info(int level) override
		{
			std::string result{ this->Tabs(level) };
			result += this->name;
			result += "[" + std::to_string(this->Attack());
			result += ", " + std::to_string(this->Defence()) + "]\n";

			for (auto unit : units)
				result += unit->Info(level + 1);

			return result;
		}

		void Add(Unit* unit) { this->units.push_back(unit); }
	};
}

