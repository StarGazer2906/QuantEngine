#include "qe/Calendar.hpp"
#include <stdexcept>


bool isLeapYear(int year)  //Checks if a given year is a leap year
{
    return (year%400==0) || ((year%4==0) && (year%100 !=0));

}

int daysInMonth(int month, int year) //returns the number of days in a month specific to year
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

int daysInYear(int yr) // returns the nuber of days in a year
{
    if (isLeapYear(yr))
        return 366;
    return 365;
}

