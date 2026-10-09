
#include <cassert>
#include <iostream>
#include <vector>

#include "qe/Schedule.hpp"

int main()
{
    USExchangeCalendar calendar;

    // Test 1: Quarterly schedule with Following convention.
    // January 1, 2027 is New Year's Day, so it moves to January 4.
    Schedule quarterlySchedule(
        Date(1, 1, 2026),
        Date(1, 1, 2027),
        4,
        calendar,
        BusinessDayConvention::following
    );

    const std::vector<Date>& quarterlyDates =
        quarterlySchedule.getScheduleDates();

    assert(quarterlyDates.size() == 5);
    assert(quarterlyDates[0] == Date(1, 1, 2026));
    assert(quarterlyDates[1] == Date(1, 4, 2026));
    assert(quarterlyDates[2] == Date(1, 7, 2026));
    assert(quarterlyDates[3] == Date(1, 10, 2026));
    assert(quarterlyDates[4] == Date(4, 1, 2027));


    // Test 2: Following convention.
    // Christmas 2026 is Friday, December 25.
    // The next business day is Monday, December 28.
    Schedule followingSchedule(
        Date(25, 11, 2026),
        Date(25, 1, 2027),
        12,
        calendar,
        BusinessDayConvention::following
    );

    const std::vector<Date>& followingDates =
        followingSchedule.getScheduleDates();

    assert(followingDates.size() == 3);
    assert(followingDates[0] == Date(25, 11, 2026));
    assert(followingDates[1] == Date(28, 12, 2026));
    assert(followingDates[2] == Date(25, 1, 2027));


    // Test 3: Preceding convention.
    // Christmas 2026 moves back to Thursday, December 24.
    Schedule precedingSchedule(
        Date(25, 11, 2026),
        Date(25, 1, 2027),
        12,
        calendar,
        BusinessDayConvention::preceding
    );

    const std::vector<Date>& precedingDates =
        precedingSchedule.getScheduleDates();

    assert(precedingDates.size() == 3);
    assert(precedingDates[0] == Date(25, 11, 2026));
    assert(precedingDates[1] == Date(24, 12, 2026));
    assert(precedingDates[2] == Date(25, 1, 2027));


    // Test 4: The start date remains unadjusted.
    // January 1, 2026 is a holiday, but the start date is preserved.
    Schedule holidayStartSchedule(
        Date(1, 1, 2026),
        Date(1, 4, 2026),
        4,
        calendar,
        BusinessDayConvention::following
    );

    const std::vector<Date>& holidayStartDates =
        holidayStartSchedule.getScheduleDates();

    assert(holidayStartDates.size() == 2);
    assert(holidayStartDates[0] == Date(1, 1, 2026));
    assert(holidayStartDates[1] == Date(1, 4, 2026));


    std::cout << "All Schedule tests passed.\n";

    return 0;
}
