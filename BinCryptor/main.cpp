#include <iostream>

#include "BinCryptor.h"

using namespace std;

constexpr std::byte operator""_B(unsigned long long ch)
{
	return static_cast<std::byte>(ch);
}

int main()
{
	crypt::MaskedFileManager files("G://", "*.bin");

	constexpr std::array keyBytes{
		0xFF_B, 0xFF_B, 0xFF_B, 0xFF_B,
		0xFF_B, 0xFF_B, 0xFF_B, 0xFF_B
	};

	crypt::cryptFile(&files, keyBytes, "G://result.txt");

	return 0;
}
