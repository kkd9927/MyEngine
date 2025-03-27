#pragma once

#include <fstream>
#include <string>

namespace Util 
{
	class File
	{
	public:
		explicit File(const std::string& filePath);
		~File();

		File(File&& rhs) noexcept;
		File& operator=(File&& rhs) noexcept;

		const std::ifstream& GetStream() const;
		const bool IsValid() const;

		const std::string GetStreamToString() const;

	private:
		std::ifstream stream;

		File(const File& rhs) = delete;
		File& operator=(const File& rhs) = delete;
	};
}