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
class Working_time_manager;
class Level;

struct Time_interval
{
        int start;
        int end;
};

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
        Working_time_manager working_times;

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

class Working_time_manager
{
private:
        vector<pair<int, Time_interval>> times;
public:
        Working_time_manager(/*arg*/);
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
