#pragma once
#include <iostream>
#include <map>

namespace PtototypeNamespace
{
	class Prototype
	{
	public:
		virtual ~Prototype() = default;
		virtual Prototype* Clone() = 0;
	};

	class ValueObject : public Prototype
	{
		int value{};
	public:

		int& Value() { return value; }

		Prototype* Clone() override
		{
			return new ValueObject(*this);
		}
	};

	class ReferenceObject : public Prototype
	{
		int* reference{};
		int size{};
	public:
		ReferenceObject(int size = 1)
			: size{ size }, reference{ new int[size] }{ }

		int*& Reference() { return reference; }
		int Size() { return size; }

		Prototype* Clone() override
		{
			ReferenceObject* clone = new ReferenceObject(this->size);
			for (int i{}; i < size; i++)
				clone->reference[i] = this->reference[i];
			return clone;
		}
	};

	class CopyObject
	{
		int* reference{};
		int size{};
	public:
		CopyObject(int size = 1)
			: size{ size }, reference{ new int[size] } {
		}

		CopyObject(const CopyObject& other)
			: size{ other.size }
		{
			reference = new int[size];
			for (int i{}; i < size; i++)
				reference[i] = other.reference[i];
		}

		CopyObject operator=(const CopyObject& other)
		{
			size = other.size;
			delete[] reference;
			reference = new int[size];
			for (int i{}; i < size; i++)
				reference[i] = other.reference[i];

			return *this;
		}

		int*& Reference() { return reference; }
		int Size() { return size; }
	};


	////
	enum class UnitType
	{
		Infantry,
		Archer,
		Cavalry
	};

	class Unit : public Prototype
	{
	protected:
		std::string name;
	public:
		Unit(std::string name = "") : name{ name } {}
		virtual ~Unit() = default;

		std::string& Name() { return name; }

		virtual std::string ToString()
		{
			return "Unit: " + name;
		}
	};

	class Factory
	{
	public:
		virtual Unit* Create() = 0;
	};

	class Infantry : public Unit
	{
	public:
		Infantry() : Unit("Infantry"){}
		Prototype* Clone() override
		{
			return new Infantry(*this);
		}
	};

	class InfantryFactory : public Factory
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
		Archer() : Unit("Archer") {}
		Prototype* Clone() override
		{
			return new Archer(*this);
		}
	};

	class ArcherFactory : public Factory
	{
	public:
		Unit* Create() override
		{
			return new Archer();
		}
	};


	class UnitClonesStore
	{
		std::map<UnitType, Prototype*> clones;
	public:
		Prototype* GetUnit(UnitType type)
		{
			if (clones.contains(type))
				return clones[type]->Clone();

			Factory* factory{};
			
			switch (type)
			{
			case PtototypeNamespace::UnitType::Infantry:
				factory = new InfantryFactory();
				break;
			case PtototypeNamespace::UnitType::Archer:
				factory = new ArcherFactory();
				break;
			case PtototypeNamespace::UnitType::Cavalry:
				break;
			default:
				break;
			}

			if (!factory) return nullptr;

			auto unit = (Prototype*)factory->Create();
			clones.insert(std::make_pair(type, unit));
			delete factory;

			return unit->Clone();
		}
	};
}
