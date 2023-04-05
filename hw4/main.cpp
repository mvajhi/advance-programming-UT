#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>
#include <map>

using namespace std;

class Salary_manager;
class Employee;
class Team;
class Working_interval;
class Level;

vector<string> dumping_CSV_file_into_memory_line_by_line(string file_address);

int main()
{

        return 0;
}

class Salary_manager
{
private:
        vector<Employee> employees;
        vector<Team> teams;
        map<string, Level> employee_levels;

public:
        Salary_manager(/* args */);
};

class Employee
{
private:
        int id;
        string name;
        int age;
        string level;
        Level *level_details;
        int working_day;
        Working_interval working_interval;

public:
        Employee(/* args */);
};

class Team
{
private:
        int team_id;
        Employee *head;
        vector<Employee> *members;
        float avg_working_hours;
        float varinace_working_hours;
        int bonus_min_working_hours;
        float bonus_working_hours_max_variance;

public:
        Team(/* args */);
};

class Working_interval
{
private:
        int start_time;
        int end_time;

public:
        Working_interval(/*arg*/);
};

class Level
{
private:
        int base_salary;
        int salary_per_hour;
        int salary_per_extra_hour;
        int oddcial_working_hours;
        int tax_perecentage;

public:
        Level(/* args */);
};
