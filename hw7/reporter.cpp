#include "reporter.hpp"
#include "match.hpp"
#include "player.hpp"
#include <cmath>

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
    double score = players[role][index]->get_score(week);
    score = round(score * 10) / 10;
    string score_str = to_string(score);
    size_t decimal_pos = score_str.find('.');
    if (decimal_pos != string::npos && score_str.size() > decimal_pos + 2)
        score_str = score_str.substr(0, decimal_pos + 2);

    return players[role][index]->get_name() + " | " + score_str;
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