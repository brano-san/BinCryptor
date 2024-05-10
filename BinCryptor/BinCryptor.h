#pragma once

#include <fstream>
#include <filesystem>
#include <array>
#include <vector>
#include <Windows.h>

namespace crypt
{
	class File;
	class MaskedFileManager;

	void cryptFile(File* file,
		const std::array<std::byte, 8>& keyBytes,
		const std::string& outputPath);

	void cryptFile(MaskedFileManager* files,
		const std::array<std::byte, 8>& keyBytes,
		const std::string& outputPath);

	class File
	{
	public:
		File() = default;
		File(const std::string& path,
			std::ios_base::openmode mode = std::ios::in | std::ios::out);

	public:
		std::string getPath();
		std::string getFileName();

		void open(const std::string& path,
			std::ios_base::openmode mode = std::ios::in | std::ios::out);
		void close();

		std::string read();
		void write(const std::string& str);

	private:
		std::fstream _file;
		std::filesystem::path _path;
	};

	class MaskedFileManager
	{
	public:
		MaskedFileManager() = default;
		explicit MaskedFileManager(const std::string& path,
								   const std::string& mask);

		~MaskedFileManager() = default;

	public:
		void findFilesByMask(const std::string& path,
							 const std::string& mask);

	private:
		friend void cryptFile(MaskedFileManager* files,
							  const std::array<std::byte, 8>& keyBytes,
							  const std::string& outputPath);

	private:
		std::vector<File> _files;
	};
}
