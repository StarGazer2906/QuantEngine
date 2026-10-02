#include "qe/calendar/USExchangeCalendar.hpp"
#include "qe/Calendar.hpp"
#include <stdexcept>
#include <set>


Date nthWeekdayOfMonth(int year, int month, int weekday, int n)
{
    if ((month < 1 || month > 12) || (n < 1 || n > 5) || (weekday < 0 || weekday > 6))
    {
        throw std::invalid_argument("Invalid nth Weekday Request");
    }
    
    Date d1(1, month, year);
    int day = d1.dayOfWeek();

    int req_day= d1.toSerial() + (weekday - day + 7) % 7 + (n - 1) * 7;

    Date d2(daysInMonth(month, year), month, year);
    int end_day_month = d2.toSerial();

    if (req_day>end_day_month)
        {
            throw std::invalid_argument("Invalid nth Weekday Request");
        }
        
    return Date::fromSerial(req_day);
    
}

Date lastWeekdayOfMonth(int year, int month, int weekday)
{   
    if ((weekday<0)||(weekday>6))
    {
        throw std::invalid_argument("Invalid Weekday");
    }
    
    int last_day = daysInMonth(month, year);
    Date d1(last_day, month, year);
    int last_weekday = d1.dayOfWeek(); // returns which day of the week is the last day

    int serial = d1.toSerial();

    return Date::fromSerial(serial + (weekday - last_weekday -7)%7);

}

Date observedFixedHoliday(const Date& holiday)
{
    int day=holiday.dayOfWeek();
    if (day==6)
    {
        return holiday - 1;
    }
    else if (day==0)
    {
        return holiday + 1;
    }

    return holiday;

}


Date easterSunday(int year)
{
    int a = year % 19;
    int b = year / 100;
    int c = year % 100;
    int d = b / 4;
    int e = b % 4;
    int f = (b + 8) / 25;
    int g = (b - f + 1) / 3;
    int h = (19 * a + b - d - g + 15) % 30;
    int i = c / 4;
    int k = c % 4;
    int l = (32 + 2 * e + 2 * i - h - k) % 7;
    int m = (a + 11 * h + 22 * l) / 451;

    int month = (h + l - 7 * m + 114) / 31;
    int day = ((h + l - 7 * m + 114) % 31) + 1;

    return Date(day, month, year);
}

Date goodFriday(int year)
{
    return easterSunday(year)-2;
}

void addHolidaysForYear(std::set<Date>& holidays, int year)
{

    holidays.insert(observedFixedHoliday(Date(1, 1, year)));    // New Year's Day
    holidays.insert(nthWeekdayOfMonth(year, 1, 1, 3));          // MLK Day
    holidays.insert(nthWeekdayOfMonth(year, 2, 1, 3));          // Washington's Birthday
    holidays.insert(goodFriday(year));                          // Good Friday
    holidays.insert(lastWeekdayOfMonth(year, 5, 1));            // Memorial Day
    holidays.insert(observedFixedHoliday(Date(19, 6, year)));   // Juneteenth
    holidays.insert(observedFixedHoliday(Date(4, 7, year)));    // Independence Day
    holidays.insert(nthWeekdayOfMonth(year, 9, 1, 1));          // Labor Day
    holidays.insert(nthWeekdayOfMonth(year, 11, 4, 4));         // Thanksgiving
    holidays.insert(observedFixedHoliday(Date(25, 12, year)));  // Christmas

}

// Member function Definitions

bool USExchangeCalendar::isHoliday(const Date& date) const
{
    int year = date.year();
    
    std::set<Date> holidays;

    addHolidaysForYear(holidays, year);
    addHolidaysForYear(holidays, year+1);

    return holidays.find(date) != holidays.end();

}
        
bool USExchangeCalendar::isBusinessDay(const Date& date) const
{

    return !(date.isWeekend() || isHoliday(date));
}