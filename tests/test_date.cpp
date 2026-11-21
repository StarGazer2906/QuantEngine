// Tests for Date (qe/date/Date.hpp) and the date utilities (qe/Calendar.hpp).
// Ported from the old assert-based test_date.cpp (Checkpoint 1.1, Step B).

#include <gtest/gtest.h>       // GoogleTest: TEST, EXPECT_EQ, EXPECT_THROW, ...
#include <ostream>             // std::ostream, used by PrintTo below
#include <stdexcept>           // std::invalid_argument

#include "qe/Calendar.hpp"     // isLeapYear, daysInMonth
#include "qe/date/Date.hpp"

// When a test fails, GoogleTest prints the values it compared.
// This function teaches it to print a Date as day/month/year
// (without it, a failing Date would be printed as raw bytes).
void PrintTo(const Date& d, std::ostream* os)
{
    *os << d.day() << "/" << d.month() << "/" << d.year();
}

// ---------------------------------------------------------------------
// Date utilities
// ---------------------------------------------------------------------

TEST(DateUtilsTest, LeapYears)
{
    EXPECT_FALSE(isLeapYear(1900));   // divisible by 100 but not by 400
    EXPECT_TRUE(isLeapYear(2000));    // divisible by 400
    EXPECT_TRUE(isLeapYear(2024));    // divisible by 4
    EXPECT_FALSE(isLeapYear(2025));
}

TEST(DateUtilsTest, DaysInFebruary)
{
    EXPECT_EQ(daysInMonth(2, 2024), 29);
    EXPECT_EQ(daysInMonth(2, 2025), 28);
}

// ---------------------------------------------------------------------
// Construction
// ---------------------------------------------------------------------

TEST(DateTest, StoresDayMonthYear)
{
    Date today(23, 9, 2026);
    EXPECT_EQ(today.day(), 23);
    EXPECT_EQ(today.month(), 9);
    EXPECT_EQ(today.year(), 2026);
}

TEST(DateTest, AcceptsLeapDayInLeapYear)
{
    Date leapDay(29, 2, 2024);
    EXPECT_EQ(leapDay.day(), 29);
    EXPECT_EQ(leapDay.month(), 2);
    EXPECT_EQ(leapDay.year(), 2024);
}

TEST(DateTest, RejectsInvalidDates)
{
    EXPECT_THROW(Date(29, 2, 2025), std::invalid_argument);   // 2025 is not a leap year
    EXPECT_THROW(Date(10, 13, 2026), std::invalid_argument);  // there is no month 13
    EXPECT_THROW(Date(31, 4, 2026), std::invalid_argument);   // April has only 30 days
}

// ---------------------------------------------------------------------
// Comparison operators
// ---------------------------------------------------------------------

TEST(DateTest, EarlierDateComparesLess)
{
    Date a(20, 9, 2026);
    Date b(25, 9, 2026);

    EXPECT_TRUE(a < b);
    EXPECT_TRUE(a <= b);
    EXPECT_TRUE(a != b);
    EXPECT_FALSE(a > b);
    EXPECT_FALSE(a >= b);
    EXPECT_FALSE(a == b);

    EXPECT_TRUE(b > a);
    EXPECT_TRUE(b >= a);
    EXPECT_FALSE(b < a);
}

TEST(DateTest, EqualDatesCompareEqual)
{
    Date a(20, 9, 2026);
    Date c(20, 9, 2026);

    EXPECT_TRUE(a == c);
    EXPECT_FALSE(a != c);
    EXPECT_TRUE(a <= c);
    EXPECT_TRUE(a >= c);
    EXPECT_FALSE(a < c);
    EXPECT_FALSE(a > c);
}

TEST(DateTest, ComparisonUsesYearThenMonthThenDay)
{
    Date a(20, 9, 2026);
    EXPECT_TRUE(Date(20, 9, 2025) < a);    // earlier year
    EXPECT_TRUE(Date(20, 8, 2026) < a);    // earlier month
    EXPECT_TRUE(Date(15, 12, 2025) < Date(10, 1, 2026));   // later month but earlier year

    Date x(15, 12, 2025);
    EXPECT_FALSE(x == Date(16, 12, 2025));   // different day
    EXPECT_FALSE(x == Date(15, 11, 2025));   // different month
    EXPECT_FALSE(x == Date(15, 12, 2026));   // different year
}

// ---------------------------------------------------------------------
// Serial numbers (day count since 31/12/1899, so 1/1/1900 = 1)
// ---------------------------------------------------------------------

TEST(DateTest, ToSerialKnownValues)
{
    EXPECT_EQ(Date(1, 1, 1900).toSerial(), 1);
    EXPECT_EQ(Date(2, 1, 1900).toSerial(), 2);
    EXPECT_EQ(Date(31, 1, 1900).toSerial(), 31);
    EXPECT_EQ(Date(1, 2, 1900).toSerial(), 32);
    EXPECT_EQ(Date(1, 1, 1901).toSerial(), 366);
    EXPECT_EQ(Date(1, 1, 2026).toSerial(), 46022);
}

