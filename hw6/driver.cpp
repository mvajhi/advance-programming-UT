#include "driver.hpp"

Driver::Driver(int id_)
{
    id = id_;
}

void Driver::assign_mission(int mission_id, Mission *new_mission)
{
    if (missions.count(mission_id) != 0)
        throw DUPLICATE_DRIVER_MISSION_MASSAGE;
    
    missions.insert(make_pair(mission_id, new_mission));
}
