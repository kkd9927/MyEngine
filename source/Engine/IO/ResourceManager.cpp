#include "ResourceManager.h"

ResourceManager::ResourceManager()
{
    string directoryPath = "./resource/";

    addResource("vertex", directoryPath + "glsl/vertex.glsl", ResourceType::SHADER);
    addResource("fragment", directoryPath + "glsl/fragment.glsl", ResourceType::SHADER);
    addResource("awesomeface", directoryPath + "texture/awesomeface.png", ResourceType::TEXTURE);
    addResource("container", directoryPath + "texture/container.jpg", ResourceType::TEXTURE);
}

ResourceManager& ResourceManager::getInstance()
{
    static ResourceManager instance;
    return instance;
}

bool ResourceManager::addResource(const string& key, const string& filePath, ResourceType type)
{
    if (resources.find(key) != resources.end()) {
        return false;
    }
    
    resources.insert(pair<string, Resource>(key, Resource(filePath, type)));
    return true;
}

Resource* ResourceManager::getResource(const string& key)
{
    auto iter = resources.find(key);
    if (iter != resources.end()) {
        return &(iter->second);
    }
    return nullptr;
}