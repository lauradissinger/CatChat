// CatChat.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>

using namespace std;

bool AppendCharacter(string& resultString, char charToAppend)
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

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        cout << "Usage: CatChat <message to convert>\n";
        return 0;
    }

    string resultString;
    int wordIndex = 1;
    while (wordIndex < argc)
    {
        char* nextChar = argv[wordIndex];
        while (*nextChar != '\0')
        {
            if (!AppendCharacter(resultString, *nextChar))
            {
                return 1;
            }
            ++nextChar;
        }

        if (wordIndex + 1 < argc)
        {
            // Add a space
            AppendCharacter(resultString, ' ');
        }

        ++wordIndex;
    }

    cout << "Resulting CatChat:\n" << resultString << "\n";

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
