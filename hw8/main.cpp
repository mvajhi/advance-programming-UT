#include "define.hpp"
#include "file_handle.hpp"
#include "question.hpp"

int main(int argc, char *argv[])
{
    // read_file(argv[FILE_PATH_INDEX_ARG]);
    Q_single_answer({1, "single_answer",
     {"2+2?", "4", "1", "2", "4", "IDK"}, "3"});
    return 0;
}