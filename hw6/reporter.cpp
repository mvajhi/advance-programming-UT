#include "reporter.hpp"

Massage_reporter::Massage_reporter(string massage_)
{
    massage = massage_;
}

void Massage_reporter::cli_report()
{
    cout << massage;
}

new_completed_missions_reporter::new_completed_missions_reporter(vector<shared_ptr<Mission_with_status>> completed_missions_, int driver_id_)
{
    completed_missions = completed_missions_;
    driver_id = driver_id_;
}

bool sort_mission_logic(shared_ptr<Mission_with_status> m1, shared_ptr<Mission_with_status> m2)
{
    return m1->detail->get_time_range().start < m2->detail->get_time_range().start;
}

void new_completed_missions_reporter::cli_report()
{
    sort(completed_missions.begin(), completed_missions.end(), sort_mission_logic);
    cout << "completed missions for driver " << driver_id << ":";
    for (auto mission : completed_missions)
    {
        cout << endl;
        cout << "mission: " << mission->detail->get_id() << endl;
        cout << "start timestamp: " << mission->detail->get_time_range().start << endl;
        cout << "end timestamp: " << mission->detail->get_time_range().end << endl;
        cout << "reward: " << mission->detail->get_reward() << endl;
    }

    if (completed_missions.size() == 0)
        cout << "\n\n";
}

all_missions_reporter::all_missions_reporter(vector<shared_ptr<Mission_with_status>> mission_, int driver_id_)
{
    missions = mission_;
    driver_id = driver_id_;
}

void all_missions_reporter::cli_report()
{
    sort(missions.begin(), missions.end(), sort_mission_logic);
    cout << "missions status for driver " << driver_id << ":";
    for (auto mission : missions)
    {
        cout << endl;
        cout << "mission " << mission->detail->get_id() << ":" << endl;
        cout << "start timestamp: " << mission->detail->get_time_range().start << endl;
        cout << "end timestamp: "
             << (mission->is_complete
                     ? to_string(mission->complete_time)
                     : DEFAULT_INCOMPLETE_END_TIME_MISSION_CLI_MASSAGE)
             << endl;
        cout << "reward: " << mission->detail->get_reward() << endl;
        cout << "status: "
             << (mission->is_complete
                     ? COMPLETE_MISSION_STATUS_CLI_MASSAGE
                     : INCOMPLETE_MISSION_STATUS_CLI_MASSAGE)
             << endl;
    }
}
