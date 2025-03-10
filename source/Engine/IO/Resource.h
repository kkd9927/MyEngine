#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <cerrno>
#include <cstring>

#include "ResourceType.h"

using namespace std;

struct Texture
{
	unsigned char* buffer;
	int width;
	int height;
	int channel;
};

class Resource
{
private:
	ifstream fileStream;
	Texture texture;
	ResourceType type;

public:
	Resource(const string& filePath, ResourceType resourceType);
	Resource(Resource&& rhs) noexcept;
	Resource& operator=(Resource&& rhs) noexcept;
	~Resource();

	const ifstream& getShader() const { return fileStream; }
	const Texture& getTextrue() const { return texture; }
	Texture& getTextrue() { return texture; }

	Resource(const Resource&) = delete;
	Resource& operator=(const Resource&) = delete;

};