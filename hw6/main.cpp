#include "define.hpp"
#include "io_functions.hpp"
#include "manager.hpp"

int main()
{
    string line;
    Manager manager;

    while (getline(cin, line))
    {
        vector<string> separated_line = separate_line(line);
        // proccess
        string output = proccess(separated_line, manager);
        // output
        cout << output;
    }

    return 0;
}