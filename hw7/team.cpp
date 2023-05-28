#include "team.hpp"

Team::Team(string name_, map<string, vector<shared_ptr<Player>>> players_)
{
    name = name_;
    players = players_;

    /*
        cout << "\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\n";
        cout << "team name: " << name << endl;
        for (auto i : players)
        {
            cout << "\t\\\\\\\\\\\\\n";
            cout << "\trole: " << i.first << endl;
            for (auto j : i.second)
            {
                cout << "\t\t\\\\\\\\\\\\\n";
                cout << "\t\tname: " << j->get_name() << endl;
            }
            cout << "\t\\\\\\\\\\\\\n";
        }
        cout << "\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\n";
        */
}

Team_status Team::get_status(int week)
{
    if (weeks_status.count(week) != 0)
        return weeks_status[week];

    Team_status not_played_week;
    not_played_week.ga = 0;
    not_played_week.gf = 0;
    not_played_week.score = 0;

    return not_played_week;
}

vector<shared_ptr<Player>> Team::get_players(bool is_sort, bool have_role, string role)
{
    vector<shared_ptr<Player>> output;

    //! possible bug
    for (auto i : players)
        output.insert(output.end(), i.second.begin(), i.second.end());

    return output;
}

string Team::get_name()
{
    return name;
}

void Team::add_new_match(int week, int score, int ga, int gf)
{
    Team_status status;
    status.score = score;
    status.ga = ga;
    status.gf = gf;
    weeks_status.insert(make_pair(week, status));
}
