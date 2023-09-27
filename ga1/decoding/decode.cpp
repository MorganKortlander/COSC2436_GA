#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>
#include <regex>
#include <iterator>

using namespace std;

/* //plan: find a ( then trigger another call if a ( is found before a ).

overload function to accept iterator, so that can be passed in
 */
std::string decode(std::string &toDec)
{

    auto opening = '(';
    auto closing = ')';
    std::string::iterator itFirst = std::find_if(toDec.begin(), toDec.end(), [opening](auto i){ return i == opening });

    if (itFirst != toDec.end())
    {
        std::string::iterator itFirst = std::find_if(toDec.begin(), toDec.end(), [opening](auto i){ return i == opening });
        std::string::iterator itr2 = decode(toDec, itr); // first try not as reference
        std::string::iterator itrSecond = find ')';
    }
    for (i = itr1)

    for (std::string::iterator itr = 
    replace "(stuff)" with "ffuts" in situ 
    return toDec;
} // notes: get iterator for the range, remove ( ) then use std::reverse then use std::string.replace to replace old substring with the fixed one

void decode(std::string &part, std::string::iterator itr)
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
    std::ifstream inFile("input1.txt");
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
    }
}

void example(std::string perm)
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
}

std::string maxPerm(std::string perm, int count = 0) //
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
}