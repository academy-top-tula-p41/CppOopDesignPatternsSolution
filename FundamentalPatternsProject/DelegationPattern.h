// Delegation Pattern

#pragma once
#include <iostream>

class IVending
{
public:
	virtual void Select() = 0;
	virtual void Payment() = 0;
	virtual void Receipt() = 0;
};

class BeverageVending : public IVending
{
public:
	void Select() override
	{
		std::cout << "Beverage Vending Select\n";
	}
	void Payment() override
	{
		std::cout << "Beverage Vending Payment\n";
	}
	void Receipt() override
	{
		std::cout << "Beverage Vending Receipt\n";
	}
};

class CigaretteVending : public IVending
{
public:
	void Select() override
	{
		std::cout << "Cigarette Vending Select\n";
	}
	void Payment() override
	{
		std::cout << "Cigarette Vending Payment\n";
	}
	void Receipt() override
	{
		std::cout << "Cigarette Vending Receipt\n";
	}
};

class BookVending : public IVending
{
public:
	void Select() override
	{
		std::cout << "Book Vending Select\n";
	}
	void Payment() override
	{
		std::cout << "Book Vending Payment\n";
	}
	void Receipt() override
	{
		std::cout << "Book Vending Receipt\n";
	}
};

class UniversalVending : public IVending
{
	IVending* vending;
public:

	UniversalVending() : vending{ new BeverageVending() } {}
	~UniversalVending() { delete vending; }

	void ToBeverage()
	{
		delete vending;
		vending = new BeverageVending();
	}

	void ToCigarette()
	{
		delete vending;
		vending = new CigaretteVending();
	}

	void SetVending(IVending* vending)
	{
		this->vending = vending;
	}

	void Select() override
	{
		vending->Select();
	}
	void Payment() override
	{
		vending->Payment();
	}
	void Receipt() override
	{
		vending->Receipt();
	}
};