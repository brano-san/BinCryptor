#pragma once

#include <fstream>
#include <filesystem>
#include <array>
#include <vector>
#include <Windows.h>

namespace crypt
{
	class File;
	class Cryptor;
	class MaskedFileManager;

	class Cryptor
	{
	public:
		Cryptor() = default;

		void cryptFile(File* file,
					   const std::array<std::byte, 8>& keyBytes);

		void cryptFile(MaskedFileManager* files,
					   const std::array<std::byte, 8>& keyBytes);

	private:

	};

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
		MaskedFileManager();
		explicit MaskedFileManager(std::string fileMask);

		~MaskedFileManager();

		void setDeleteRequired(bool flag);

		void setMask(const std::string& fileMask);

		std::string getFileNameAt(int index) const;

	private:
		friend void Cryptor::cryptFile(MaskedFileManager* files, const std::array<std::byte, 8>& keyBytes);

		std::string _fileMask;

		bool _isDeleteRequired = false;

		std::vector<File> _files;
	};
}
