// Interpreter Pattern
#pragma once
#include <iostream>
#include <map>

/*
IEExpression ::= NumberExpression | Constant | BinaryOperation
NumberExpression ::= [0-9]+
BinaryOperation ::= AddOperation | MultiplyOperation
AddOperation ::= IExpression + IExpression
*/

class Context;

class IExpression
{
public:
	virtual double Interpret(Context* context) = 0;
};

class Context
{
	std::map<std::string, double> variables;
public:
	double GetVar(std::string name)
	{
		return variables[name];
	}
	void SetVar(std::string name, double value)
	{
		variables[name] = value;
	}
};

class Number : public IExpression
{
	std::string name;
public:
	Number(std::string name) : name{ name }{}

	double Interpret(Context* context) override
	{
		return context->GetVar(name);
	}
};

class BynaryOperation : public IExpression
{
protected:
	IExpression* left;
	IExpression* right;
public:
	BynaryOperation(IExpression* left, IExpression* right)
		: left{ left }, right{ right } {}
};

class AddOperation : public BynaryOperation
{
public:
	AddOperation(IExpression* left, IExpression* right)
		: BynaryOperation(left, right){ }

	double Interpret(Context* context) override
	{
		return left->Interpret(context) + right->Interpret(context);
	}
};

class MultiplyOperation : public BynaryOperation
{
public:
	MultiplyOperation(IExpression* left, IExpression* right)
		: BynaryOperation(left, right) {}

	double Interpret(Context* context) override
	{
		return left->Interpret(context) * right->Interpret(context);
	}
};

class InterpterterClient
{
public:
	void ExpressionOne()
	{
		Context* context = new Context();
		context->SetVar("a", 5);
		context->SetVar("b", 3);
		context->SetVar("c", 4);

		IExpression* expression = new MultiplyOperation(
			new AddOperation(
				new Number("a"),
				new Number("b")),
			new Number("c"));
		std::cout << "result = " << expression->Interpret(context) << "\n";

		//context->SetVar("b", 10);
		//std::cout << "result = " << expression->Interpret(context) << "\n";

		

		expression = new AddOperation(
			new Number("a"),
			new MultiplyOperation(
				new Number("b"),
				new Number("c")));

		std::cout << "result = " << expression->Interpret(context) << "\n";
	}
};