#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>
#include <regex>
#include <cstdio>

using namespace std;

/* //plan: find a ( then trigger another call if a ( is found before a ).

overload function to accept iterator, so that can be passed in
 */
std::string decode(std::string &toDec)
{

    char opening = '(';
    char closing = ')';
    std::string::iterator itFirst = std::find_if(toDec.begin(), toDec.end(), [opening](char i){ return i == opening;});

    if (itFirst != toDec.end())
    {
        std::string::iterator itFirst = std::find_if(toDec.begin(), toDec.end(), [opening](auto i){ return i == opening });
        std::string::iterator itr2 = decode(toDec, itr);
        std::string::iterator itrSecond = find ')';
    }
    for (i = itr1)

    for (std::string::iterator itr = 
    replace "(stuff)" with "ffuts" in situ 
    return toDec;
} // notes: get iterator for the range, remove ( ) then use std::reverse then use std::string.replace to replace old substring with the fixed one

std::string::iterator decode(std::string &part, std::string::iterator itr)
{

    /* std::string::iterator itr1 = std::find_if(toDec.begin) _, toDec.end() '(';
    if (itr != end)
    {
    decode(&itr)
    }

    std::string::iterator itr2 = find ')';
    for (std::string::iterator itr =
    replace "(stuff)" with "ffuts" in situ  */
}

int main()
{
    freopen("myOutput.txt", "w", stdout);
    
}