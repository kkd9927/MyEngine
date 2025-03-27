#include "Util/FileSystem/File.h"
#include "Util/Logger/Logger.h"

#include <iostream>
#include <sstream>
#include <filesystem>

namespace Util
{
	File::File(const std::string& filePath)
	{
		stream.open(filePath, std::ios::in);
		std::string& fileName = std::filesystem::path(filePath).filename().string();
	}

	File::~File()
	{
		if (stream.is_open())
		{
			stream.close();
		}
	}

	File::File(File&& rhs) noexcept
		: stream(std::move(rhs.stream))
	{}

	File& File::operator=(File&& rhs) noexcept
	{
		if (this != &rhs)
		{
			stream = std::move(rhs.stream);
		}
		return *this;
	}

	const std::ifstream& File::GetStream() const
	{
		return stream;
	}

	const bool File::IsValid() const
	{
		if (stream.is_open())
		{
			return true;
		}
		return false;
	}

	const std::string File::GetStreamToString() const
	{
		std::stringstream strStream;
		strStream << stream.rdbuf();
		return strStream.str();
	}
}