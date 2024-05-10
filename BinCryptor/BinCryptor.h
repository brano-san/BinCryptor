#pragma once

#include <fstream>
#include <filesystem>
#include <array>
#include <vector>
#include <Windows.h>

namespace crypt
{
	class MaskedFileManager;

	class Cryptor
	{
	public:
		Cryptor();

		~Cryptor();

		void cryptFiles(MaskedFileManager* files, const std::array<std::byte, 8>& keyBytes);

	private:

	};

	class File
	{
	public:
		File() = default;
		explicit File(const std::string& path);

	public:
		std::string getPath();
		std::string getFileName();

		void close();
		std::string read();
		void open(const std::string& path);
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
		friend void Cryptor::cryptFiles(MaskedFileManager* files, const std::array<std::byte, 8>& keyBytes);

		std::string _fileMask;

		bool _isDeleteRequired = false;

		std::vector<File> _files;
	};
}
