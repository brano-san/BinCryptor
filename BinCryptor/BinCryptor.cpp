#include "BinCryptor.h"

crypt::File::File(const std::string& path)
{
	this->open(path);
}

std::string crypt::File::getPath()
{
	return _path.string();
}

std::string crypt::File::getFileName()
{
	return _path.filename().string();
}

void crypt::File::open(const std::string& path)
{
	if (_file.is_open())
		_file.close();

	_path = path;

	_file.open(_path);
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
	_file >> data;
	return data;
}

void crypt::File::write(const std::string& str)
{
	_file.write(str.c_str(), str.size());
}

void crypt::MaskedFileManager::setDeleteRequired(const bool flag)
{
	_isDeleteRequired = flag;
}

void crypt::MaskedFileManager::setMask(const std::string& fileMask)
{
	_fileMask = fileMask;
}