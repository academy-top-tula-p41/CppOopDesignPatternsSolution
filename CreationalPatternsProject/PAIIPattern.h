#pragma once
#include <iostream>
#include <fstream>

// SmartPointer
template <typename T>
class SmartPointer
{
	T* value;
public:
	SmartPointer(T* value) : value{ value } {}

	//

	~SmartPointer() { delete value; }
};

class ResourceManager
{
	std::ofstream* file;
public:
	ResourceManager(const std::string& fileName)
	{
		file = new std::ofstream(fileName);
		if (!file->is_open())
			throw std::runtime_error("Failed to open file");
		
		std::cout << "Manager create and open file\n";
	}

	~ResourceManager()
	{
		if (file->is_open())
		{
			file->close();
			std::cout << "file closed\n";
		}
			
	}

	void Write(std::string data)
	{
		*file << data;
		std::cout << "data writed to file\n";
	}
};
