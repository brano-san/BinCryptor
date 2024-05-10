#include <gtest/gtest.h>
#include <BinCryptor/BinCryptor.h>

TEST(FileTest, PathConstructorFileName) {
	std::string fileName = "file.txt";
	
	crypt::File file("G://file.txt");

	ASSERT_STREQ(file.getFileName().c_str(), fileName.c_str());
}

TEST(FileTest, OpenFuncFileName) {
	std::string fileName = "file.txt";

	crypt::File file;
	file.open("G://file.txt");

	ASSERT_STREQ(file.getFileName().c_str(), fileName.c_str());
}

TEST(FileTest, PathConstructorFilePath) {
	std::string filePath = "G://file.txt";

	crypt::File file(filePath);

	ASSERT_STREQ(file.getPath().c_str(), filePath.c_str());
}

TEST(FileTest, OpenFuncFilePath) {
	std::string filePath = "G://file.txt";

	crypt::File file;
	file.open(filePath);

	ASSERT_STREQ(file.getPath().c_str(), filePath.c_str());
}