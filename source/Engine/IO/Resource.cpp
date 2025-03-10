#include "stb_image.h"

#include "Resource.h"

Resource::Resource(const string& filePath, ResourceType resourceType) : texture(), type(resourceType) {
    if (type == MESH)
    {
        // 구현필요
    }
    else if (type == TEXTURE)
    {
        stbi_set_flip_vertically_on_load(true);

        int width, height, channel;
        texture.buffer = stbi_load(filePath.c_str(), &width, &height, &channel, 0);
        texture.width = width;
        texture.height = height;
        texture.channel = channel;
    }
    else if (type == SHADER)
    {
        fileStream.open(filePath, ios::in);

        char buffer[256];
        strerror_s(buffer, sizeof(buffer), errno);

        if (!fileStream.is_open()) {
            cerr << "ERROR | \"" + filePath + "\"를 찾을 수 없음(" << buffer << ")" << endl;
        }
    }
}

Resource::Resource(Resource&& rhs) noexcept : 
    fileStream(std::move(rhs.fileStream)),
    texture(rhs.texture),
    type(rhs.type)
{
    rhs.texture.buffer = nullptr;
}

Resource& Resource::operator=(Resource&& rhs) noexcept
{
    if (this != &rhs)
    {
        if (type == TEXTURE && texture.buffer)
        {
            stbi_image_free(texture.buffer);
        }
        if (type == SHADER && fileStream.is_open())
        {
            fileStream.close();
        }

        fileStream = std::move(rhs.fileStream);
        texture = rhs.texture;
        type = rhs.type;

        rhs.texture.buffer = nullptr;
    }
    return *this;
}

Resource::~Resource() {
    if (type == MESH)
    {

    }
    else if (type == TEXTURE)
    {
        stbi_image_free(texture.buffer);
    }
    else if (type == SHADER)
    {
        if (fileStream.is_open()) {
            fileStream.close();
        }
    }
}