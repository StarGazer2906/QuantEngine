#include "qe/date/Date.hpp"

Date:: Date(int day, int month, int year): day_(day), month_(month), year_(year)

{

}

int Date::day() const
{
    return day_;
}

int Date::month() const
{
    return month_;
}

int Date::year() const
{
    return year_;
}