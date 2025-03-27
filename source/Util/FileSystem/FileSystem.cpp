#include "Util/FileSystem/FileSystem.h"

#include <iostream>
#include <filesystem>
#include <Windows.h>

#include "Util/Logger/Logger.h"

namespace Util
{
	FileSystem& FileSystem::GetInstance()
	{
		static FileSystem instance;
		return instance;
	}
	
	/**
	 * @brief 현재 실행중인 exe 파일 경로를 반환합니다.
	 * 
	 * @return std::string& 실행파일 경로
	 */
	std::string& FileSystem::GetExcutablePath()
	{
		char buffer[MAX_PATH];
		GetModuleFileNameA(NULL, buffer, MAX_PATH);
		std::string fullPath(buffer);
		return fullPath.substr(0, fullPath.find_last_of("\\/"));
	}

	bool FileSystem::AddFile(const std::string& filePath)
	{
		std::string& fileName = std::filesystem::path(filePath).filename().string(); // 파일명(이름 + 확장자) 추출
		if (fileMap.find(fileName) != fileMap.end())
		{
			// Util::Logger::Warn("파일 \"" + fileName + "(경로: " + filePath + ")" + "\"이(가) 이미 fileMap에 존재합니다.");
			return false;
		}

		Util::File file(filePath);
		if (file.IsValid() == false)
		{
			// Util::Logger::Warn("파일 \"" + fileName + "(경로: " + filePath + ")" + "\" 을(를) 찾을 수 없습니다.");
			return false;
		}

		fileMap.emplace(fileName, std::move(file));
		return true;
	}

	const File* FileSystem::FindFile(const std::string& key) const
	{
		auto iter = fileMap.find(key);
		if (iter == fileMap.end()) {
			// Util::Logger::Warn("파일명 \"" + key + "\"에 해당하는 파일을 찾을 수 없습니다.");
			return nullptr;
		}

		return &(iter->second);
	}

	bool FileSystem::RemoveFile(const std::string& key)
	{
		auto iter = fileMap.find(key);
		if (iter == fileMap.end()) {
			// Util::Logger::Warn("파일명 \"" + key + "\"에 해당하는 파일을 찾을 수 없습니다.");
			return false;
		}

		return true;
	}
}