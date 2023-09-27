#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>
#include <regex>

using namespace std;

std::string decode(std::string &toDec)
{
    
}

int main()
{
    std::ifstream inFile("input1.txt");
    std::ofstream ofs("output1.txt");

    std::string line="";
    std::string barName; // need to preserve barname between loops

    while (getline(inFile >> std::ws, line))
    {
        // >> std::ws eats white space before inserting to string, no need for removal lines

        //receive bar
        if (line == "Bar1" || line == "Bar2")
        {
            barName = line;
            break; // restart loop with current bar
        }
        //case: no bar given yet
        else if (line=="")
            break;
        
        string encodedID = "";
        string decodedID = "";
    }