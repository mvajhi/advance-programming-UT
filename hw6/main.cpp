#include "define.hpp"
#include "io_functions.hpp"

int main()
{
    string line;

    while (getline(cin, line))
    {
        vector<string> separated_line = separate_line(line);
        // proccess
        // output
    }

    return 0;
}