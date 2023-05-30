#ifndef ADVANCE_PROGRAMMING_UT_FANTASYTEAM_HPP
#define ADVANCE_PROGRAMMING_UT_FANTASYTEAM_HPP
#include "define.hpp"
#include "player.hpp"
class FantasyTeam
{
private:
    string name;
    int week_num;
    map<string,vector<Player*>> players;
public:
    double get_score(int week_num);
    bool can_add_player(string post);
    bool have_this_player(string name);
    void add_player(Player* target_player); /* in here we can use string of name isntead of a Player*/
    void remove_player(string name);
    void show_fantasy_team();

};
#endif //ADVANCE_PROGRAMMING_UT_FANTASYTEAM_HPP
