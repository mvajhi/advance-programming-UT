#include "reporter.hpp"
#include "match.hpp"

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
