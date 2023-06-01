#include "team.hpp"

double Team::get_sum_weeks(int week, function<double(Team_status)> thing_collect)
{
    double sum = 0;

    for (int i = 1; i <= week; i++)
        sum += thing_collect(weeks_status[i]);

    return sum;
}

vector<shared_ptr<Player>> Team::get_team_players(bool have_role, string role)
{
    vector<shared_ptr<Player>> output;

    //! possible bug
    if (have_role)
        output = players[role];
    else
        for (auto i : players)
            output.insert(output.end(), i.second.begin(), i.second.end());

    return output;
}

vector<shared_ptr<Player>> Team::sort_players(vector<shared_ptr<Player>> team_players, bool is_sort_by_score, int week)
{
    if (is_sort_by_score)
        sort(team_players.begin(), team_players.end(),
             [week](shared_ptr<Player> p1, shared_ptr<Player> p2)
             {
            if (p1->get_avg_score(week) == p2->get_avg_score(week))
                return p1->get_name().compare(p2->get_name()) < 0;
            else
                return p1->get_avg_score(week) > p2->get_avg_score(week); });
    else
        sort(team_players.begin(), team_players.end(),
             [](shared_ptr<Player> p1, shared_ptr<Player> p2)
             { return p1->get_name().compare(p2->get_name()) < 0; });

    return team_players;
}

void Team::create_weeks()
{
    Team_status tmp_week;
    tmp_week.ga = 0;
    tmp_week.gf = 0;
    tmp_week.score = 0;

    for (size_t i = 0; i <= FINAL_WEEK; i++)
        weeks_status.insert(make_pair(i, tmp_week));
}

Team::Team(string name_, map<string, vector<shared_ptr<Player>>> players_)
{
    name = name_;
    players = players_;

    create_weeks();

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
    return weeks_status[week];
}

vector<shared_ptr<Player>> Team::get_players(bool is_sort, bool have_role, string role, int week_for_sort)
{
    vector<shared_ptr<Player>> output = get_team_players(have_role, role);

    output = sort_players(output, is_sort, week_for_sort);

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

double Team::get_sum_score(int week)
{
    return get_sum_weeks(week, [this](Team_status status) -> double
                         { return status.score; });
}

int Team::get_gf(int week)
{
    return weeks_status[week].gf;
}

int Team::get_ga(int week)
{
    return weeks_status[week].ga;
}

int Team::get_sum_gf(int week)
{
    return get_sum_weeks(week, [this](Team_status status) -> double
                         { return status.gf; });
}

int Team::get_sum_ga(int week)
{
    return get_sum_weeks(week, [this](Team_status status) -> double
                         { return status.ga; });
}

int Team::get_diff_goal(int week)
{
    return get_sum_gf(week) - get_sum_ga(week);
}
