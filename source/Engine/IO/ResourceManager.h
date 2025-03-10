#pragma once

#include <iostream>
#include <string>
#include <unordered_map>
#include "Resource.h"

using namespace std;

class ResourceManager {
private:
    unordered_map<string, Resource> resources;

    ResourceManager();

    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;
public:
    static ResourceManager& getInstance();
    bool addResource(const string& key, const string& filePath, ResourceType type);
    Resource* getResource(const string& key);
};