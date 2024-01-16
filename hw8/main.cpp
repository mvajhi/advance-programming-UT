#include "define.hpp"
#include "file_handle.hpp"
#include "question.hpp"
#include "reporter.hpp"

int main(int argc, char *argv[])
{
    // read_file(argv[FILE_PATH_INDEX_ARG]);
    Question_input in = {1, "short_answer",
     {"What is a prime number?"},
      "A_number_that_is_divisible_only_by_itself_and_1"};
    shared_ptr<Question> q = make_shared<Q_short_answer>(in);

    // q->set_user_ans("A_number_that_is_divisible_only_by_itself_and_1");
    Question_reporter r(q);
    cout << r.get_cli_short_report();
    cout << r.get_cli_full_report();
    return 0;
}