#include <iostream>
#include <vector>
#include <string>

#define COUNT_DAY_SHOULD_TEACH 2
#define TIME_SIZE 5
#define HOUR_PER_MIN 60

using namespace std;

struct teacher
{
        string name;
        vector<string> lessons;
        vector<int> free_days;
};

struct lesson
{
        string name;
        vector<int> days_shoud_teach;
        int start_time;
        int end_time;
};

int input(vector<teacher> &teachers, vector<lesson> &lessons);
int day_stoi(string str_day);
int input_teachers(vector<teacher> &teachers);
int input_lessons(vector<lesson> &lessons);
int time_stoi(string time_str);

int main()
{
        // input
        vector<teacher> teachers;
        vector<lesson> lessons;
        input(teachers, lessons);
        return 0;
}

int input(vector<teacher> &teachers, vector<lesson> &lessons)
{

        input_teachers(teachers);
        input_lessons(lessons);
        return 0;
}

int day_stoi(string day)
{
        vector<string> week = {"Saturday", "Sunday", "Monday", "Tuesday",
                               "Wednesday", "Thusday", "Friday"};

        for (int i = 0; i < week.size(); i++)
                if (day == week[i])
                        return i;

        cout << "error day stoi\n";
        return -1;
}

int input_teachers(vector<teacher> &teachers)
{
        int teachers_count = 0;

        cin >> teachers_count;
        for (int i = 0; i < teachers_count; i++)
        {
                teacher new_teacher;
                int free_days_count = 0;
                int lessons_count = 0;
                cin >> new_teacher.name;
                cin >> free_days_count;
                for (int i = 0; i < free_days_count; i++)
                {
                        string new_day;
                        cin >> new_day;
                        new_teacher.free_days.push_back(day_stoi(new_day));
                }
                cin >> lessons_count;
                for (int i = 0; i < lessons_count; i++)
                {
                        string new_lesson;
                        cin >> new_lesson;
                        new_teacher.lessons.push_back(new_lesson);
                }
                teachers.push_back(new_teacher);
        }
        return 0;
}

int input_lessons(vector<lesson> &lessons)
{
        int lesson_count = 0;

        cin >> lesson_count;
        for (int i = 0; i < lesson_count; i++)
        {
                lesson new_lesson;
                
                cin >> new_lesson.name;

                for (int i = 0; i < COUNT_DAY_SHOULD_TEACH; i++)
                {
                        string new_day;
                        cin >> new_day;
                        new_lesson.days_shoud_teach.push_back(day_stoi(new_day));
                }

                string start_time_str;
                string end_time_str;
                cin >> start_time_str >> end_time_str;
                new_lesson.start_time = time_stoi(start_time_str);
                new_lesson.end_time = time_stoi(end_time_str);

                lessons.push_back(new_lesson);
        }
        return 0;
}

/*
input "hh:mm"
return hh * 60 + mm
*/
int time_stoi(string time_str)
{
        if (time_str.length() != TIME_SIZE)
                cout << "Invalid time input\n";
        int hour = stoi(time_str.substr(0, 2));
        int min = stoi(time_str.substr(3, 2));
        return hour * HOUR_PER_MIN + min;
}