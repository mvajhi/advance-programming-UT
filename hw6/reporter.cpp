#include "reporter.hpp"

Massage_reporter::Massage_reporter(string massage_)
{
    massage = massage_;
}

void Massage_reporter::cli_report()
{
    cout << massage;
}
