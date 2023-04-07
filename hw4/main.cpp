#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>
#include <map>

using namespace std;

const string SPREATE_CHAR_IN_CSV = ",";
const string SPREATE_MEMBER_IN_TEAM_CSV = "$";
const char SPREATE_TIME_RANGE_IN_CSV = '-';
const string SPREATE_2_EMPLOYEE_CLI_OUTPUT = "---\n";
const int MONTH_LENGTH = 30;
const int DAY_LENGTH = 24;
const int DEFAULT_TEAM_BONUS = 0;

const string EMPLOYEE_NOT_FOUND_MASSAGE = "EMPLOYEE_NOT_FOUND";
const string EMPLOYEE_WITHOUT_TEAM_MASSAGE = "N/A";

const string NAME_INDEX_IN_CONFIGS_CSV = "level";
const string BASE_SALARY_INDEX_IN_CONFIGS_CSV = "base_salary";
const string SALARY_PER_HOUR_INDEX_IN_CONFIGS_CSV = "salary_per_hour";
const string SALARY_PER_EXTRA_HOUR_INDEX_IN_CONFIGS_CSV = "salary_per_extra_hour";
const string OFFCIAL_WORKING_HOURS_INDEX_IN_CONFIGS_CSV = "official_working_hours";
const string TAX_PERECENTAGE_INDEX_IN_CONFIGS_CSV = "tax_percentage";
const vector<string> LEVEL_NAMES = {"junior", "expert", "senior", "team_lead"};

const string ID_INDEX_IN_EMPLOYEE_CSV = "id";
const string NAME_INDEX_IN_EMPLOYEE_CSV = "name";
const string AGE_INDEX_IN_EMPLOYEE_CSV = "age";
const string LEVEL_INDEX_IN_EMPLOYEE_CSV = "level";

const string EMPLOYEE_INDEX_IN_WORKING_HOURS_CSV = "employee_id";
const string DAY_INDEX_IN_WORKING_HOURS_CSV = "day";
const string WORKING_INTERVAL_INDEX_IN_WORKING_HOURS_CSV = "working_interval";

const string TEAM_ID_INDEX_IN_TEAMS_CSV = "team_id";
const string TEAM_HEAD_ID_INDEX_IN_TEAMS_CSV = "team_head_id";
const string MEMBER_IDS_INDEX_IN_TEAMS_CSV = "member_ids";
const string BONUS_MIN_TIME_INDEX_IN_TEAMS_CSV = "bonus_min_working_hours";
const string BONUS_MAX_VARIANCE_INDEX_IN_TEAMS_CSV = "bonus_working_hours_max_variance";

class Salary_manager;
class Employee;
class Team;
class Working_time_manager;
class Level;

struct Time_interval
{
        int start;
        int end;
};

struct Level
{
        string name;
        int base_salary;
        int salary_per_hour;
        int salary_per_extra_hour;
        int offcial_working_hours;
        float tax_perecentage;
};

class Salary_manager
{
private:
        map<int, Employee *> employees;
        map<int, Team *> teams;
        map<string, Level *> employee_levels;

        vector<string> dumping_CSV_file_into_memory_line_by_line(string file_address);
        vector<string> seperate_words(const string line, string separate_char);
        vector<map<string, string>> convert_csv_lines_to_dictionary(vector<string> csv_lines);
        void add_levels_with_dectionary(vector<map<string, string>> level_dectionary);
        void add_employee_with_dectionary(vector<map<string, string>> employee_dectionary);
        void add_working_hours_with_dectionary(vector<map<string, string>> working_hours_dectionary);
        void add_team_with_dectionary(vector<map<string, string>> team_dectionary);
        vector<Employee *> find_list_of_employee_with_csv_part(string csv_part);

public:
        ~Salary_manager();
        void import_csv_files(string employee_file_address, string team_file_address,
                              string working_hours_file_address, string salary_config_file_address);
        string report_salaries();
        string employee_report(int id);
};

class Working_time_manager
{
private:
        vector<pair<int, Time_interval>> times;

        bool is_busy(pair<int, Time_interval> time);

public:
        int add_new_time(int day, string range);
        int total_work();
        int get_absent_day_count();
};

