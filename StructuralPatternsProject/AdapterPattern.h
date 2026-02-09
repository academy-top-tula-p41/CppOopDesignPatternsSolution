#pragma once
#include <iostream>
#include <string>

namespace AdapterNamespace
{
	class ClientInterface
	{
	public:
		virtual ~ClientInterface() = default;
		virtual std::string ClientMethod() = 0;
	};

	class ConcreteClassA : public ClientInterface
	{
		int value;
	public:
		ConcreteClassA(int value) : value{ value }{}

		std::string ClientMethod() override
		{
			return "Class A. Value = " + std::to_string(value);
		}
	};

	class ConcreteClassB : public ClientInterface
	{
		int value;
	public:
		ConcreteClassB(int value) : value{ value } {}

		std::string ClientMethod() override
		{
			return "Class B. Value = " + std::to_string(value);
		}
	};


	class Service
	{
		int data;
	public:
		void SetData(int data)
		{
			this->data = data;
		}

		int ServiceMethod()
		{
			return 1000 * data;
		}
	};

	class ServiceAdapter : public ClientInterface
	{
		Service* service;
	public:
		ServiceAdapter(Service* service) 
			: service{ service }{ }

		void SetData(int data)
		{
			service->SetData(data);
		}

		std::string ClientMethod() override
		{
			return "Service. Value = " + std::to_string(service->ServiceMethod());
		}
	};


	class Client
	{
	public:
		void ClientCode(ClientInterface* interface)
		{
			std::cout << interface->ClientMethod() << "\n";
		}
	};

	//

	class IArchivator
	{
	public:
		virtual std::string Zip(std::string text) = 0;
		virtual std::string Unzip(std::string archive) = 0;
	};

	class RarArchivator : public IArchivator
	{
	public:
		std::string Zip(std::string text) override
		{
			return "rar: " + text;
		}

		std::string Unzip(std::string archive) override
		{
			return archive.substr(5, archive.length() - 5);
		}
	};


	class ArjArc
	{
		std::string text;
		std::string archive;
	public:

		std::string& Text() { return this->text; }
		std::string& Archive() { return this->archive; }

		void Arj()
		{
			this->archive = this->text + " <arj>";
		}

		void UnArj()
		{
			this->text = this->archive.substr(0, archive.length() - 6);
		}
	};

	class ArjAdapter : public IArchivator
	{
		ArjArc* arjArc;
	public:
		ArjAdapter(ArjArc* arjArc) : arjArc{ arjArc } {}

		std::string Zip(std::string text) override
		{
			arjArc->Text() = text;
			arjArc->Arj();
			return arjArc->Archive();
		}

		std::string Unzip(std::string archive) override
		{
			arjArc->Archive() = archive;
			arjArc->UnArj();
			return arjArc->Text();
		}
	};

	class ArchClient
	{
	public:
		void ClientCode(IArchivator* archivator, std::string text)
		{
			std::string arch = archivator->Zip(text);
			std::cout << arch << "\n";
			
			std::string txt = archivator->Unzip(arch);
			std::cout << txt << "\n";
		}
	};
}
