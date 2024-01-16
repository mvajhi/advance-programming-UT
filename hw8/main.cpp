#include "define.hpp"
#include "file_handle.hpp"
#include "question.hpp"
#include "reporter.hpp"

int main(int argc, char *argv[])
{
    // read_file(argv[FILE_PATH_INDEX_ARG]);
    Question_input in = {1, "single_answer",
     {"2+2?", "4", "1", "2", "4", "IDK"}, "3"};
    shared_ptr<Question> q = make_shared<Q_single_answer>(in);
    q->set_user_ans("1");
    Question_reporter r(q);
    cout << r.get_cli_short_report();
    cout << r.get_cli_full_report();
    return 0;
}