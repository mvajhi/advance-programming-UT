#include "reporter.hpp"

Massage_reporter::Massage_reporter(string massage_)
{
    massage = massage_;
}

void Massage_reporter::cli_report()
{
    cout << massage;
}

new_completed_mission_reporter::new_completed_mission_reporter(vector<shared_ptr<Mission_with_status>> completed_missions_, int driver_id_)
{
    completed_missions = completed_missions_;
    driver_id = driver_id_;
}

void new_completed_mission_reporter::cli_report()
{
    // TODO sorting
    cout << "completed missions for driver " << driver_id << ":\n";
    for (auto mission : completed_missions)
    {
        cout << "mission: " << mission->detail->get_id() << endl;
        cout << "start timestamp: " << mission->detail->get_time_range().start << endl;
        cout << "end timestamp: " << mission->detail->get_time_range().end << endl;
        cout << "reward: " << mission->detail->get_reward() << endl;
        cout << endl;
    }

    if (completed_missions.size() == 0)
        cout << endl;
}
