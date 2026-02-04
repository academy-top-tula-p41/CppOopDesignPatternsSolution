#pragma once
#include <vector>

class Object
{
	static int globalId;
	int id;
public:
	Object() : id{ ++globalId }{}
	int operator()() { return id; }
};
int Object::globalId = 0;


class ObjectsPool
{
	struct ObjectBox
	{
		Object* object{};
		bool isUse{};
	};

	std::vector<ObjectBox> pool;
public:
	Object* CreateObject()
	{
		for (int i{}; i < pool.size(); i++)
		{
			if (!pool[i].isUse)
			{
				pool[i].isUse = true;
				return pool[i].object;
			}
		}

		ObjectBox box{ new Object, true };
		pool.push_back(box);

		return box.object;
	}
	
	void DeleteObject(Object* object)
	{
		for (int i{}; i < pool.size(); i++)
		{
			if (pool[i].object == object)
			{
				pool[i].isUse = false;
				break;
			}
		}
	}

	virtual ~ObjectsPool()
	{
		for (auto box : pool)
			delete box.object;
	}
};
