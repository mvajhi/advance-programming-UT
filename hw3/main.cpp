#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

#define COUNT_DAY_SHOULD_TEACH 2
#define TIME_SIZE 5
#define HOUR_PER_MIN 60
#define START_SCHOOL_STR "07:30"
#define END_SCHOOL_STR "13:00"
#define BREAK_TIME_STR "00:30"
#define CLASS_TIME_STR "01:30"
#define START_WEEK_STR "Saturday"
#define END_WEEK_STR "Wednesday"
#define NUMBER_OF_CLASS 2

using namespace std;

struct schedule_part;

struct teacher
{
        string name;
        vector<string> lessons;
        vector<int> free_days;
        vector<schedule_part> busy_time;
        // TODO save busy time per day
};

struct lesson
{
        string name;
        vector<int> days_shoud_teach;
        int start_time;
        int end_time;
};

struct schedule_part
{
        int week_day;
        int start_time;
        int end_time;
        lesson this_time_lesson;
        teacher this_time_teacher;
};

int input(vector<teacher> &teachers, vector<lesson> &lessons);
int day_stoi(string str_day);
int input_teachers(vector<teacher> &teachers);
int input_lessons(vector<lesson> &lessons);
int time_stoi(string time_str);
int create_schedule_for_school(vector<schedule_part> *schedules, vector<teacher> &teachers, vector<lesson> &lessons);
int create_schedule_for_class(vector<teacher> &teachers, vector<lesson> &lessons,
                              vector<schedule_part> &schedule);
vector<pair<lesson, teacher>> sorted_available_lessons_with_teachers_list(vector<teacher> teachers, vector<lesson> lessons, int day, int time);
vector<lesson> find_lessons_with_time(int day, int time, vector<lesson> lessons);
vector<pair<lesson, teacher>> find_lessons_have_teacher(int day, int time, vector<teacher> teachers, vector<lesson> lessons_in_this_time);
bool sorting_class_method(pair<lesson, teacher> class1, pair<lesson, teacher> class2);
bool have_this_lesson(string the_lesson_name, vector<string> lessons_name);
bool free_in_this_day(int the_day, vector<int> free_days);
bool free_in_this_time(int day, int start_time, int end_time, vector<schedule_part> busy_time);
void update_time(int &day, int &clock);
void add_to_busy_time(vector<teacher> &teachers, pair<lesson, teacher> the_class, int now);
pair<lesson, teacher> choosing_class_from_list(vector<pair<lesson, teacher>> list, vector<schedule_part> schedule);
bool before_added_in_schedule(pair<lesson, teacher> the_class, vector<schedule_part> schedule);
void add_to_schedule(vector<schedule_part> &schedule, pair<lesson, teacher> the_class, int week_day, int time);
bool is_time_full(vector<schedule_part> schedule, int day, int time);
void output(vector<schedule_part> *schedules, vector<lesson> lessons);
vector<schedule_part> find_lessons_in_schedule(string lesson_name, vector<schedule_part> schedule);
string time_itos(int int_time);
string make_two_digit(string number);
vector<pair<lesson, teacher>> check_classes_available_next_time(vector<pair<lesson, teacher>> classes, int today,
                                                                int time, vector<schedule_part> schedule);
bool can_have_class(pair<lesson, teacher> the_class, int day, int time, vector<schedule_part> schedule);
bool lesson_sort_method(lesson l1, lesson l2);

const int START_SHOOL = time_stoi(START_SCHOOL_STR);
const int END_SCHOOL = time_stoi(END_SCHOOL_STR);
const int BREAK_TIME = time_stoi(BREAK_TIME_STR);
const int START_WEEK = day_stoi(START_WEEK_STR);
const int END_WEEK = day_stoi(END_WEEK_STR);
const int CLASS_TIME = time_stoi(CLASS_TIME_STR);
const pair<lesson, teacher> BREAK_CLASS = make_pair((lesson){"break"}, (teacher){"break"});

