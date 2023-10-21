#include "ArgumentManager.h" //<map> <string> <iostream> <sstream>
#include <fstream>
// #include "header.h"

// beautful code
// it's working!!!

int main(int argc, char *argv[])
{
    ArgumentManager am(argc, argv);

    // Re-enable before submission
   /*
   ifstream ifs(am.get("input"));
   ofstream ofs(am.get("output"));
   ifstream cmd(am.get("command"));
   */

    // local testing (hardcoding filenames)
    
    std::ifstream ifs("input1.txt");
    std::ofstream ofs("output1.txt");
    std::ifstream cmd("command1.txt");
   
    // debugging for opening files
    /*if (ofs.is_open() == true)
        std::cout << "ofs is open" << std::endl;
    if (ifs.is_open() == true)
        std::cout << "ifs is open" << std::endl;
        std::cout << "Remove me after testing on server!" << std::endl;*/
    if (cmd.is_open() != true)
        {
        std::cout << "failed to open command file. Exiting..." << std::endl;
        return 1;
    }
    if (ofs.is_open() != true)
    {
        std::cout << "failed to open output file. Exiting..." << std::endl;
        return 1;
    }

    if (ifs.is_open() == true)
    {
        // std::cout << "ifs is open" << std::endl;

        while (!(ifs >> std::ws).eof()) // FIXME use getline this time
        {
            // std::string fillString = "";
            // std::cout << "Looping with " << inStr << std::endl;
            // input >> inStr;
            // newStr += fillString;
            // std::cout << "before erase " << inStr << std::endl;
            // inStr.erase(remove(inStr.begin(), inStr.end(), '\n'), inStr.end());
            // inStr.erase(remove(inStr.begin(), inStr.end(), '\r'), inStr.end()); // some computers interpret return key as return carriage
            // std::cout << "after erase " << inStr << std::endl;

            // std::cout << '\n' << count << " command read: " << cmd << std::endl;
            
            /* switch (operation)
            {
            case 'P':
                // std::cout << "Call print" << std::endl;
                myList.printAt(position, ofs);
                break;
            case 'I':
                // std::cout << "Call insert" << std::endl;
                myList.insertAt(position, ifs);
                break;
            case 'R':
                // std::cout << "Call remove" << std::endl;
                myList.removeAt(position);
                break;
            default:
                std::cout << "Invalid command: " << cmd << std::endl;
            } */
        }
    }
    else
    {
        std::cout << "failed to open input file. Exiting..." << std::endl;
        return 1;
    }

    ifs.close();
    ofs.close();
    return 0;
}