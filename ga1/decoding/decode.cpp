#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>
#include <regex>
#include <cstdio>

/* //plan: find a ( then trigger another call if a ( is found before a ).

overload function to accept iterator, so that can be passed in IF there are parentheses
 */

// Overload that accepts a string and an iterator from its first instance of a '('. Since the string in this overloaded function is a reference, any changes made during recursive calls should carry over
void decode(std::string &toDec, std::string::iterator previous)
{
    char openChar = '(';
    char closeChar = ')';

    // find opening (, if any left
    std::string::iterator opening = std::find_if(previous+1, toDec.end(), [openChar](char i)
                                                 { return i == openChar; });
    if (opening != toDec.end())
    {
        decode(toDec, opening);
    }

    // find closing )
    std::string::iterator closing = std::find_if(previous+1, toDec.end(), [closeChar](char i)
                                                 { return i == closeChar; });

    // pull out part to be reversed. Variable closing is technically a "beginning" iterator, so it doesn't need +1, since "ending iterators" are expected go one element past the last one !!!.
    opening = previous;
    std::cout << "String before: " << toDec << std::endl;
    std::string toReverse(opening + 1, closing);
    std::cout << "Going to reverse: " << toReverse << std::endl;
    std::reverse(toReverse.begin(), toReverse.end());
    std::cout << "Reverse out: " << toReverse << std::endl;

    // stick it back in, overwriting where there was ( ). !!! now we have the opposite situation with needing the +1 on closing, instead of opening.

    toDec.replace(opening, closing + 1, toReverse);
    std::cout << "String after replacement: " << toDec << std::endl;
}

// Base function that accepts a string to decode. Should make a local copy of the string. Calls the overloaded version if it finds a '('
std::string decode(std::string &toDec)
{
    char openChar = '(';
    char closeChar = ')';

    // find opening (
    std::string::iterator opening = std::find_if(toDec.begin(), toDec.end(), [openChar](char i)
                                                 { return i == openChar; });
    if (opening != toDec.end())
    {
        decode(toDec, opening);
        /* std::string::iterator closing = std::find_if(opening, toDec.end(), [closeChar](char i)
                                                     { return i == closeChar; });

        // pull out part to be reversed. Variable closing is technically a "beginning" iterator, so it doesn't need +1, since "ending iterators" are expected go one element past the last one !!!.

        std::cout << "String before: " << toDec << std::endl;
        std::string toReverse(opening + 1, closing);
        std::cout << "Going to reverse: " << toReverse << std::endl;
        std::reverse(toReverse.begin(), toReverse.end());
        std::cout << "Reverse out: " << toReverse << std::endl;

        // stick it back in, overwriting where there was ( ). !!! now we have the opposite situation with needing the +1 on closing, instead of opening.

        toDec.replace(opening, closing + 1, toReverse);
        std::cout << "String after replacement: " << toDec << std::endl; */
    }
    return toDec;
}
// notes: get iterator for the range, remove ( ) then use std::reverse then use std::string.replace to replace old substring with the fixed one

int main()
{
    freopen("myOutput.txt", "w", stdout);

    std::string testString = "(as)dbig(god)s"; // should be "sadbigdogs"
    std::string decoded = decode(testString);
    std::cout << decoded << std::endl;
    return 0;
    /* std::ifstream inFile("input1.txt");
    std::ofstream ofs("output1.txt");

    std::string line = "";
    std::string barName; // need to preserve barname between loops

    while (getline(inFile >> std::ws, line))
    {
        // >> std::ws eats white space before inserting to string, no need for removal lines

        // receive bar
        if (line == "Bar1" || line == "Bar2")
        {
            barName = line;
            break; // restart loop with current bar
        }
        // edge case: no bar given yet, or emtpy
        else if (line == "")
            break;

        string encodedID = "";
        string decodedID = "";
    } */
}

/* void example(std::string perm)
{ // example reverse iteration
    std::string newPerm = "";
    if (perm.size() < 2)
    {
    std::cout << "string size is < 2. Only one permutation" << std::endl;
    return perm;
    }
    // base case 2: enough numbers but not already ordered
    char swap = '0'; // domain is given as 0 to 10 not inclusive, so 0 won't appear in input file

    // experiment with iterators in loop. str.end() points to address 1 over from last index, so use it+1 to compare location

    // can reduce time by adding a passcount that reduces the checks by 1 each call following first, since each pass places the correct element at the end position

    for (std::string::iterator it = perm.end() - 1; (it) != perm.begin(); --it)
    {
    std::cout << "Checking " << *it << " and " << *(it - 1) << std::endl;
    if (*it > *(it - 1))
    {
        swap = *it;
        *it = *(it - 1);
        *(it - 1) = swap;
    }
    }
} */

/* std::string maxPerm(std::string perm, int count = 0) //
{

    // sentry value
    if (count > 1000)
    {
    std::cout << "Exceeded 1000 iterations. Exiting with error" << std::endl;
    exit(EXIT_FAILURE);
    }
    // base case 1: 1 or fewer numbers; no change needed
    std::string newPerm = "";
    if (perm.size() < 2)
    {
    std::cout << "string size is < 2. Only one permutation" << std::endl;
    return perm;
    }
    // base case 2: enough numbers but not already ordered
    char swap = '0'; // domain is given as 0 to 10 not inclusive, so 0 won't appear in input file

    // experiment with iterators in loop. str.end() points to address 1 over from last index, so use it+1 to compare location

    // can reduce time by adding a passcount that reduces the checks by 1 each call following first, since each pass places the correct element at the end position
    for (std::string::iterator it = perm.begin(); (it + 1) != perm.end(); ++it)
    {
    std::cout << "Checking " << *it << " and " << *(it + 1) << std::endl;
    if (*it < *(it + 1))
    {
        swap = *it;
        *it = *(it + 1);
        *(it + 1) = swap;
    }
    }
    std::cout << "Current perm: " << perm << std::endl;
    // case 3: no change happened, swap still = '0'
    if (swap == '0')
    return perm;
    count++;
    // case 4: change happened, check again
    return maxPerm(perm, count);
} */