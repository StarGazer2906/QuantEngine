#pragma once

#include "qe/date/Date.hpp"

Date nthWeekdayOfMonth(int year, int month, int weekday, int n);

Date lastWeekdayOfMonth(int year, int month, int weekday);

Date observedFixedHoliday(const Date& holiday);

Date easterSunday(int year);

Date goodFriday(int year);


class USExchangeCalendar
{

    public:
        
        bool isHoliday(const Date& date) const;
        bool isBusinessDay(const Date& date) const;
        
};