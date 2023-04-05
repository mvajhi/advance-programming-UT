#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>
#include <map>

using namespace std;

const string SPREATE_CHAR_IN_CSV = ",";
const string NAME_INDEX_IN_CONFIGS_CSV = "level";
const string BASE_SALARY_INDEX_IN_CONFIGS_CSV = "base_salary";
const string SALARY_PER_HOUR_INDEX_IN_CONFIGS_CSV = "salary_per_hour";
const string SALARY_PER_EXTRA_HOUR_INDEX_IN_CONFIGS_CSV = "salary_per_extra_hour";
const string OFFCIAL_WORKING_HOURS_INDEX_IN_CONFIGS_CSV = "official_working_hours";
const string TAX_PERECENTAGE_INDEX_IN_CONFIGS_CSV = "tax_percentage";
const vector<string> LEVEL_NAMES = {"junior", "expert", "senior", "team_lead"};

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

class Salary_manager
{
private:
        vector<Employee *> employees;
        vector<Team *> teams;
        map<string, Level *> employee_levels;

        vector<string> dumping_CSV_file_into_memory_line_by_line(string file_address);
        vector<string> seperate_words(const string line, string separate_char);
        vector<map<string, string>> convert_csv_lines_to_dictionary(vector<string> csv_lines);
        void add_levels_with_dectionary(vector<map<string, string>> level_dectionary);

public:
        ~Salary_manager();
        void import_csv_files(string employe_file_address, string team_file_address,
                              string working_hours_file_address, string salary_config_file_address);
};

class Working_time_manager
{
private:
        vector<pair<int, Time_interval>> times;

public:
        int foo() { return 0; }
};

class Employee
{
private:
        int id;
        string name;
        int age;
        Level *level_details;
        Working_time_manager working_times;

public:
        Employee(int employee_id, string employee_name, int employee_age, Level *employee_level);
};

class Team
{
private:
        int id;
        Employee *head;
        vector<Employee *> members;
        int bonus_min_working_hours;
        float bonus_working_hours_max_variance;

public:
        Team(int team_id, Employee *team_head, vector<Employee *> team_members, int bonus_min_work, float bonus_max_variance);
};


class Level
{
private:
        string name;
        int base_salary;
        int salary_per_hour;
        int salary_per_extra_hour;
        int offcial_working_hours;
        int tax_perecentage;

public:
        bool set_name(string name_level);
        void set_base_salary(int base_salary_level) { base_salary = base_salary_level; }
        void set_salary_per_hour(int salary_per_hour_level) { salary_per_hour = salary_per_hour_level; }
        void set_salary_per_extra_hour(int salary_per_extra_hour_level) { salary_per_extra_hour = salary_per_extra_hour_level; }
        void set_offcial_working_hours(int offcial_working_hours_level) { offcial_working_hours = offcial_working_hours_level; }
        bool set_tax_perecentage(int tax_perecentage_level);
        string get_name() { return name; }
};

// TODO get address from arg
int main()
{
        string employe_file_address = "./assets/employees.csv";
        string team_file_address = "./assets/teams.csv";
        string working_hours_file_address = "./assets/working_hours.csv";
        string salary_config_file_address = "./assets/salary_configs2.csv";

        Salary_manager the_salary_manager;
        the_salary_manager.import_csv_files(employe_file_address, team_file_address,
                                            working_hours_file_address, salary_config_file_address);

        cout << "end\n";

        return 0;
}

Employee::Employee(int employee_id, string employee_name, int employee_age, Level *employee_level)
{
        id = employee_id;
        name = employee_name;
        age = employee_age;
        level_details = employee_level;
}

Salary_manager::~Salary_manager()
{
        for (Employee *employee : employees)
                delete employee;
        for (Team *team : teams)
                delete team;
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
                for (auto j : i)
                {
                        if (j.first == NAME_INDEX_IN_CONFIGS_CSV)
                                new_level->set_name(j.second);
                        else if (j.first == BASE_SALARY_INDEX_IN_CONFIGS_CSV)
                                new_level->set_base_salary(stoi(j.second));
                        else if (j.first == SALARY_PER_HOUR_INDEX_IN_CONFIGS_CSV)
                                new_level->set_salary_per_hour(stoi(j.second));
                        else if (j.first == SALARY_PER_EXTRA_HOUR_INDEX_IN_CONFIGS_CSV)
                                new_level->set_salary_per_extra_hour(stoi(j.second));
                        else if (j.first == OFFCIAL_WORKING_HOURS_INDEX_IN_CONFIGS_CSV)
                                new_level->set_offcial_working_hours(stoi(j.second));
                        else if (j.first == TAX_PERECENTAGE_INDEX_IN_CONFIGS_CSV)
                                new_level->set_tax_perecentage(stoi(j.second));
                }
                employee_levels.insert(pair(new_level->get_name(), new_level));
        }
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

void Salary_manager::import_csv_files(string employe_file_address, string team_file_address,
                                      string working_hours_file_address, string salary_config_file_address)
{
        vector<string> level_csv = dumping_CSV_file_into_memory_line_by_line(salary_config_file_address);
        vector<map<string, string>> level_dectionary = convert_csv_lines_to_dictionary(level_csv);
        add_levels_with_dectionary(level_dectionary);
}

Team::Team(int team_id, Employee *team_head, vector<Employee *> team_members, int bonus_min_work, float bonus_max_variance)
{
        id = team_id;
        head = team_head;
        members = team_members;
        bonus_min_working_hours = bonus_min_work;
        bonus_working_hours_max_variance = bonus_max_variance;
}

bool Level::set_name(string name_level)
{
        for (auto i : LEVEL_NAMES)
                if (i == name_level)
                {
                        name = name_level;
                        return true;
                }

        return false;
}

bool Level::set_tax_perecentage(int tax_perecentage_level)
{
        if (tax_perecentage_level < 0 && tax_perecentage_level > 100)
                return false;
        tax_perecentage = tax_perecentage_level;
        return true;
}
