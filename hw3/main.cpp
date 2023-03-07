#include <iostream>
#include <vector>
#include <string>

#define NUMBER_OF_DAYS_TO_TEACH 2
#define DEFAULT_TEACHING_DAYS 0
#define HOUR_MINUTE 60
#define TIME_STRING_SIZE 5
#define DEFAULT_MINUTE_TIME 0
#define DEFAULT_HOUR_TIME 0

using namespace std;

class Time;
class lesson;
class teacher;
class school_schedule;

int main()
{
        // Time t1, t2, t3;
        // cout << "-----------------\n";
        // Time t4("10:30");
        // cout << "t4 : " << t4.str_time() << endl;
        // cout << "-----------------\n";
        // Time t5(10 ,30);
        // cout << "t4 : " << t5.str_time() << endl;
        // cout << "-----------------\n";
        // Time t6(10 * HOUR_MINUTE + 30);
        // cout << "t4 : " << t6.str_time() << endl;
        // while (true)
        // {
        //         string t1_str, t2_str;
        //         cin >> t1_str;
        //         cin >> t2_str;
        //         cout << "-----------------\n";
        //         cout << "t1 hour: " << t1.hour() << endl;
        //         cout << "-----------------\n";
        //         cout << "t1 min: " << t1.minute() << endl;
        //         cout << "-----------------\n";
        //         t3 = t1 + t2;
        //         cout << "tt+: " << t3.str_time() << endl;
        //         cout << "-----------------\n";
        //         t3 = t1 + 30;
        //         cout << "t30+: " << t3.str_time() << endl;
        //         cout << "-----------------\n";
        //         cout << "t1 < t2: " << to_string(t1 < t2) << endl;
        //         cout << "-----------------\n";
        //         cout << "t1 <= t2: " << to_string(t1 <= t2) << endl;
        //         cout << "-----------------\n";
        //         cout << "t1 == t2: " << to_string(t1 == t2) << endl;
        //         cout << "-----------------\n";
        //         cout << "t1 > t2: " << to_string(t1 > t2) << endl;
        //         cout << "-----------------\n";
        //         cout << "t1 >= t2: " << to_string(t1 >= t2) << endl;
        //         cout << "-----------------\n";

        // }

        return 0;
}

class Time
{
private:
        int time_per_min;

public:
        Time(string str_time);
        Time(int hour, int minute) { set_time(hour, minute); }
        Time(int new_time_per_minute) { set_time(new_time_per_minute); }
        Time() { set_time(DEFAULT_HOUR_TIME, DEFAULT_MINUTE_TIME); }
        void set_time(int hour, int minute) { time_per_min = hour * HOUR_MINUTE + minute; }
        void set_time(int new_time_per_minute) { time_per_min = new_time_per_minute; }
        int per_min() { return time_per_min; }
        int hour() { return time_per_min / HOUR_MINUTE; }
        int minute() { return time_per_min % HOUR_MINUTE; };
        string str_time() { return to_string(hour()) + ':' + to_string(minute()); }
        Time operator+(int minute) { return (Time)this->time_per_min + minute; }
        Time operator+(Time t2) { return (Time)(this->time_per_min + t2.time_per_min); }
        bool operator<(Time t2) { return this->time_per_min < t2.time_per_min; }
        bool operator<=(Time t2) { return this->time_per_min <= t2.time_per_min; }
        bool operator==(Time t2) { return this->time_per_min == t2.time_per_min; }
        bool operator>(Time t2) { return this->time_per_min > t2.time_per_min; }
        bool operator>=(Time t2) { return this->time_per_min >= t2.time_per_min; }
};

Time::Time(string str_time)
{
        if (str_time.length() != TIME_STRING_SIZE)
        {
                cout << "invalid arg to set time. set default time try again\n";
                set_time(DEFAULT_HOUR_TIME, DEFAULT_MINUTE_TIME);
        }
        set_time(stoi(str_time.substr(0, 2)), stoi(str_time.substr(3, 2)));
}

class lesson
{
private:
        string name;
        vector<int> teaching_days;
        vector<teacher> teachers;
        Time start;
        Time end;

public:
        lesson(/* args */);
        bool can_hold_class(Time now, int week_day);
};

class teacher
{
private:
        string name;
        vector<lesson> lessons;
        vector<int> free_days;

public:
        teacher(/* args */);
        bool is_busy(Time now, int week_day);
};

class school_schedule
{
private:
        vector<lesson> lessons;
        vector<teacher> teachers;
        Time break_time;

public:
        school_schedule(Time break_time);
};
