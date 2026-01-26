#pragma once
#include <iostream>
#include <map>
#include <vector>

class Movie
{
	int id;
	std::string title;
	static int gloabalId;

	std::map<std::string, std::string> properties;
public:
	Movie(std::string title)
		: title{ title }, id{ ++gloabalId }{}
	Movie() : Movie(""){}
	
	std::string& Title() { return title; }
	int Id() const { return id; }

	void SetProperty(std::string propertyName, std::string propertyValue)
	{
		if (propertyName.empty()) return;

		if (properties.contains(propertyName))
			properties[propertyName] = propertyValue;
		else
			properties.insert(std::make_pair(propertyName, propertyValue));
	}

	std::string GetProperty(std::string propertyName)
	{
		if (propertyName.empty() || !properties.contains(propertyName))
			return nullptr;

		return properties[propertyName];
	}

	void DeleteProperty(std::string propertyName)
	{
		if (propertyName.empty() || !properties.contains(propertyName))
			return;

		properties.erase(propertyName);
	}

	std::vector<std::string> GetPropertyNames()
	{
		std::vector<std::string> propertyNames;
		for (auto it{ properties.begin() }; it != properties.end(); it++)
			propertyNames.push_back(it->first);
		return propertyNames;
	}
};
int Movie::gloabalId{};

class HtmlElement
{
			
};
