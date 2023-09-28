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
// notes: get iterator for the range, remove ( ) then use std::reverse then use std::string.replace to replace old substring with the fixed one

/* std::string::iterator itr1 = std::find_if(toDec.begin) _, toDec.end() '(';
if (itr != end)
{
decode(&itr)
}

std::string::iterator itr2 = find ')';
for (std::string::iterator itr =
replace "(stuff)" with "ffuts" in situ  */

int main()
{
    freopen("myOutput.txt", "w", stdout);
    string toDec = "(1234)";
    char openChar = '(';
    char closeChar = ')';

    //find opening (
    std::string::iterator opening = std::find_if(toDec.begin(), toDec.end(), [openChar](char i){ return i == openChar; });

    //find closing )
    std::string::iterator closing = std::find_if(toDec.begin(), toDec.end(), [closeChar](char i){ return i == closeChar; });
    
    // pull out part to be reversed. Closing is technically a "beginning" iterator, so it doesn't need +1, since "ending iterators" are expected go one element past the last one.
    std::string toReverse(opening+1,closing);
    cout<<toReverse<<endl;
    std::reverse(toReverse.begin(),toReverse.end());
    cout<<toReverse<<endl;
    //stick it back in
    toDec.replace(opening,closing+1,toReverse);
    cout << toDec << endl;

    //confirmed: iterator returned will simply start at that point
    //cout << *(itFirst+1) << endl;
    /*     if (itFirst != toDec.end())
        {
            std::string::iterator itFirst = std::find_if(toDec.begin(), toDec.end(), [opening](auto i){ return i == opening });
            std::string::iterator itr2 = decode(toDec, itr);
            std::string::iterator itrSecond = find ')';
    } */
}