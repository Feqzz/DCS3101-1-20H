#include <iostream>
#include <string>

std::string vigenereEncrypt(std::string plaintext, std::string key)
{
	char tmp[plaintext.size()];
	int outOfBoundsCharacters = 0;
	for (int i = 0; i < plaintext.size(); i++)
	{
		bool isLowerCaseInput;
		bool isLowerCaseKey;
		if (static_cast<int>(plaintext[i]) > 64 && static_cast<int>(plaintext[i]) < 91)
		{
			isLowerCaseInput = false;
		}
		else if (static_cast<int>(plaintext[i]) > 96 && static_cast<int>(plaintext[i]) < 123)
		{
			isLowerCaseInput = true;
		}
		else
		{
			tmp[i] = plaintext[i];
			outOfBoundsCharacters++;
			continue;
		}

		const int keyIndex = (i - outOfBoundsCharacters) % key.length();

		if (static_cast<int>(key[keyIndex]) > 64 && static_cast<int>(key[keyIndex]) < 91)
		{
			isLowerCaseKey = false;
		}
		else if (static_cast<int>(key[keyIndex]) > 96 && static_cast<int>(key[keyIndex]) < 123)
		{
			isLowerCaseKey = true;
		}
		else
		{
			std::cout << "The key is illegal! Only alphabet characters are allowed." << std::endl;
			exit(1);
		}

		const int asciiGapInput = isLowerCaseInput ? 97 : 65;
		const int asciiGapKey = isLowerCaseKey ? 97 : 65;

		const int indexInAlphabetInput = static_cast<int>(plaintext[i]) - asciiGapInput;
		const int indexInAlphabetKey = static_cast<int>(key[keyIndex]) - asciiGapKey;

		tmp[i] = static_cast<char>(((indexInAlphabetInput + indexInAlphabetKey) % 26) + asciiGapInput);
	}
	return tmp;
}

void printUsage()
{
	std::cout << "Usage: ./vigenere <text> <key1> ... <key N>" << std::endl;
}

int main(int argc, char** argv)
{
	if (argc < 3)
	{
		printUsage();
		exit(1);
	}

	std::string text = argv[1];

	for (int i = 0; i < (argc - 2); i++)
	{
		const std::string key = argv[i + 2];
		text = vigenereEncrypt(text, key);
	}

	std::cout << text << std::endl;
	return 0;
}