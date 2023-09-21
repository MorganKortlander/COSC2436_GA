#include "ArgumentManager.h" //<map> <string> <iostream> <sstream>
#include <fstream>
#include "LL.h"


// check that 2 files opened correctly
bool filesOpened(std::ifstream &ifs, std::ofstream &ofs);
// check that 3 files opened correctly
bool filesOpened(std::ifstream &ifs, std::ofstream &ofs, std::ifstream &cmd);

int main(int argc, char *argv[])
{
    ArgumentManager am(argc, argv);

    // Re-enable before submission

    std::ifstream ifs(am.get("input"));
    std::ofstream ofs(am.get("output"));
    std::ifstream cmd(am.get("command"));
    

    // local testing (hardcoding filenames)

    /* std::ifstream ifs("input2.txt");
    std::ofstream ofs("output2.txt");
    std::ifstream cmd("command2.txt");
    std::ofstream log("log2.txt"); */

    // no command file included
    /* if (!filesOpened(ifs, ofs, cmd))
    {
        return 1;
    } */

    // command file included
    if (!filesOpened(ifs, ofs, cmd))
    {
        return 1;
    }
    else
    {
        std::string inStr;
        LL clients;

        // read in input file
        while (std::getline(ifs >> std::ws, inStr))
        {
            //containers for receiving credentials
            std::string name = "";
            
            std::map<std::string, int> cred;
            cred["age:"] = 0;
            cred["deposit:"] = 0;
            cred["number"] = 0;

            std::stringstream ss(inStr);

            /* std::cout << name << std::endl; */
            while (!(ss >> std::ws).eof())
            {
                std::string attribute = "";
                std::string val = "";
                ss >> attribute >> std::ws;
                if (attribute == "number")
                {
                    std::string waste;
                    ss >> waste >> std::ws;
                    ss >> waste >> std::ws;
                }

                ss >> val >> std::ws;

                val.erase(remove(val.begin(), val.end(), ';'), val.end());
                val.erase(remove(val.begin(), val.end(), ']'), val.end());

                if (attribute == "[name:")
                    name = val;
                else
                    cred[attribute] = stoi(val);
            }
            clients.addNew(
                name,
                cred["age:"],
                cred["deposit:"],
                cred["number"]);
        }

        ifs.close();

        // read in cmd file
        while (getline(cmd >> std::ws, inStr))
        {
            std::string command = "";
            std::stringstream ss(inStr);
            ss >> command >> std::ws;
            //cout << command << endl;
            std::string directive;
            ss >> directive >> std::ws;
            //cout << directive << endl;
            directive.erase(0, 1); // eliminate parenthesis
            if (command == "Add")
            {
                std::string indexStr = directive;
                
                cout << indexStr << endl;
                indexStr.pop_back(); // eliminate parenthesis
                cout << indexStr << endl;
                int indexInt = stoi(indexStr);

                std::string name = "";
                std::map<std::string, int> cred;
                cred["age:"] = 0;
                cred["deposit:"] = 0;
                cred["number of drinks:"] = 0;
                // take in attributes
                while (!(ss >> std::ws).eof())
                {
                    std::string attribute = "";
                    std::string val = "";
                    ss >> attribute >> std::ws;
                    std::cout << "Attribute read: " << attribute << std::endl;
                    if (attribute == "number")
                    {
                        std::string waste;
                        ss >> waste >> std::ws;
                        ss >> waste >> std::ws;
                    }

                    ss >> val >> std::ws;
                    val.erase(remove(val.begin(), val.end(), ';'), val.end());
                    val.erase(remove(val.begin(), val.end(), ']'), val.end());
                    std::cout << "Cleaned Val: " << val << std::endl;

                    if (attribute == "[name:")
                        name = val;
                    else
                        cred[attribute] = stoi(val);
                }
                clients.Add(
                    indexInt,
                    name,
                    cred["age:"],
                    cred["deposit:"],
                    cred["number"]);
            }
            else if (command == "Remove")
            {
                if (directive == "number")
                {
                    std::string waste;
                    ss >> waste >> std::ws;
                    ss >> waste >> std::ws;
                }
                else
                    directive.pop_back();
                std::string val;
                ss >> val;
                val.pop_back();

                clients.Remove(directive, val);
            }
            else if (command == "Sort")
            {
                if (directive != "number")
                    directive.pop_back();
                cout << "Directive is " << directive << endl;
                clients.getaddr();
                clients.Sort(directive);
                //clients.Sort(directive,&log);
            }
        }
        cmd.close();
        // debugging
        // log.close();
        clients.outputNodes(ofs);

        ofs.close();
    }
    return 0;
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

/* potential solutions for whitepsace issues. getline() ends at a newline character, but can pick up leading whitespace. Using
getline(stream >> std::ws, thestring) seems to solve it, though.
 */
/* inStr.erase(remove(inStr.begin(), inStr.end(), '\n'), inStr.end());

inStr.erase(remove(inStr.begin(), inStr.end(), '\r'), inStr.end()); */