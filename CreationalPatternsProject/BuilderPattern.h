#pragma once
#include <iostream>
#include <vector>
#include <string>

namespace BuilderPattern
{
	class Product
	{
		std::string name;
		std::vector<std::string> properties;
	public:
		Product(std::string name = "")
			: name{ name }{ }

		std::string& Name() { return name; }

		void AddProperty(std::string property)
		{
			properties.push_back(property);
		}

		void ShowInfo()
		{
			std::cout << "Name: " << name << "\n";
			for (std::string property : properties)
				std::cout << "\t" << property << "\n";
			std::cout << "\n";
		}
	};

	class Builder
	{
		Product* product;
	public:
		Builder() : product{ new Product() }{}

		void Reset() { product = new Product(); }

		Builder* AddName(std::string name) 
		{ 
			product->Name() = name; 
			return this;
		}

		Builder* AddPropertyA() 
		{ 
			product->AddProperty("Property A"); 
			return this;
		}

		Builder* AddPropertyB() 
		{ 
			product->AddProperty("Property B"); 
			return this;
		}

		Builder* AddPropertyC() 
		{ 
			product->AddProperty("Property C"); 
			return this;
		}

		Builder* AddPropertyD() 
		{ 
			product->AddProperty("Property D"); 
			return this;
		}

		Builder* AddPropertyE() 
		{ 
			product->AddProperty("Property E"); 
			return this;
		}

		Product* GetProduct() { return product; }
	};


	//////////
	enum class BoolOperation
	{
		EMPTY,
		AND,
		OR
	};

	class Query
	{
		std::pair<std::string, std::string> tableName;
		std::vector<std::pair<std::string, std::string>> fieldsSelect;
		std::vector<std::pair<std::string, BoolOperation>> whereExpression;
		std::vector<std::pair<std::string, bool>> fieldsOrder;

		std::string queryString{ "" };
	public:
		friend class QueryBuilder;

		std::string QueryString() { return queryString; }
	};

	class QueryBuilder
	{
		Query* query;
	public:
		QueryBuilder() : query{ new Query() }{}

		QueryBuilder* Reset(std::string tableName = "", 
			                std::string tableAlias = "")
		{
			//delete query;
			query = new Query();

			if (!tableName.empty())
				this->Table(tableName, tableAlias);

			return this;
		}

		QueryBuilder* Table(std::string tableName,
							std::string tableAlias = "")
		{
			query->tableName = std::make_pair(tableName, tableAlias);
			return this;
		}

		QueryBuilder* Select(std::string fieldName,
							 std::string fieldAlias = "")
		{
			query->fieldsSelect.push_back(std::make_pair(fieldName, fieldAlias));
			return this;
		}

		QueryBuilder* Where(std::string whereExpression,
							BoolOperation boolOperation = BoolOperation::EMPTY)
		{
			query->whereExpression.push_back(std::make_pair(whereExpression, boolOperation));
			return this;
		}

		QueryBuilder* OrderBy(std::string fieldName, bool ascDirection = true)
		{
			query->fieldsOrder.push_back(std::make_pair(fieldName, ascDirection));
			return this;
		}

		Query* GetQuery()
		{
			std::string result = "SELECT ";

			// select fields
			if (!query->fieldsSelect.empty())
			{
				for (auto field : query->fieldsSelect)
				{
					result += field.first;
					if (!field.second.empty())
						result += " AS " + field.second;
					result += ", ";
				}
				result = result.substr(0, result.length() - 2);
			}
			else
				result += "*";
			result += "\n";

			// from table
			result += "\tFROM " + query->tableName.first;
			if (!query->tableName.second.empty())
				result += " AS " + query->tableName.second;
			result += "\n";

			// where expressions
			if (!query->whereExpression.empty())
			{
				result += "\tWHERE ";
				for (auto expression : query->whereExpression)
				{
					switch (expression.second)
					{
					case BoolOperation::AND:
						result += " AND "; break;
					case BoolOperation::OR:
						result += " OR "; break;
					default:
						result += " ";
					}
					result += expression.first;
				}
				result += "\n";
			}

			// order by fields
			if (!query->fieldsOrder.empty())
			{
				result += "\tORDER BY ";
				for (auto field : query->fieldsOrder)
				{
					result += field.first;
					if (field.second)
						result += " ASC";
					else
						result += " DESC";
					result += ", ";
				}
				result = result.substr(0, result.length() - 2);
				result += "\n";
			}

			query->queryString = result;

			return query;
		}
	};
}