TEST(DateTest, FromSerialUndoesToSerial)
{
    // Round trip: date -> serial -> date must give back the same date.
    EXPECT_EQ(Date::fromSerial(Date(15, 12, 2025).toSerial()), Date(15, 12, 2025));
    EXPECT_EQ(Date::fromSerial(Date(31, 1, 2025).toSerial()), Date(31, 1, 2025));
    EXPECT_EQ(Date::fromSerial(Date(1, 2, 2025).toSerial()), Date(1, 2, 2025));
    EXPECT_EQ(Date::fromSerial(Date(31, 12, 2025).toSerial()), Date(31, 12, 2025));
    EXPECT_EQ(Date::fromSerial(Date(1, 1, 2026).toSerial()), Date(1, 1, 2026));
    EXPECT_EQ(Date::fromSerial(Date(29, 2, 2024).toSerial()), Date(29, 2, 2024));
    EXPECT_EQ(Date::fromSerial(Date(29, 2, 2000).toSerial()), Date(29, 2, 2000));
    EXPECT_EQ(Date::fromSerial(Date(28, 2, 1900).toSerial()), Date(28, 2, 1900));
}

// ---------------------------------------------------------------------
// Adding and subtracting days
// ---------------------------------------------------------------------

TEST(DateTest, AddDays)
{
    Date d(28, 2, 2024);
    EXPECT_EQ(d + 1, Date(29, 2, 2024));                  // leap day
    EXPECT_EQ(d + 2, Date(1, 3, 2024));
    EXPECT_EQ(Date(31, 12, 2025) + 1, Date(1, 1, 2026));  // year end
    EXPECT_EQ(Date(1, 1, 2024) + 59, Date(29, 2, 2024));
}

TEST(DateTest, SubtractDays)
{
    Date d(1, 3, 2024);
    EXPECT_EQ(d - 1, Date(29, 2, 2024));
    EXPECT_EQ(d - 2, Date(28, 2, 2024));
    EXPECT_EQ(Date(1, 1, 2026) - 1, Date(31, 12, 2025));
    EXPECT_EQ(Date(1, 3, 2024) - 59, Date(2, 1, 2024));
}

TEST(DateTest, DifferenceInDays)
{
    EXPECT_EQ(Date(10, 1, 2026) - Date(1, 1, 2026), 9);
    EXPECT_EQ(Date(1, 1, 2026) - Date(10, 1, 2026), -9);
    EXPECT_EQ(Date(1, 3, 2024) - Date(28, 2, 2024), 2);   // crosses 29 Feb
    EXPECT_EQ(Date(28, 2, 2024) - Date(1, 3, 2024), -2);
}

// ---------------------------------------------------------------------
// Day of week (0 = Sunday, 1 = Monday, ..., 6 = Saturday)
// ---------------------------------------------------------------------

TEST(DateTest, DayOfWeekAndWeekend)
{
    EXPECT_EQ(Date(1, 1, 1900).dayOfWeek(), 1);   // Monday
    EXPECT_FALSE(Date(1, 1, 1900).isWeekend());

    EXPECT_EQ(Date(6, 1, 1900).dayOfWeek(), 6);   // Saturday
    EXPECT_TRUE(Date(6, 1, 1900).isWeekend());

    EXPECT_EQ(Date(7, 1, 1900).dayOfWeek(), 0);   // Sunday
    EXPECT_TRUE(Date(7, 1, 1900).isWeekend());

    EXPECT_EQ(Date(8, 1, 1900).dayOfWeek(), 1);   // Monday
    EXPECT_FALSE(Date(8, 1, 1900).isWeekend());
}

// ---------------------------------------------------------------------
// addMonths (positive months only for now; negative months are bug H2)
// ---------------------------------------------------------------------

TEST(DateTest, AddMonthsSimple)
{
    EXPECT_EQ(Date(15, 1, 2026).addMonths(1), Date(15, 2, 2026));
    EXPECT_EQ(Date(15, 1, 2026).addMonths(3), Date(15, 4, 2026));
    EXPECT_EQ(Date(15, 1, 2026).addMonths(12), Date(15, 1, 2027));
}

TEST(DateTest, AddMonthsCrossesYearEnd)
{
    EXPECT_EQ(Date(15, 11, 2026).addMonths(3), Date(15, 2, 2027));
    EXPECT_EQ(Date(15, 12, 2026).addMonths(1), Date(15, 1, 2027));
}

TEST(DateTest, AddMonthsClampsToMonthEnd)
{
    // If the target month is shorter, the day is moved back to its last day.
    EXPECT_EQ(Date(31, 1, 2026).addMonths(1), Date(28, 2, 2026));   // non-leap year
    EXPECT_EQ(Date(31, 1, 2028).addMonths(1), Date(29, 2, 2028));   // leap year
    EXPECT_EQ(Date(31, 3, 2026).addMonths(1), Date(30, 4, 2026));   // April has 30 days
}
