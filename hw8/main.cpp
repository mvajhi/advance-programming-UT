#include "define.hpp"
#include "file_handle.hpp"
#include "question.hpp"
#include "reporter.hpp"

int main(int argc, char *argv[])
{
    // read_file(argv[FILE_PATH_INDEX_ARG]);
    Question_input in = {1, "multiple_answer",
     {"prime numbers below 5?"
     , "4", "1", "2", "4", "3"}, "2 4"};
    shared_ptr<Question> q = make_shared<Q_multiple_answer>(in);
    
    // q->set_user_ans("4 4");
    Question_reporter r(q);
    cout << r.get_cli_short_report();
    cout << r.get_cli_full_report();
    return 0;
}