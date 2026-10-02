#include "qe/calendar/USExchangeCalendar.hpp"
#include <cassert>
#include <stdexcept>

int main()
{
    Date d1 = nthWeekdayOfMonth(2026, 1, 1, 3);
    assert(d1 == Date(19, 1, 2026));

    Date d2 = nthWeekdayOfMonth(2026, 2, 1, 3);
    assert(d2 == Date(16, 2, 2026));

    Date d3 = nthWeekdayOfMonth(2026, 3, 1, 5);
    assert(d3 == Date(30, 3, 2026));

    try
    {
        Date d4 = nthWeekdayOfMonth(2026, 2, 1, 5);
        assert(false);
    }
    catch (const std::invalid_argument&)
    {
    }

    Date d5 = lastWeekdayOfMonth(2026, 5, 1);
    assert(d5 == Date(25, 5, 2026));

    // Last Monday of September 2026
    Date d6 = lastWeekdayOfMonth(2026, 9, 1);
    assert(d6 == Date(28, 9, 2026));

    // Last Monday of March 2026
    Date d7 = lastWeekdayOfMonth(2026, 3, 1);
    assert(d7 == Date(30, 3, 2026));

    // Last Thursday of November 2026
    Date d8 = lastWeekdayOfMonth(2026, 11, 4);
    assert(d8 == Date(26, 11, 2026));

    // Last day is already the requested weekday
    Date d9 = lastWeekdayOfMonth(2026, 12, 4);
    assert(d9 == Date(31, 12, 2026));

    // Invalid weekday
    try
    {
        Date d10 = lastWeekdayOfMonth(2026, 5, 7);
        assert(false);
    }
    catch (const std::invalid_argument&)
    {
    }

    Date d11(4, 7, 2026);
    assert(observedFixedHoliday(d11) == Date(3, 7, 2026));

    Date d12(4, 7, 2027);
    assert(observedFixedHoliday(d12) == Date(5, 7, 2027));

    Date d13(4, 7, 2023);
    assert(observedFixedHoliday(d13) == Date(4, 7, 2023));

    assert(easterSunday(2026) == Date(5, 4, 2026));
    assert(goodFriday(2026) == Date(3, 4, 2026));

    USExchangeCalendar calendar;

    // ---- isHoliday() ----

    // New Year's Day
    assert(calendar.isHoliday(Date(1, 1, 2026)));

    // MLK Day: 3rd Monday of January
    assert(calendar.isHoliday(Date(19, 1, 2026)));

    // Washington's Birthday
    assert(calendar.isHoliday(Date(16, 2, 2026)));

    // Good Friday
    assert(calendar.isHoliday(Date(3, 4, 2026)));

    // Memorial Day
    assert(calendar.isHoliday(Date(25, 5, 2026)));

    // Juneteenth
    assert(calendar.isHoliday(Date(19, 6, 2026)));

    // Independence Day observed: July 4, 2026 is Saturday
    assert(calendar.isHoliday(Date(3, 7, 2026)));

    // Labor Day
    assert(calendar.isHoliday(Date(7, 9, 2026)));

    // Thanksgiving
    assert(calendar.isHoliday(Date(26, 11, 2026)));

    // Christmas
    assert(calendar.isHoliday(Date(25, 12, 2026)));


    // ---- Dates that should NOT be holidays ----

    // Ordinary weekday
    assert(!calendar.isHoliday(Date(2, 1, 2026)));

    // July 4 itself is Saturday; the observed holiday is July 3
    assert(!calendar.isHoliday(Date(4, 7, 2026)));


    // ---- isBusinessDay() ----

    // Ordinary weekday
    assert(calendar.isBusinessDay(Date(2, 1, 2026)));

    // Weekend
    assert(!calendar.isBusinessDay(Date(4, 1, 2026)));

    // Holiday
    assert(!calendar.isBusinessDay(Date(19, 1, 2026)));

    // Observed Independence Day
    assert(!calendar.isBusinessDay(Date(3, 7, 2026)));

    // ---- Different years ----

    // MLK Day 2027: January 18
    assert(calendar.isHoliday(Date(18, 1, 2027)));

    // Washington's Birthday 2027: February 15
    assert(calendar.isHoliday(Date(15, 2, 2027)));

    // Good Friday 2027: March 26
    assert(calendar.isHoliday(Date(26, 3, 2027)));

    // Thanksgiving 2027: November 25
    assert(calendar.isHoliday(Date(25, 11, 2027)));

    // New Year's Day 2022 was Saturday,
    // so the observed exchange holiday was Friday, Dec 31, 2021.
    assert(calendar.isHoliday(Date(31, 12, 2021)));

    assert(!calendar.isHoliday(Date(1, 1, 2022)));

    return 0;
}