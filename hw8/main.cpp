#include "define.hpp"
#include "io_functions.hpp"
#include "manager.hpp"
#include "reporter.hpp"

int main(int argc, char *argv[])
{
    string line;
    Manager manager(read_file(argv[FILE_PATH_INDEX_ARG]));

    while (getline(cin, line) && !manager.is_end())
    {
        // input
        vector<string> separated_line = separate_line(line);
        // proccess
        vector<shared_ptr<Reporter>> reports = command_proccess(separated_line, manager);
        // output
        print_report_CLI(reports);
    }
    return 0;
}