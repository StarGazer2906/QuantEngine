#include "qe/daycount/Thirty360.hpp"
#include "qe/Calendar.hpp"

bool isLastDayOfFeb(const Date& d)  //checks if a particular date is the last day of February
{
    if ((d.month()==2)&&(isLeapYear(d.year()))&&(d.day()==29))
    {
        return true;
    }
    else if ((d.month()==2)&&(!isLeapYear(d.year()))&&(d.day()==28))
    {
        return true;
    }
    return false;
}

//Implementation of the 30/360 US (NASD) convention (also commonly called Bond Basis)

double Thirty360::yearFraction(const Date& start, const Date& end) const
{
    int d1=start.day();
    int m1=start.month();
    int y1=start.year();

    int d2=end.day();
    int m2=end.month();
    int y2=end.year();

    if ((d1==31)||(isLastDayOfFeb(start)))
    {
        d1=30;
    }
    if (((d2==31)&&(d1>29))||(isLastDayOfFeb(start)&&(isLastDayOfFeb(end))))
    {
        d2=30;
    }

    return static_cast<double>(360*(y2-y1) + 30*(m2-m1) + (d2-d1))/360.0;
}