class Employee
{
private:
        int id;
        string name;
        int age;
        Level *level_details;
        Team *team;
        Working_time_manager working_times;
        int total_earning();
        int tax();
        int salary();
        int bonus();
        bool have_team() { return team != NULL; }

public:
        Employee(int employee_id, string employee_name, int employee_age, Level *employee_level);
        int add_new_work_time(int day, string range) { return working_times.add_new_time(day, range); }
        void added_to_team(Team *employee_team) { team = employee_team; }
        string summery_report();
        string full_report();
};

class Team
{
private:
        int id;
        Employee *head;
        vector<Employee *> members;
        int bonus_min_working_hours;
        float bonus_percentage;
        float bonus_working_hours_max_variance;

        //TODO
        bool have_bonus() { return true; }

public:
        Team(int team_id, Employee *team_head, vector<Employee *> team_members, int bonus_min_work, float bonus_max_variance);
        int get_id() { return id; }
        float get_bonus() { return have_bonus() ? bonus_percentage : 0; }
};

// TODO get address from arg
int main()
{
        string employee_file_address = "./assets/employees.csv";
        string team_file_address = "./assets/teams.csv";
        string working_hours_file_address = "./assets/working_hours.csv";
        string salary_config_file_address = "./assets/salary_configs.csv";

        Salary_manager the_salary_manager;
        the_salary_manager.import_csv_files(employee_file_address, team_file_address,
                                            working_hours_file_address, salary_config_file_address);

        cout << the_salary_manager.report_salaries() << endl;
        cout << the_salary_manager.employee_report(6);

        return 0;
}

Employee::Employee(int employee_id, string employee_name, int employee_age, Level *employee_level)
{
        id = employee_id;
        name = employee_name;
        age = employee_age;
        level_details = employee_level;
        team = NULL;
}

string Employee::summery_report()
{
        string output;
        output += "ID: " + to_string(id) + "\n";
        output += "Name: " + name + "\n";
        output += "Total Hours Working: " + to_string(working_times.total_work()) + "\n";
        output += "Total Earning: " + to_string(total_earning()) + "\n";

        return output;
}

string Employee::full_report()
{
        string output;
        output += "ID: " + to_string(id) + "\n";
        output += "Name: " + name + "\n";
        output += "Age: " + to_string(age) + "\n";
        output += "Level: " + level_details->name + "\n";
        output += "Team ID: ";
        if (team == NULL)
                output += EMPLOYEE_WITHOUT_TEAM_MASSAGE + "\n";
        else
                output += to_string(team->get_id()) + "\n";
        output += "Total Hours Working: " + to_string(working_times.total_work()) + "\n";
        output += "Absent Days: " + to_string(working_times.get_absent_day_count()) + "\n";
        output += "Salary: " + to_string(salary()) + "\n";
        output += "Bonus: " + to_string(bonus()) + "\n";
        output += "Tax: " + to_string(tax()) + "\n";
        output += "Total Earning: " + to_string(total_earning()) + "\n";

        return output;
}

int Employee::total_earning()
{
        return (salary() + bonus()) * (1 - level_details->tax_perecentage);
}

int Employee::tax()
{
        return (salary() + bonus()) * level_details->tax_perecentage;
}

int Employee::salary()
{
        int sum = 0;
        int total_hours = working_times.total_work();
        if (total_hours > level_details->offcial_working_hours)
        {
                sum += level_details->salary_per_hour * level_details->offcial_working_hours;
                sum += level_details->salary_per_extra_hour * (total_hours - level_details->offcial_working_hours);
        }
        else
        {
                sum += level_details->salary_per_hour * total_hours;
        }

        return sum;
}

int Employee::bonus()
{
        if (!have_team())
                return 0;
        return salary() * team->get_bonus();
}

Salary_manager::~Salary_manager()
{
        for (pair<int, Employee *> employee : employees)
                delete employee.second;
        for (pair<int, Team *> team : teams)
                delete team.second;
        for (pair<string, Level *> level : employee_levels)
                delete level.second;
}

vector<string> Salary_manager::seperate_words(const string line, string separate_char)
{
        vector<string> words;
        string temp = line;
        size_t pos = 0;
        while ((pos = temp.find(separate_char)) != string::npos)
        {
                words.push_back(temp.substr(0, pos));
                temp.erase(0, pos + separate_char.length());
        }
        words.push_back(temp);
        return words;
}