int main()
{
        vector<teacher> teachers;
        vector<lesson> lessons;

        input(teachers, lessons);

        vector<schedule_part> schedules[NUMBER_OF_CLASS];
        create_schedule_for_school(schedules, teachers, lessons);

        output(schedules, lessons);

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
        const vector<string> week = {"Saturday", "Sunday", "Monday", "Tuesday",
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

int create_schedule_for_school(vector<schedule_part> *schedules, vector<teacher> &teachers, vector<lesson> &lessons)
{
        for (int i = 0; i < NUMBER_OF_CLASS; i++)
                create_schedule_for_class(teachers, lessons, schedules[i]);
        return 0;
}

int create_schedule_for_class(vector<teacher> &teachers, vector<lesson> &lessons, vector<schedule_part> &schedule)
{
        int now = START_SHOOL;
        int today = START_WEEK;
        while (today <= END_WEEK)
        {
                if (is_time_full(schedule, today, now))
                {
                        update_time(today, now);
                        continue;
                }

                vector<pair<lesson, teacher>> lessons_with_teachers_list = sorted_available_lessons_with_teachers_list(teachers, lessons, today, now);
                vector<pair<lesson, teacher>> classes_availeble_next_day = check_classes_available_next_time(lessons_with_teachers_list, today, now, schedule);

                pair<lesson, teacher> chosen_class = choosing_class_from_list(classes_availeble_next_day, schedule);

                add_to_schedule(schedule, chosen_class, today, now);

                if (chosen_class.first.name != BREAK_CLASS.first.name)
                        add_to_busy_time(teachers, chosen_class, now);

                update_time(today, now);
        }
        return 0;
}

vector<pair<lesson, teacher>> sorted_available_lessons_with_teachers_list(vector<teacher> teachers,
                                                                          vector<lesson> lessons,
                                                                          int day, int time)
{
        vector<lesson> lessons_in_this_time = find_lessons_with_time(day, time, lessons);

        vector<pair<lesson, teacher>> lessons_have_teacher = find_lessons_have_teacher(day, time, teachers, lessons_in_this_time);

        sort(lessons_have_teacher.begin(), lessons_have_teacher.end(), sorting_class_method);

        return lessons_have_teacher;
}

vector<lesson> find_lessons_with_time(int day, int time, vector<lesson> lessons)
{
        vector<lesson> found_lessons;

        for (auto i : lessons)
                for (int j : i.days_shoud_teach)
                {
                        if (j != day)
                                continue;
                        if (i.start_time <= time && time + CLASS_TIME <= i.end_time)
                        {
                                found_lessons.push_back(i);
                                break;
                        }
                }

        return found_lessons;
}

vector<pair<lesson, teacher>> find_lessons_have_teacher(int day, int time, vector<teacher> teachers, vector<lesson> lessons_in_this_time)
{
        vector<pair<lesson, teacher>> lessons_have_teacher;

        for (auto i : lessons_in_this_time)
                for (auto j : teachers)
                {
                        if (!have_this_lesson(i.name, j.lessons))
                                continue;
                        if (!free_in_this_day(day, j.free_days))
                                continue;
                        if (!free_in_this_time(day, time, time + CLASS_TIME, j.busy_time))
                                continue;

                        lessons_have_teacher.push_back(make_pair(i, j));
                }

        return lessons_have_teacher;
}

bool sorting_class_method(pair<lesson, teacher> class1, pair<lesson, teacher> class2)
{
        if (class1.first.name != class2.first.name)
                if (class1.first.name.compare(class2.first.name) < 0)
                        return true;
                else
                        return false;
        else if (class1.second.free_days.size() != class2.second.free_days.size())
                if (class1.second.free_days.size() < class2.second.free_days.size())
                        return true;
                else
                        return false;
        else if (class1.second.name != class2.second.name)
                if (class1.second.name.compare(class2.second.name) < 0)
                        return true;
                else
                        return false;
        else
                return true;
}

bool have_this_lesson(string the_lesson_name, vector<string> lessons_name)
{
        for (auto i : lessons_name)
                if (the_lesson_name == i)
                        return true;
        return false;
}

bool free_in_this_day(int the_day, vector<int> free_days)
{
        for (auto i : free_days)
                if (the_day == i)
                        return true;
        return false;
}

bool free_in_this_time(int day, int start_time, int end_time, vector<schedule_part> busy_time)
{
        for (auto i : busy_time)
                if (day != i.week_day)
                        continue;
                else if (i.start_time <= start_time && start_time <= i.end_time)
                        return false;
                else if (start_time <= i.end_time && i.end_time <= end_time)
                        return false;
                else if (start_time <= i.start_time && i.start_time <= end_time)
                        return false;
        return true;
}

void update_time(int &day, int &clock)
{
        clock += CLASS_TIME + BREAK_TIME;

        if (clock >= END_SCHOOL)
        {
                day++;
                clock = START_SHOOL;
        }
}

void add_to_busy_time(vector<teacher> &teachers, pair<lesson, teacher> the_class, int time)
{
        schedule_part new_part;
        new_part.week_day = the_class.first.days_shoud_teach[0];
        new_part.start_time = time;
        new_part.end_time = time + CLASS_TIME;
        new_part.this_time_lesson = the_class.first;
        new_part.this_time_teacher = the_class.second;

        string teacher_name = the_class.second.name;
        for (int i = 0; i < teachers.size(); i++)
                if (teachers[i].name == teacher_name)
                {
                        teachers[i].busy_time.push_back(new_part);
                        new_part.week_day = the_class.first.days_shoud_teach[1];
                        teachers[i].busy_time.push_back(new_part);
                }
}

pair<lesson, teacher> choosing_class_from_list(vector<pair<lesson, teacher>> list, vector<schedule_part> schedule)
{
        for (auto i : list)
                if (!before_added_in_schedule(i, schedule))
                        return i;
        return BREAK_CLASS;
}

bool before_added_in_schedule(pair<lesson, teacher> the_class, vector<schedule_part> schedule)
{
        int repeat_count = find_lessons_in_schedule(the_class.first.name, schedule).size();

        if (repeat_count != 0)
                return true;
        else
                return false;
}

vector<schedule_part> find_lessons_in_schedule(string lesson_name, vector<schedule_part> schedule)
{
        vector<schedule_part> schedule_part_have_this;

        for (auto i : schedule)
                if (lesson_name == i.this_time_lesson.name)
                        schedule_part_have_this.push_back(i);

        return schedule_part_have_this;
}

void add_to_schedule(vector<schedule_part> &schedule, pair<lesson, teacher> the_class, int week_day, int time)
{
        schedule_part new_part;
        new_part.start_time = time;
        new_part.end_time = time + CLASS_TIME;
        new_part.this_time_lesson = the_class.first;
        new_part.this_time_teacher = the_class.second;

        if (the_class.first.name != BREAK_CLASS.first.name)
        {
                for (auto i : the_class.first.days_shoud_teach)
                {
                        new_part.week_day = i;
                        schedule.push_back(new_part);
                }
        }
        else
        {
                new_part.week_day = week_day;
                schedule.push_back(new_part);
        }
}

bool is_time_full(vector<schedule_part> schedule, int day, int time)
{
        for (auto i : schedule)
                if (i.start_time == time && i.week_day == day)
                        return true;
        return false;
}

void output(vector<schedule_part> *schedules, vector<lesson> lessons)
{
        sort(lessons.begin(), lessons.end(), lesson_sort_method);
        for (auto i : lessons)
        {
                cout << i.name << endl;
                for (int j = 0; j < NUMBER_OF_CLASS; j++)
                {
                        vector<schedule_part> parts_have_this_lesson = find_lessons_in_schedule(i.name, schedules[j]);

                        if (parts_have_this_lesson.size() == 0)
                                cout << "Not Found" << endl;
                        else
                        {
                                string teacher_name = parts_have_this_lesson[0].this_time_teacher.name;
                                string start_time = time_itos(parts_have_this_lesson[0].start_time);
                                string end_time = time_itos(parts_have_this_lesson[0].end_time);

                                cout << teacher_name << ": " << start_time << " " << end_time << endl;
                        }
                }
        }
}

bool lesson_sort_method(lesson l1, lesson l2) { return l1.name.compare(l2.name) < 0 ? true : false; }

string time_itos(int int_time)
{
        string hour = make_two_digit(to_string(int_time / 60));
        string min = make_two_digit(to_string(int_time % 60));

        string clock_form = hour + ":" + min;

        return clock_form;
}

string make_two_digit(string number)
{
        while (number.length() < 2)
                number = "0" + number;
        return number;
}

vector<pair<lesson, teacher>> check_classes_available_next_time(vector<pair<lesson, teacher>> classes, int today, int time, vector<schedule_part> schedule)
{
        vector<pair<lesson, teacher>> classes_availeble_next_day;

        for (auto i : classes)
        {
                int next_day = i.first.days_shoud_teach[0] == today
                                   ? i.first.days_shoud_teach[1]
                                   : i.first.days_shoud_teach[0];

                if (can_have_class(i, next_day, time, schedule))
                        classes_availeble_next_day.push_back(i);
        }
        return classes_availeble_next_day;
}

bool can_have_class(pair<lesson, teacher> the_class, int day, int time, vector<schedule_part> schedule)
{
        if (is_time_full(schedule, day, time))
                return false;

        vector<lesson> class_lesson = {the_class.first};
        vector<teacher> class_teacher = {the_class.second};
        if (sorted_available_lessons_with_teachers_list(class_teacher, class_lesson, day, time).size() == 0)
                return false;

        return true;
}
