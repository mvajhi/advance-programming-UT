#include "file_handle.hpp"

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

Question_input make_question(vector<string> question)
{
    string type = question.front();
    vector<string> question_body(question.begin() + 1, question.end() - 1);
    string answer = question.back();

    Question_input output = {type, question_body, answer};

    return output;
}

vector<Question_input> convert_to_questions_input(vector<vector<string>> questions)
{
    vector<Question_input> output;
    for (auto &&q : questions)
    {
        Question_input new_question = make_question(q);
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
