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

TEST(FileTest, ReadData) {
	std::string sourceFilePath = "G://file.txt";
	crypt::File sourceFile(sourceFilePath, std::ios::in);

	std::string result = "123456";

	ASSERT_STREQ(sourceFile.read().c_str(), result.c_str());
}

TEST(FileTest, WriteData) {
	std::string inputFilePath = "G://WriteTest.txt";
	crypt::File inputFile(inputFilePath, std::ios::out);
	
	std::string data = "123456";
	inputFile.write(data);

	inputFile.close();

	crypt::File outputFile(inputFilePath, std::ios::in);

	std::string result = outputFile.read();

	outputFile.close();

	ASSERT_STREQ(data.c_str(), result.c_str());
}
