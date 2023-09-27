#include <iostream>
#include <string>


int main()
{
    std::string t1 = "12345abcd";
    std::string::iterator itB = t1.begin() + 3;
    std::string::iterator itE = t1.end() - 4;
    // iterator std::distance shows 2
    std::cout << std::distance(itB, itE);
    // Problem line
    t1.replace(t1.begin() + 5, t1.begin() + 7, "%abcdefghijklm%");
}