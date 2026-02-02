#pragma once
#include <iostream>

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

}
