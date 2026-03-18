#pragma once
#include <iostream>
#include <list>

// Observer - Subscriber
class Observer
{
	std::string name;
public:
	Observer(std::string name)
		: name{ name }{ }

	virtual ~Observer() = default;
	virtual void EventHandler(std::string stateObservable) = 0;
	std::string Name() const { return this->name; }
};

// Observable - Publisher
class Observable
{
public:
	virtual ~Observable() = default;
	virtual void AddObserver(Observer* observer) = 0;
	virtual void RemoveObserver(Observer* observer) = 0;
	virtual void NotifyObservers() = 0;
};

class ConcreteObservable : public Observable
{
	std::list<Observer*> observers;
	std::string state;

	std::string GenerateState(int length = 20)
	{
		std::string alpha = "abcdefghijklmnopqrstuvwxyz"
							"ABCDEFGHIJKLMNOPQRSTUVWXYZ";
		std::string randomState = "";
		for (int i{}; i < length; i++)
			randomState += alpha[std::rand() % alpha.length()];
		return randomState;
	}
public:
	void AddObserver(Observer* observer) override
	{
		std::cout << "Observable. Add new observer "
			<< observer->Name() << "\n";
		observers.push_back(observer);
	}

	void RemoveObserver(Observer* observer) override
	{
		std::cout << "Observable. Remove observer "
			<< observer->Name() << "\n";
		observers.remove(observer);
	}

	void NotifyObservers() override
	{
		std::cout << "Observable. Notify my observers\n";
		for (auto observer : observers)
			observer->EventHandler(this->state);
	}

	void BuisnessLogic()
	{
		this->state = this->GenerateState();
		std::cout << "\nObservable. Change state: "
			<< this->state << "\n";
		this->NotifyObservers();
	}
};

class ConcreteObserver : public Observer
{
	std::string state;
	Observable* observable{};
public:
	ConcreteObserver(std::string name, Observable* observable = nullptr)
		: Observer(name), observable{ observable }
	{
		if (this->observable)
			this->Attach(this->observable);
	}

	void EventHandler(std::string stateObservable) override
	{
		std::cout << "Observer " << this->Name()
			<< ". Handled event from Observable\n";
		this->state = stateObservable;
		std::cout << "\tNew state: " << this->state << "\n";
	}

	void Attach(Observable* observable)
	{
		std::cout << "Observer " << this->Name()
			<< ". Attach to Observable\n";
		this->observable = observable;
		this->observable->AddObserver(this);
	}

	void Detach()
	{
		std::cout << "Observer " << this->Name()
			<< ". Detach from Observable\n";
		this->observable->RemoveObserver(this);
	}
};

class ObserverClient
{
public:
	void ClientCode()
	{
		ConcreteObservable* publisher = new ConcreteObservable();

		ConcreteObserver* subsriber = new ConcreteObserver("Subscriber A");
		subsriber->Attach(publisher);

		ConcreteObserver* observer = new ConcreteObserver("Observer B", publisher);

		for (int i{}; i < 3; i++)
			publisher->BuisnessLogic();
		
		subsriber->Detach();

		publisher->BuisnessLogic();
	}
};

///

struct MarketInfo
{
	int usd;
	int euro;
};

class IMarketClient;

class IMarket
{
public:
	virtual void AddClient(IMarketClient* client) = 0;
	virtual void RemoveClient(IMarketClient* client) = 0;
	virtual void NotifyClients() = 0;
};

class IMarketClient
{
protected:
	std::string name;
	IMarket* market;
	int levelUsd;
	int levelEuro;
public:
	IMarketClient(std::string name,
		IMarket* market,
		int levelUsd,
		int levelEuro)
		: name{ name },
		market{ market },
		levelUsd{ levelUsd },
		levelEuro{ levelEuro }
	{
		if (market)
		{
			market->AddClient(this);
			std::cout << this->name << " add to Market\n";
		}
	}

	virtual void MarketEvantHandler(MarketInfo* info) = 0;
	std::string Name() { return this->name; }
};

class Market : public IMarket
{
	MarketInfo* info = new MarketInfo;
	std::list<IMarketClient*> clients;
public:
	void AddClient(IMarketClient* client) override
	{
		clients.push_back(client);
		std::cout << "Market add client " << client->Name() << "\n";
	}

	void RemoveClient(IMarketClient* client) override
	{
		clients.remove(client);
		std::cout << "Market remove client " << client->Name() << "\n";
	}

	void NotifyClients() override
	{
		std::cout << "Market notify clients\n";
		for (auto client : clients)
			client->MarketEvantHandler(info);
	}

	void StockTraiding()
	{
		this->info->usd = 80 + rand() % 21;
		this->info->euro = 90 + rand() % 30;

		std::cout << "Market traidinf:\n";
		std::cout << "\tUsd = " << this->info->usd << "\n";
		std::cout << "\tEuro = " << this->info->euro << "\n";

		this->NotifyClients();
	}
};

class BrokerUsd : public IMarketClient
{
public:
	BrokerUsd(IMarket* market, int levelUsd)
		: IMarketClient("Broker Usd", market, levelUsd, 0){ }

	void MarketEvantHandler(MarketInfo* info) override
	{
		if (this->levelUsd <= info->usd)
			std::cout << this->name << " saled usd at " << info->usd << "\n";
		else
			std::cout << this->name << " byed usd at " << info->usd << "\n";
	}
};

class BrokerEuro : public IMarketClient
{
public:
	BrokerEuro(IMarket* market, int levelEuro)
		: IMarketClient("Broker Euro", market, 0, levelEuro) {}

	void MarketEvantHandler(MarketInfo* info) override
	{
		if (this->levelEuro <= info->euro)
			std::cout << this->name << " saled euro at " << info->euro << "\n";
		else
			std::cout << this->name << " byed euro at " << info->euro << "\n";
	}
};

class Broker : public IMarketClient
{
public:
	Broker(IMarket* market, int levelUsd, int levelEuro)
		: IMarketClient("Broker Univarsal", market, levelUsd, levelEuro) {}

	void MarketEvantHandler(MarketInfo* info) override
	{
		if (this->levelUsd <= info->usd)
			std::cout << this->name << " saled usd at " << info->usd << "\n";
		else
			std::cout << this->name << " byed usd at " << info->usd << "\n";

		if (this->levelEuro <= info->euro)
			std::cout << this->name << " saled euro at " << info->euro << "\n";
		else
			std::cout << this->name << " byed euro at " << info->euro << "\n";
	}
};

class Buisness
{
public:
	void BuisnessTraiding()
	{
		int rounds{ 3 };
		Market* market = new Market();
		BrokerUsd* brokerUsd = new BrokerUsd(market, 90);
		BrokerEuro* brokerEuro = new BrokerEuro(market, 105);
		Broker* brokerUniversal = new Broker(market, 88, 110);

		for (int i{}; i < rounds; i++)
			market->StockTraiding();
	}
};