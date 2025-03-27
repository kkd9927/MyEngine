#pragma once

#include <unordered_map>
#include <string>
#include "Util/FileSystem/File.h"

namespace Util
{
	class FileSystem
	{
	public:
		static FileSystem& GetInstance();
		static std::string& GetExcutablePath();

		bool AddFile(const std::string& filePath);
		const File* FindFile(const std::string& key) const;
		bool RemoveFile(const std::string& key);
		
	private:
		std::unordered_map<std::string, Util::File> fileMap;

		FileSystem() = default;
		~FileSystem() = default;

		FileSystem(const FileSystem& rhs) = delete;
		FileSystem& operator=(const FileSystem& rhs) = delete;
	};
}