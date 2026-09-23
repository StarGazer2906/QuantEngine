#include "qe/date/Date.hpp"
#include <stdexcept>

bool isLeapYear(int year)
{
    return (year%400==0) || ((year%4==0) && (year%100 !=0));

}

int daysInMonth(int month, int year)
{   
    if (month <1 || month >12)
    {
        throw std::invalid_argument("Invalid Month");
    }

    if (((month<=7) && (month%2!=0)) || ((month>=8) && (month%2==0)))
        return 31;
    else if (((month<=6) && (month%2==0) && (month!=2)) || ((month>=9) && (month%2!=0)))
        return 30;
    else
    {
        if (isLeapYear(year))
            return 29;
        else
            return 28;
    }

}


void validateDate(int day, int month, int year)
{
    if (year<=0)
    {
        throw std::invalid_argument("Invalid Year");
    }
    int max_day=daysInMonth(month, year);

    if (day<1 || day > max_day)
    {
        throw std::invalid_argument("Invalid Day");
    }
}


Date:: Date(int day, int month, int year): day_(day), month_(month), year_(year)

{
    validateDate(day, month, year);
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

