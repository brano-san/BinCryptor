#include <iostream>

#include "BinCryptor.h"

using namespace std;

constexpr std::byte operator""_B(unsigned long long ch)
{
	return static_cast<std::byte>(ch);
}

int main()
{
	crypt::MaskedFileManager files("G:/", "file.*");

	constexpr std::array keyBytes{
		0xFF_B, 0xFF_B, 0xFF_B, 0xFF_B,
		0xFF_B, 0xFF_B, 0xFF_B, 0xFF_B
	};

	crypt::Cryptor cryptor(new crypt::NewNameSavingStrategy);

	cryptor.cryptFile(&files, keyBytes, "G:/");

	return 0;
}
