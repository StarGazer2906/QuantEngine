#pragma once
#include <vector>

#include "qe/calendar/USExchangeCalendar.hpp"
#include "qe/date/Date.hpp"

enum class BusinessDayConvention
{
    following, 
    preceding,
    modifiedFollowing,
    modifiedPreceding
};


class Schedule
{
    private: 
        Date start_date_;
        Date end_date_;
        int frequency_;
        const USExchangeCalendar& calendar_;
        BusinessDayConvention convention_;
        std::vector<Date> dates_;
        void generateScheduleDates();

    public:
        Schedule(const Date& start_date, const Date& end_date, int frequency, const USExchangeCalendar& calendar,
        BusinessDayConvention convention);

        const std::vector<Date>& getScheduleDates() const; // returns a refernce to the existing vector and the caller cannot modify it
   
};