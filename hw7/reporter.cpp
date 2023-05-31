#include "reporter.hpp"
#include "match.hpp"
#include "player.hpp"
#include <cmath>

string float_to_string(double number)
{
    number = round(number * 10) / 10;
    string output = to_string(number);
    size_t decimal_pos = output.find('.');
    if (decimal_pos != string::npos && output.size() > decimal_pos + 2)
        output = output.substr(0, decimal_pos + 2);
    return output;
}

Massage_reporter::Massage_reporter(string massage_)
{
    massage = massage_;
}

void Massage_reporter::cli_report()
{
    cout << massage;
}

Match_reporter::Match_reporter(vector<shared_ptr<Match>> matches_)
{
    matches = matches_;
}

void Match_reporter::cli_report()
{
    for (auto match : matches)
    {
        cout << match->team1.first->get_name() << " " << match->team1.second;
        cout << " | ";
        cout << match->team2.first->get_name() << " " << match->team2.second;
        cout << endl;
    }
}

string Best_team_reporter::convert_player_to_cli_output(string role, int index)
{
    return players[role][index]->get_name() + " | " + float_to_string(players[role][index]->get_score(week));
}

Best_team_reporter::Best_team_reporter(map<string, vector<shared_ptr<Player>>> players_, int week_)
{
    players = players_;
    week = week_;
}

void Best_team_reporter::cli_report()
{
    cout << "team of the week:\n";
    cout << "GoalKeeper: " << convert_player_to_cli_output(GK) << endl;
    cout << "Defender 1: " << convert_player_to_cli_output(DF, 0) << endl;
    cout << "Defender 2: " << convert_player_to_cli_output(DF, 1) << endl;
    cout << "Midfielder: " << convert_player_to_cli_output(MF) << endl;
    cout << "Forward: " << convert_player_to_cli_output(FW) << endl;
}

string Team_player_reporter::convert_player_to_string(shared_ptr<Player> player)
{
    string output;

    output += "name: " + player->get_name() + " | ";
    output += "role: " + player->get_role() + " | ";
    output += "score: " + float_to_string(player->get_avg_score(week)) ;

    return output;
}

Team_player_reporter::Team_player_reporter(vector<shared_ptr<Player>> players_, int week_)
{
    players = players_;
    week = week_;
}

void Team_player_reporter::cli_report()
{
    cout << "list of players:\n";
    for (size_t i = 0; i < players.size(); i++)
        cout << i + 1 << ". " << convert_player_to_string(players[i]) << endl;
}

string Team_list_reporter::convert_team_to_string(shared_ptr<Team> team)
{
    string output = "";

    output += team->get_name() + ": ";
    output += "score: " + float_to_string(team->get_sum_score(week)) + " | ";
    output += "GF: " + to_string(team->get_gf(week)) + " | ";
    output += "GA: " + to_string(team->get_ga(week));

    return output;
}

Team_list_reporter::Team_list_reporter(vector<shared_ptr<Team>> teams_, int week_)
{
    teams = teams_;
    week = week_;
}

void Team_list_reporter::cli_report()
{
    cout << "league standings:\n";
    for (size_t i = 0; i < teams.size(); i++)
        cout << i + 1 << ". " << convert_team_to_string(teams[i]) << endl;
}
