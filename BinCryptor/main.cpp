#include <iostream>

#include "BinCryptor.h"

using namespace std;

constexpr std::byte operator""_B(unsigned long long ch)
{
	return static_cast<std::byte>(ch);
}

int main()
{
	constexpr std::array keyBytes{
		0xFF_B, 0xFF_B, 0xFF_B, 0xFF_B,
		0xFF_B, 0xFF_B, 0xFF_B, 0xFF_B
	};

	crypt::File file("G://file.bin", std::ios::binary | std::ios::in);

	crypt::Cryptor cryptor;
	cryptor.cryptFile(&file, keyBytes);

	return 0;
}
