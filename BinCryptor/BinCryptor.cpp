#include "BinCryptor.h"
#include <iostream>

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

// MaskedFileManager class
void crypt::MaskedFileManager::setDeleteRequired(const bool flag)
{
	_isDeleteRequired = flag;
}

void crypt::MaskedFileManager::setMask(const std::string& fileMask)
{
	_fileMask = fileMask;
}

void crypt::Cryptor::cryptFile(File* file, const std::array<std::byte, 8>& keyBytes)
{
	auto data = file->read();

	std::string result;
	result.resize(data.size());

	for (int i = 0; i < data.size(); ++i)
	{
		auto res = static_cast<std::byte>(data[i]) ^ keyBytes[i % 8];

		result[i] = static_cast<unsigned char>(res);
	}
	
	File resultFile("G://result.txt", std::ios::out);
	resultFile.write(result);
}

void crypt::Cryptor::cryptFile(MaskedFileManager* files, const std::array<std::byte, 8>& keyBytes)
{
	for (auto& file : files->_files)
	{
		cryptFile(&file, keyBytes);
	}
}
