#pragma once
#include <iostream>

namespace DecoratorNamespace
{
	class IComponent
	{
	public:
		virtual ~IComponent() = default;
		virtual std::string Execute() = 0;
	};

	class ConcreteComponent : public IComponent
	{
	public:
		std::string Execute() override
		{
			return "Executed Concrete Component";
		}
	};

	class BaseDecorator : public IComponent
	{
	protected:
		IComponent* component;
	public:
		BaseDecorator(IComponent* component)
			: component{ component }{ }

		std::string Execute() override
		{
			return component->Execute();
		}
	};

	class ConcreteDecoratorA : public BaseDecorator
	{
	public:
		ConcreteDecoratorA(IComponent* component)
			: BaseDecorator(component){ }

		std::string Execute() override
		{
			return "Executed Decoartor A with " + component->Execute();
		}
	};

	class ConcreteDecoratorB : public BaseDecorator
	{
	public:
		ConcreteDecoratorB(IComponent* component)
			: BaseDecorator(component) {
		}

		std::string Execute() override
		{
			return "Executed Decoartor B with " + component->Execute();
		}
	};

	class DecoratorClient
	{
	public:
		void ClientCode(IComponent* component)
		{
			std::cout << "Result: " << component->Execute() << "\n";
		}
	};

	///
	class IMessage
	{
	protected:
		std::string from;
		std::string to;
		std::string text;

	public:
		std::string& From() { return this->from; }
		std::string& To() { return this->to; }
		std::string& Text() { return this->text; }

		virtual ~IMessage() = default;

		virtual void Send() = 0;
	};

	class MessanderMessage : public IMessage
	{
		std::string sticker;
	public:
		std::string& Sticker() { return this->sticker; }

		MessanderMessage()
			: sticker(":-)") {}

		void Send() override
		{
			std::cout << "Messanger sended from: " << from
				<< "\nto: " << to
				<< "\ntext: " << text
				<< "\n" << sticker << "\n";
		}
	};

	class EmailMessage : public IMessage
	{
		std::string subject;
	public:
		std::string& Subject() { return this->subject; }

		EmailMessage() : subject("subject"){}

		void Send() override
		{
			std::cout << "Email sended from: " << from
				<< "\nto: " << to
				<< "\subject: " << subject
				<< "\ntext: " << text << "\n";
				
		}
	};


	class IMessageDecorator : public IMessage
	{
	protected:
		IMessage* message;
	public:
		IMessageDecorator(IMessage* message)
			: message{ message }{ }
	};

	class FileMessage : public IMessageDecorator
	{
		std::string file;
	public:
		FileMessage(IMessage* message, std::string file)
			: IMessageDecorator(message), file{ file } {}

		void Send() override
		{
			message->Send();
			std::cout << "attach file: " << file << "\n";
		}
	};

	class ContactMessage : public IMessageDecorator
	{
		std::string contact;
	public:
		ContactMessage(IMessage* message, std::string contact)
			: IMessageDecorator(message), contact{ contact }{ }

		void Send() override
		{
			message->Send();
			std::cout << "with contact info: " << contact << "\n";
		}
	};

	class MessageClient
	{
	public:
		void SendMessage(IMessage* message)
		{
			message->Send();
		}
	};

}
