#include <iostream>
#include <bitset>
#include <math.h>
#include <vector>
#include <sstream>

std::string binaryText(std::string str)
{
	std::string binaryText;
	for (size_t i = 0; i < str.size(); i++)
	{
		binaryText += std::bitset<8>(str[i]).to_string();
	}
	return binaryText;
}

void constructBlocks(std::vector<std::bitset<16>> &vec, const std::string plaintext,
	const int numberOfBlocks)
{
	std::string binaryPlainText;

	for (size_t i = 0; i < plaintext.size(); i++)
	{
		binaryPlainText += std::bitset<8>(plaintext[i]).to_string();
	}

	for (int j = 0; j < numberOfBlocks; j++)
	{
		vec.push_back(std::bitset<16>(binaryPlainText.substr((j*16), 16)));
	}
}

void constructBlocks2(std::vector<std::bitset<16>> &vec, const std::string plaintext,
	const int numberOfBlocks)
{
	for (int j = 0; j < numberOfBlocks; j++)
	{
		vec.push_back(std::bitset<16>(plaintext.substr((j*16), 16)));
	}
}

std::string ecb(const std::vector<std::bitset<16>> blocks, const std::bitset<16> key, const int numberOfBlocks)
{
	std::stringstream stream;
	for (int i = 0; i < numberOfBlocks; i++)
	{
		std::bitset<16> cipher = blocks[i] ^ key;
		std::cout << std::hex << blocks[i].to_ulong() << " XOR " << std::hex << key.to_ulong() << " = " << std::hex << cipher.to_ulong() << std::endl;

		stream << std::hex << cipher.to_ulong() << " ";
	}
	return stream.str();
}

std::string cbc(const std::vector<std::bitset<16>> blocks, const std::bitset<16> key, std::bitset<16> iv, const int numberOfBlocks)
{
	std::stringstream stream;
	for (int i = 0; i < numberOfBlocks; i++)
	{
		std::bitset<16> cipher = (blocks[i] ^ iv) ^ key;

		std::cout << "(" << std::hex << blocks[i].to_ulong() << " XOR " << 
		std::hex << iv.to_ulong() << ") XOR " << std::hex << key.to_ulong() <<
		" = " << std::hex << cipher.to_ulong() << std::endl;


		iv = cipher;
		stream << std::hex << cipher.to_ulong() << " ";
	}
	return stream.str();
}

std::string ofb(const std::vector<std::bitset<16>> blocks, const std::bitset<16> key, std::bitset<16> iv, const int numberOfBlocks)
{
	std::stringstream stream;
	for (int i = 0; i < numberOfBlocks; i++)
	{
		std::bitset<16> temp = (iv ^ key);
		std::bitset<16> cipher = temp ^ blocks[i];

		std::cout << "(" << std::hex << iv.to_ulong() << " XOR " << 
		std::hex << key.to_ulong() << ") XOR " << std::hex << blocks[i].to_ulong() <<
		" = " << std::hex << cipher.to_ulong() << std::endl;


		iv = temp;
		stream << cipher.to_string();
	}
	return stream.str();
}

void flipLastBitInBlockOne(std::string &str)
{
	if (str[15] == '1')
	{
		str[15] = '0';
	}
	else
	{
		str[15] = '1';
	}
}

int main()
{
	std::string plaintext = "DCS-3101";
	//std::string initializationVector = "NO";
	//std::string key = "EU";
	const int numberOfBlocks = ceil(plaintext.length() / 2.0);

	std::bitset<16> iv(binaryText("NO"));
	std::bitset<16> key(binaryText("EU"));
	std::vector<std::bitset<16>> blocks;
	constructBlocks(blocks, plaintext, numberOfBlocks);

	std::string ciphertext;

	ciphertext = ofb(blocks, key, iv, numberOfBlocks);
	std::cout << std::endl << "ciphertext: " << ciphertext << std::endl;

	std::vector<std::bitset<16>> blocks2;
	flipLastBitInBlockOne(ciphertext);
	std::cout << std::endl << "ciphertext: " << ciphertext << std::endl;
	constructBlocks2(blocks2, ciphertext, numberOfBlocks);


	ciphertext = ofb(blocks2, key, iv, numberOfBlocks);
	std::cout << std::endl << "ciphertext: " << ciphertext << std::endl;

}