vector<map<string, string>> Salary_manager::convert_csv_lines_to_dictionary(vector<string> csv_lines)
{
        vector<map<string, string>> dictionary;
        vector<string> index = seperate_words(csv_lines[0], SPREATE_CHAR_IN_CSV);

        for (int i = 1; i < csv_lines.size(); i++)
        {
                vector<string> words_line_buffer = seperate_words(csv_lines[i], SPREATE_CHAR_IN_CSV);
                map<string, string> new_index_line;

                for (int j = 0; j < index.size(); j++)
                        new_index_line.insert(pair(index[j], words_line_buffer[j]));

                dictionary.push_back(new_index_line);
        }

        return dictionary;
}

void Salary_manager::add_levels_with_dectionary(vector<map<string, string>> level_dectionary)
{
        for (auto i : level_dectionary)
        {
                Level *new_level = new Level;

                new_level->name = i[NAME_INDEX_IN_CONFIGS_CSV];
                new_level->base_salary = stoi(i[BASE_SALARY_INDEX_IN_CONFIGS_CSV]);
                new_level->salary_per_hour = stoi(i[SALARY_PER_HOUR_INDEX_IN_CONFIGS_CSV]);
                new_level->salary_per_extra_hour = stoi(i[SALARY_PER_EXTRA_HOUR_INDEX_IN_CONFIGS_CSV]);
                new_level->offcial_working_hours = stoi(i[OFFCIAL_WORKING_HOURS_INDEX_IN_CONFIGS_CSV]);
                new_level->tax_perecentage = stof(i[TAX_PERECENTAGE_INDEX_IN_CONFIGS_CSV]) / 100;

                employee_levels.insert(pair(i[NAME_INDEX_IN_CONFIGS_CSV], new_level));
        }
}

void Salary_manager::add_employee_with_dectionary(vector<map<string, string>> employee_dectionary)
{
        for (auto i : employee_dectionary)
        {
                Employee *new_employee = new Employee(
                    stoi(i[ID_INDEX_IN_EMPLOYEE_CSV]),
                    i[NAME_INDEX_IN_EMPLOYEE_CSV],
                    stoi(i[AGE_INDEX_IN_EMPLOYEE_CSV]),
                    employee_levels[i[LEVEL_INDEX_IN_EMPLOYEE_CSV]]);
                employees.insert(pair(stoi(i[ID_INDEX_IN_EMPLOYEE_CSV]), new_employee));
        }
}

void Salary_manager::add_working_hours_with_dectionary(vector<map<string, string>> working_hours_dectionary)
{
        for (auto i : working_hours_dectionary)
        {
                employees[stoi(i[EMPLOYEE_INDEX_IN_WORKING_HOURS_CSV])]
                    ->add_new_work_time(stoi(i[DAY_INDEX_IN_WORKING_HOURS_CSV]),
                                        i[WORKING_INTERVAL_INDEX_IN_WORKING_HOURS_CSV]);
        }
}

void Salary_manager::add_team_with_dectionary(vector<map<string, string>> team_dectionary)
{
        for (auto i : team_dectionary)
        {
                Employee *team_head = employees[stoi(i[TEAM_HEAD_ID_INDEX_IN_TEAMS_CSV])];
                vector<Employee *> members = find_list_of_employee_with_csv_part(i[MEMBER_IDS_INDEX_IN_TEAMS_CSV]);

                Team *new_team = new Team(
                    stoi(i[TEAM_ID_INDEX_IN_TEAMS_CSV]),
                    team_head,
                    members,
                    stoi(i[BONUS_MIN_TIME_INDEX_IN_TEAMS_CSV]),
                    stof(i[BONUS_MAX_VARIANCE_INDEX_IN_TEAMS_CSV]));

                for (auto i : members)
                        i->added_to_team(new_team);

                teams.insert(pair(stoi(i[TEAM_ID_INDEX_IN_TEAMS_CSV]), new_team));
        }
}

