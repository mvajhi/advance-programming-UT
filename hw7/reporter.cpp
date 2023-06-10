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

void Massage_reporter::get_cli_report()
{
    cout << massage;
}

Match_reporter::Match_reporter(vector<shared_ptr<Match>> matches_)
{
    for (auto i : matches_)
        matches.push_back(i->get_match_data());
}

void Match_reporter::get_cli_report()
{
    for (auto match : matches)
    {
        cout << match.team1.first << " " << match.team1.second;
        cout << " | ";
        cout << match.team2.first << " " << match.team2.second;
        cout << endl;
    }
}

string Best_team_reporter::convert_player_to_cli_output(string role,
                                                        int index)
{
    return players[role][index]->get_name() + " | " + "score: " +
           float_to_string(players[role][index]->get_score(week));
}

Best_team_reporter::Best_team_reporter(
    map<string, vector<shared_ptr<Player>>> players_, int week_)
{
    players = players_;
    week = week_;
}

void Best_team_reporter::get_cli_report()
{
    cout << "team of the week:\n";
    cout << "GoalKeeper: " << convert_player_to_cli_output(GK) << endl;
    cout << "Defender 1: " << convert_player_to_cli_output(DF, 0) << endl;
    cout << "Defender 2: " << convert_player_to_cli_output(DF, 1) << endl;
    cout << "Midfielder: " << convert_player_to_cli_output(MF) << endl;
    cout << "Forward: " << convert_player_to_cli_output(FW) << endl;
}

string Team_player_reporter::convert_player_to_string(
    shared_ptr<Player> player)
{
    string output;

    output += "name: " + player->get_name() + " | ";
    output += "role: " + player->get_role() + " | ";
    output += "score: " +
              float_to_string(player->get_avg_score(week)) + " | ";

    if (player->get_role() != GK)
    {
        output += "goal: " + to_string(player->get_goal(week)) + " | ";
        output += "assist: " + to_string(player->get_assist(week)) + " | ";
    }

    if (player->get_role() != FW)
        output += "clean sheet: " +
                  to_string(player->get_clean_sheet(week)) + " | ";

    // remove last " | "
    for (size_t i = 0; i < string(" | ").size(); i++)
        output.pop_back();

    return output;
}

Team_player_reporter::Team_player_reporter(
    vector<shared_ptr<Player>> players_, int week_)
{
    players = players_;
    week = week_;
}

void Team_player_reporter::get_cli_report()
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

Team_list_reporter::Team_list_reporter(
    vector<shared_ptr<Team>> teams_, int week_)
{
    teams = teams_;
    week = week_;
}

void Team_list_reporter::get_cli_report()
{
    cout << "league standings:\n";
    for (size_t i = 0; i < teams.size(); i++)
        cout << i + 1 << ". " << convert_team_to_string(teams[i]) << endl;
}

string User_ranks_report::convert_collection_to_string(User_ranking_data user)
{
    string output = "";

    output += "team_name: " + user.name + " | ";
    output += "point: " + float_to_string(user.point);

    return output;
}

User_ranks_report::User_ranks_report(vector<User_ranking_data> collection_)
{
    collection = collection_;
}

void User_ranks_report::get_cli_report()
{
    if (collection.size() == 0)
        Massage_reporter(EMPTY_MASSAGE + "\n").get_cli_report();

    for (size_t i = 0; i < collection.size(); i++)
        cout << i + 1 << ". "
             << convert_collection_to_string(collection[i]) << endl;
}

void FantasyTeamReporter::sort_defender()
{
    string buffer;
    if (target_team.df1.compare(target_team.df2) < 0)
    {
        buffer = target_team.df1;
        target_team.df1 = target_team.df2;
        target_team.df2 = buffer;
    }
}

vector<string> FantasyTeamReporter::create_team_player_output()
{
    vector<string> output;

    output.push_back("fantasy_team: " + target_team.team_name);
    output.push_back("Goalkeeper: " + target_team.gk);
    output.push_back("Defender1: " + target_team.df1);
    output.push_back("Defender2: " + target_team.df2);
    output.push_back("Midfielder: " + target_team.mf);
    output.push_back("Striker: " + target_team.fw);

    return output;
}

void FantasyTeamReporter::add_captain_in_output(vector<string> &output)
{
    if (!target_team.have_captain)
        return;
    for (auto &&line : output)
        if (line.find(target_team.captain_name) != string::npos)
            line += " (CAPTAIN)";
}

FantasyTeamReporter::FantasyTeamReporter(Fantasy_team_data target_team_)
{
    target_team = target_team_;

    sort_defender();
}

void FantasyTeamReporter::get_cli_report()
{
    if (target_team.is_full == false)
    {
        Massage_reporter(EMPTY_MASSAGE + "\n").get_cli_report();
        return;
    }

    vector<string> output = create_team_player_output();
    add_captain_in_output(output);

    for (auto line : output)
        cout << line << endl;

    cout << "Total Points: " << float_to_string(target_team.total_score) << endl;
    cout << "Total Cost: " << target_team.total_cost << endl;
}