#include "define.hpp"
#include "io_functions.hpp"
#include "reporter.hpp"

int main()
{
    string line;
    Manager manager;

    import_files(manager);

    while (getline(cin, line))
    {
        // input
        vector<string> separated_line = separate_line(line);
        // proccess
        shared_ptr<Reporter> report = proccess(separated_line, manager);
        // output
        report->cli_report();
    }

    return 0;
}