vector<Employee *> Salary_manager::find_list_of_employee_with_csv_part(string csv_part)
{
        vector<string> employee_id_str = seperate_words(csv_part, SPREATE_MEMBER_IN_TEAM_CSV);
        vector<Employee *> employee_list;

        for (auto j : employee_id_str)
                employee_list.push_back(employees[stoi(j)]);

        return employee_list;
}

vector<string> Salary_manager::dumping_CSV_file_into_memory_line_by_line(string file_address)
{
        ifstream csv_file_stream;
        csv_file_stream.open(file_address);
        if (csv_file_stream.fail())
        {
                cout << "Input file opening failed.\n";
                exit(1);
        }

        vector<string> lines;
        string line_buffer;
        while (getline(csv_file_stream, line_buffer))
                lines.push_back(line_buffer);
        csv_file_stream.close();

        return lines;
}

void Salary_manager::import_csv_files(string employee_file_address, string team_file_address,
                                      string working_hours_file_address, string salary_config_file_address)
{
        vector<string> level_csv = dumping_CSV_file_into_memory_line_by_line(salary_config_file_address);
        vector<map<string, string>> level_dectionary = convert_csv_lines_to_dictionary(level_csv);
        add_levels_with_dectionary(level_dectionary);

        vector<string> employee_csv = dumping_CSV_file_into_memory_line_by_line(employee_file_address);
        vector<map<string, string>> employee_dectionary = convert_csv_lines_to_dictionary(employee_csv);
        add_employee_with_dectionary(employee_dectionary);

        vector<string> working_hours_csv = dumping_CSV_file_into_memory_line_by_line(working_hours_file_address);
        vector<map<string, string>> working_hours_dectionary = convert_csv_lines_to_dictionary(working_hours_csv);
        add_working_hours_with_dectionary(working_hours_dectionary);

        vector<string> team_csv = dumping_CSV_file_into_memory_line_by_line(team_file_address);
        vector<map<string, string>> team_dectionary = convert_csv_lines_to_dictionary(team_csv);
        add_team_with_dectionary(team_dectionary);
}

string Salary_manager::report_salaries()
{
        string output;

        for (auto i : employees)
                output += i.second->summery_report() + SPREATE_2_EMPLOYEE_CLI_OUTPUT;

        return output;
}

string Salary_manager::employee_report(int id)
{
        if (employees.count(id) == 0)
                return EMPLOYEE_NOT_FOUND_MASSAGE + "\n";

        return employees[id]->full_report();
}

Team::Team(int team_id, Employee *team_head, vector<Employee *> team_members, int bonus_min_work, float bonus_max_variance)
{
        id = team_id;
        head = team_head;
        members = team_members;
        bonus_min_working_hours = bonus_min_work;
        bonus_working_hours_max_variance = bonus_max_variance;
        bonus_percentage = DEFAULT_TEAM_BONUS;
}

bool Working_time_manager::is_busy(pair<int, Time_interval> time)
{
        for (auto i : times)
                if (time.first == i.first)
                        if ((time.second.start < i.second.start && time.second.end > i.second.start) ||
                            (time.second.start > i.second.start && time.second.start < i.second.end) ||
                            (time.second.end > i.second.start && time.second.end < i.second.end))
                                return true;
        return false;
}

// TODO fix retrun value
int Working_time_manager::add_new_time(int day, string range)
{
        int start = stoi(range.substr(0, range.find(SPREATE_TIME_RANGE_IN_CSV)));
        int end = stoi(range.substr(range.find(SPREATE_TIME_RANGE_IN_CSV) + 1, range.length()));
        Time_interval new_range = {start, end};

        if (day < 1 || day > MONTH_LENGTH)
                return 0;

        if (start < 0 || start > DAY_LENGTH ||
            end < 0 || end > DAY_LENGTH ||
            start >= end)
                return 0;

        if (is_busy(pair(day, new_range)))
                return 0;

        times.push_back(pair(day, new_range));

        return 1;
}

int Working_time_manager::total_work()
{
        int sum = 0;

        for (auto i : times)
                sum += i.second.end - i.second.start;

        return sum;
}

int Working_time_manager::get_absent_day_count()
{
        map<int, int> day;
        int count = 0;
        for (auto i : times)
                day[i.first]++;
        for (auto i : day)
                count++;
        return MONTH_LENGTH - count;
}
