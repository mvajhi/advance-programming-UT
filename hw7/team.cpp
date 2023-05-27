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
    return Team_status();
}

vector<shared_ptr<Player>> Team::get_players(bool is_sort, bool have_role, string role)
{
    return vector<shared_ptr<Player>>();
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
