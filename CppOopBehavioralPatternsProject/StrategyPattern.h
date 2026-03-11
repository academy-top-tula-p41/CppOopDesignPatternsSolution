#pragma once
#include <iostream>
#include <vector>

typedef std::pair<std::string, std::string> Property;

class IStrategy
{
public:
	virtual ~IStrategy() = default;
	virtual std::string Execute(std::string data) = 0;
};

class Context
{
	std::unique_ptr<IStrategy> strategy{};
public:
	Context(std::unique_ptr<IStrategy> strategy)
		: strategy{ std::move(strategy) }{ }

	void SetStrategy(std::unique_ptr<IStrategy> strategy)
	{
		this->strategy = std::move(strategy);
	}

	void DoSomeBuisnessLogic(std::string str)
	{
		if (this->strategy)
		{
			std::cout << "Context. Execute strategy: "
				<< this->strategy->Execute(str) << "\n";
		}
		else
			std::cout << "Context. Strategy not setting\n";
	}
};

class ConcreteStartegyLower : public IStrategy
{
public:
	std::string Execute(std::string data) override
	{
		for (int i{}; i < data.length(); i++)
			if (data[i] > 64 && data[i] < 91)
				data[i] += 32;
		return data;
	}
};

class ConcreteStartegyUpper : public IStrategy
{
public:
	std::string Execute(std::string data) override
	{
		for (int i{}; i < data.length(); i++)
			if (data[i] > 96 && data[i] < 123)
				data[i] -= 32;
		return data;
	}
};

class StrategyClient
{
public:
	void ClientCode()
	{
		Context* context = new Context(std::make_unique<ConcreteStartegyLower>());
		std::string str = "AbCdEf";
		context->DoSomeBuisnessLogic(str);
		context->SetStrategy(std::make_unique<ConcreteStartegyUpper>());
		context->DoSomeBuisnessLogic(str);
	}
};

///

class DynamicObject
{
	std::vector<Property> properties;
public:
	void AddProperty(Property property)
	{
		this->properties.push_back(property);
	}

	void AddProperty(std::string key, std::string value)
	{
		this->AddProperty(std::make_pair(key, value));
	}

	void RemoveProperty(std::string key)
	{
		std::erase_if(properties, [key](auto property) 
			{
				return property.first == key;
			});
	}

	void ChangeProperty(std::string key, std::string value)
	{
		auto it = std::ranges::find_if(properties, [key](auto property)
			{
				return property.first == key;
			});

		//if(it != std::ranges::end(properties))
		if (it != properties.end())
			(*it).second = value;
		else
			this->AddProperty(key, value);
	}

	Property At(int index)
	{
		return properties[index];
	}

	Property At(std::string key)
	{
		auto it = std::ranges::find_if(properties, [key](auto property)
			{
				return property.first == key;
			});

		if (it != properties.end())
			return *it;

		throw new std::exception("Property not found");
	}

	int Size() const { return properties.size(); }
};

class ISerializer
{
public:
	virtual std::string Serialize(DynamicObject* object) = 0;
	virtual DynamicObject* Deserialize(std::string serialText) = 0;
};

class XmlSerializer : public ISerializer
{
public:
	std::string Serialize(DynamicObject* object) override
	{
		std::string result{ "<object>\n" };
		for (int i{}; i < object->Size(); i++)
		{
			result += "\t<" + object->At(i).first + ">"
				+ object->At(i).second
				+ "</" + object->At(i).first + ">\n";
		}
		result += "</object>\n";

		return result;
	}

	DynamicObject* Deserialize(std::string serialText) override
	{
		int position{};
		int length{};
		DynamicObject* object = new DynamicObject();

		while (position < serialText.length())
		{
			position = serialText.find("<", position) + 1;
			if (!position) break;
			length = serialText.find(">", position) - position;
			std::string key = serialText.substr(position, length);
			position += length + 1;
			
			if (key == "object") continue;
			if (key == "/object") break;

			length = serialText.find("</", position) - position;
			std::string value = serialText.substr(position, length);
			position = serialText.find(">", position) + 1;

			object->AddProperty(key, value);
		}

		return object;
	}
};

class JsonSerializer : public ISerializer
{
public:
	std::string Serialize(DynamicObject* object) override
	{
		std::string result{ "object = {\n" };
		for (int i{}; i < object->Size(); i++)
		{
			result += "\t\"" + object->At(i).first + "\": \""
				+ object->At(i).second + "\",\n";
		}
		result += "}\n";

		return result;
	}

	DynamicObject* Deserialize(std::string serialText) override
	{
		int position{};
		int length{};
		DynamicObject* object = new DynamicObject();

		while (position < serialText.length())
		{
			position = serialText.find("\"", position) + 1;
			
			if (!position) break;

			length = serialText.find("\"", position) - position;
			std::string key = serialText.substr(position, length);
			position += length + 1;

			position = serialText.find("\"", position) + 1;
			length = serialText.find("\"", position) - position;
			std::string value = serialText.substr(position, length);
			position += length + 1;

			object->AddProperty(key, value);
		}

		return object;
	}
};

class UniversalSerializer : public ISerializer
{
	ISerializer* serializer;
public:
	UniversalSerializer(ISerializer* serializer)
		: serializer{ serializer }{ }

	void SetSerializer(ISerializer* serializer)
	{
		this->serializer = serializer;
	}

	std::string Serialize(DynamicObject* object) override
	{
		return this->serializer->Serialize(object);
	}

	DynamicObject* Deserialize(std::string serialText) override
	{
		return this->serializer->Deserialize(serialText);
	}
};