// CatChat.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>

using namespace std;

bool EncodeCharacter(string& resultString, char charToAppend)
{
    char ebcdicValue = 0;
    if (charToAppend >= 'A' && charToAppend <= 'I')
    {
        ebcdicValue = 0xC1 + (charToAppend - 'A');
    }
    else if (charToAppend >= 'J' && charToAppend <= 'R')
    {
        ebcdicValue = 0xD1 + (charToAppend - 'J');
    }
    else if (charToAppend >= 'S' && charToAppend <= 'Z')
    {
        ebcdicValue = 0xE2 + (charToAppend - 'S');
    }
    else if (charToAppend >= 'a' && charToAppend <= 'i')
    {
        ebcdicValue = 0x81 + (charToAppend - 'a');
    }
    else if (charToAppend >= 'j' && charToAppend <= 'r')
    {
        ebcdicValue = 0x91 + (charToAppend - 'j');
    }
    else if (charToAppend >= 's' && charToAppend <= 'z')
    {
        ebcdicValue = 0xA2 + (charToAppend - 's');
    }
    else if (charToAppend >= '0' && charToAppend <= '9')
    {
        ebcdicValue = 0xF0 + (charToAppend - '0');
    }
    else if (charToAppend == ' ')
    {
        ebcdicValue = 0x40;
    }
    else
    {
        cout << "Character not handled: " << charToAppend << "\n";
        return false;
    }

    for (int i = 7; i >= 0; --i)
    {
        if ((ebcdicValue >> i) & 1)
        {
            resultString.append("CAT");
        }
        else
        {
            resultString.append("cat");
        }
    }
    return true;
}

bool DecodeString(string& resultString, char** catStringPtr)
{
    if (catStringPtr == nullptr || *catStringPtr == nullptr)
    {
        cout << "Invalid pointer\n";
        return false;
    }

    unsigned char ebcdicValue = 0;
    char charToAppend = 0;

    for (int i = 7; i >= 0; --i)
    {
        if (strncmp(*catStringPtr, "CAT", 3) == 0)
        {
            ebcdicValue |= (1 << i);
        }
        else if (strncmp(*catStringPtr, "cat", 3) == 0)
        {
            // no-op
        }
        else
        {
            cout << "Invalid input, needs to be CAT or cat\n";
            return false;
        }
        *catStringPtr += 3;
    }

    if (ebcdicValue >= 0xC1 && ebcdicValue <= 0xC9)
    {
        charToAppend = 'A' + (ebcdicValue - 0xC1);
    }
    else if (ebcdicValue >= 0xD1 && ebcdicValue <= 0xD9)
    {
        charToAppend = 'J' + (ebcdicValue - 0xD1);
    }
    else if (ebcdicValue >= 0xE2 && ebcdicValue <= 0xE9)
    {
        charToAppend = 'S' + (ebcdicValue - 0xE2);
    }
    else if (ebcdicValue >= 0x81 && ebcdicValue <= 0x89)
    {
        charToAppend = 'a' + (ebcdicValue - 0x81);
    }
    else if (ebcdicValue >= 0x91 && ebcdicValue <= 0x99)
    {
        charToAppend = 'j' + (ebcdicValue - 0x91);
    }
    else if (ebcdicValue >= 0xA2 && ebcdicValue <= 0xA9)
    {
        charToAppend = 's' + (ebcdicValue - 0xA2);
    }
    else if (ebcdicValue >= 0xF0 && ebcdicValue <= 0xF9)
    {
        charToAppend = '0' + (ebcdicValue - 0xF0);
    }
    else if (ebcdicValue == 0x40)
    {
        charToAppend = ' ';
    }
    else
    {
        cout << "Character not handled: " << charToAppend << "\n";
        return false;
    }

    resultString.append(1, charToAppend);

    return true;
}

int main(int argc, char* argv[])
{
    if (argc < 3)
    {
        cout << "Usage: CatChat encode <message to encode>\n";
        cout << "Usage: CatChat decode <message to decode>\n";
        return 0;
    }

    if (_stricmp(argv[1], "encode") == 0)
    {
        string resultString;
        int wordIndex = 2;
        while (wordIndex < argc)
        {
            char* nextChar = argv[wordIndex];
            while (*nextChar != '\0')
            {
                if (!EncodeCharacter(resultString, *nextChar))
                {
                    return 1;
                }
                ++nextChar;
            }

            if (wordIndex + 1 < argc)
            {
                // Add a space
                EncodeCharacter(resultString, ' ');
            }

            ++wordIndex;
        }

        cout << "Resulting CatChat:\n" << resultString << "\n";
    }
    else if (_stricmp(argv[1], "decode") == 0)
    {
        string resultString;
        char* catStringPtr = argv[2];
        while (catStringPtr[0] != '\0')
        {
            if (!DecodeString(resultString, &catStringPtr))
            {
                return 1;
            }
        }

        cout << "Resulting CatChat:\n" << resultString << "\n";
    }
    else
    {
        cout << "Unrecognized command: " << argv[1] << "\n";
        return 1;
    }

    return 0;
}
