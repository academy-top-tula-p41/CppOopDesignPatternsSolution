#include <iostream>

#include "FlyweightPattern.h"
using namespace FlyweightNamespace;

int main()
{
	FlyweightFactory factory { 
		SharedState("tank", "tank.jpg"), 
		SharedState("plane", "plane.png") };

	factory.ListFlyweights();

	SharedState tankState("tank", "tank.jpg");
	auto fw = factory.GetFlyweight(tankState);
	
	std::cout << "\n----\n" << fw.GetSharedState()->ToString() << "\n----\n\n";

	factory.ListFlyweights();
}