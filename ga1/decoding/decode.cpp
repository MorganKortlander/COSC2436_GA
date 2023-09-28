#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <iostream>
#include <cstdio>

// check that 2 files opened correctly--function is defined below main
bool filesOpened(std::ifstream &ifs, std::ofstream &ofs);
// check that 3 files opened correctly--function is defined below main
bool filesOpened(std::ifstream &ifs, std::ofstream &ofs, std::ifstream &cmd);

// Overload that accepts a string and an iterator from its first instance of a '('. Since the string in this overloaded function is a reference, any changes made during recursive calls should carry over
void decode(std::string &toDec, std::string::iterator previous)
{
    char openChar = '(';
    char closeChar = ')';

    // find opening (, if any left
    std::string::iterator opening = std::find_if(previous + 1, toDec.end(), [openChar](char i)
                                                 { return i == openChar; });
    if (opening != toDec.end())
    {
        decode(toDec, opening);
    }
    // find closing )
    std::string::iterator closing = std::find_if(previous + 1, toDec.end(), [closeChar](char i)
                                                 { return i == closeChar; });
    opening = previous;
    std::string toReverse(opening + 1, closing);
    std::reverse(toReverse.begin(), toReverse.end());
    toDec.replace(opening, closing + 1, toReverse);

}

// Base function that accepts a string to decode. Should make a local copy of the string. Calls the overloaded version if it finds a '('
std::string decode(std::string toDec)
{
    char openChar = '(';
    char closeChar = ')';

    // find opening (, if any
    std::string::iterator opening = std::find_if(toDec.begin(), toDec.end(), [openChar](char i)
                                                 { return i == openChar; });
    if (opening != toDec.end())
    {
        decode(toDec, opening);
    }
    return toDec;
}
// notes: gets iterator for the range, remove ( ) then use std::reverse then use std::string.replace to replace old substring with the fixed one

int main()
{
    freopen("myOutput.txt", "w", stdout);

    /* std::string testString = "(as)dbig(god)s"; // should be "sadbigdogs"
    std::string decoded = decode(testString);
    std::cout << decoded << std::endl; */
    std::ifstream inFile("input1.txt");
    std::ofstream ofs("output1.txt");

    std::string line = "";
    std::string barName = ""; // need to preserve barname between loops
    if (!filesOpened(inFile, ofs))
    {
        std::cerr << "Bad read" << std::endl;
        return 1;
    }

    while (getline(inFile >> std::ws, line))
    {
        // >> std::ws eats white space before inserting to string. No need for removal lines!
        std::cout << "Read in " << line << std::endl;
        // receive bar
        std::string encodedID = "";
        std::string decodedID = "";
        if (line == "Bar1" || line == "Bar2")
        {
            barName = line;
            std::cout << "Detected " << line << std::endl;
            continue; // restart loop with current bar
        }
        // edge case: no bar given yet, or emtpy
        else if (line == "")
        {
            std::cerr << "No bar!" << std::endl;
            return 1;
        }
        else
        {
            decodedID = decode(line);
            std::cout << "read in " << line << " and decoded as " << decodedID << std::endl;
        }
    }
}

bool filesOpened(std::ifstream &ifs, std::ofstream &ofs)
{
    bool opened = true;
    if (!ofs.is_open())
    {
        std::cerr << "failed to open output file." << std::endl;
        opened = false;
        ofs.close();
    }
    if (!ifs.is_open())
    {
        std::cerr << "failed to open input file." << std::endl;
        opened = false;
        ifs.close();
    }
    return opened;
}

bool filesOpened(std::ifstream &ifs, std::ofstream &ofs, std::ifstream &cmd)
{
    bool opened = true;
    if (!ofs.is_open())
    {
        std::cerr << "failed to open output file." << std::endl;
        opened = false;
        ofs.close();
    }
    if (!ifs.is_open())
    {
        std::cerr << "failed to open input file." << std::endl;
        opened = false;
        ifs.close();
    }
    if (!cmd.is_open())
    {
        std::cerr << "failed to open command file." << std::endl;
        opened = false;
        cmd.close();
    }
    return opened;
}