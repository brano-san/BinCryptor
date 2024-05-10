#include "BinCryptor.h"
#include <iostream>
#include <Windows.h>

// File class
crypt::File::File(const std::string& path, std::ios_base::openmode mode)
{
	this->open(path, mode);
}

std::string crypt::File::getPath()
{
	return _path.string();
}

std::string crypt::File::getFileName()
{
	return _path.filename().string();
}

void crypt::File::open(const std::string& path, std::ios_base::openmode mode)
{
	if (_file.is_open())
		_file.close();
	
	_path = path;

	_file.open(_path, mode);
}

void crypt::File::close()
{
	_file.close();
}

std::string crypt::File::read()
{
	if (!_file.is_open())
		return std::string();
		
	std::string data;
	std::string line;
	while (std::getline(_file, line)) {
		data += line;
	}

	return data;
}

void crypt::File::write(const std::string& str)
{
	_file.write(str.c_str(), str.size());
}

// Cryptor class
void crypt::cryptFile(File* file, const std::array<std::byte, 8>& keyBytes, const std::string& outputPath)
{
	auto data = file->read();

	std::string result;
	result.resize(data.size());

	for (int i = 0; i < data.size(); ++i)
	{
		auto res = static_cast<std::byte>(data[i]) ^ keyBytes[i % 8];

		result[i] = static_cast<unsigned char>(res);
	}

	File resultFile(outputPath, std::ios::out);
	resultFile.write(result);
}

void crypt::cryptFile(MaskedFileManager* files, const std::array<std::byte, 8>& keyBytes, const std::string& outputPath)
{
	for (auto& file : files->_files)
	{
		cryptFile(&file, keyBytes, outputPath);
	}
}

// MaskedFileManager class
crypt::MaskedFileManager::MaskedFileManager(const std::string& path, const std::string& mask)
{
	findFilesByMask(path, mask);
}

void crypt::MaskedFileManager::findFilesByMask(const std::string& path, const std::string& mask)
{
	WIN32_FIND_DATA fileData{};

	std::string maskedPath = path + mask;

	HANDLE hFind = FindFirstFile(maskedPath.c_str(), &fileData);

	if (hFind == INVALID_HANDLE_VALUE)
	{
		return;
	}
	else
	{
		do
		{
			_files.emplace_back(path + fileData.cFileName, std::ios::binary | std::ios::in);
		} while (FindNextFile(hFind, &fileData));

		FindClose(hFind);
	}
}
