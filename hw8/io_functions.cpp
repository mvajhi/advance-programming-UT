#include "io_functions.hpp"

vector<string> read_file_line(string file_path)
{
    ifstream file(file_path);
    string line;
    vector<string> output;
    while (getline(file, line))
        output.push_back(line);
    file.close();
    return output;
}

vector<vector<string>> divide_into_questions(vector<string> lines)
{
    vector<vector<string>> questions;
    vector<string> new_question;
    for (auto &&line : lines)
        if (line != "#")
            new_question.push_back(line);
        else
        {
            questions.push_back(new_question);
            new_question.clear();
        }

    if (new_question.size() > 0)
        questions.push_back(new_question);

    return questions;
}

Question_input make_question(vector<string> question, int number)
{
    string type = question.front();
    vector<string> question_body(question.begin() + 1, question.end() - 1);
    string answer = question.back();

    Question_input output = {number, type, question_body, answer};

    return output;
}

vector<Question_input> convert_to_questions_input(vector<vector<string>> questions)
{
    vector<Question_input> output;
    for (size_t i = 0; i < questions.size(); i++)
    {
        Question_input new_question = make_question(questions[i], i + 1);
        output.push_back(new_question);
    }

    return output;
}

vector<Question_input> read_file(string file_path)
{
    vector<string> lines = read_file_line(file_path);
    vector<vector<string>> questions = divide_into_questions(lines);
    vector<Question_input> output = convert_to_questions_input(questions);
    return output;
}

vector<string> separate_line(string line)
{
    vector<string> result;
    istringstream iss(line);
    string token;
    
    for (int i = 0; i < 2 && getline(iss, token, ' '); i++)
        result.push_back(token);
    
    while (getline(iss, token))
        result.push_back(token);

    return result;
}

Submit_input convert_to_submit(vector<string> input)
{
    return Submit_input({stoi(input[1]), input[2]});
}

vector<shared_ptr<Reporter>> command_proccess(vector<string> input, Manager &manager)
{
    vector<shared_ptr<Reporter>> output;
    if (input[0] == CLI_END)
        manager.end_quiz();
    if (input[0] == CLI_SUBMIT)
        output.push_back(manager.submit(convert_to_submit(input)));
    if (manager.is_end())
        output.push_back(manager.get_end_report());
    return output;
        
}

void print_report_CLI(vector<shared_ptr<Reporter>> reports)
{
    for (auto &&r : reports)
        cout << r->get_cli_report();
}
