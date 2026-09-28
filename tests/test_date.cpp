#include "qe/date/Date.hpp"
#include <cassert>
#include<stdexcept>

int main()
{
    Date today(23, 9,2026);

    // std::cout<<today.day()<<"\n";
    // std::cout<<today.month()<<"\n";
    // std::cout<<today.year()<<"\n";

    assert(today.day()==23);
    assert(today.month()==9);
    assert(today.year()==2026);

    Date leapDay(29, 2, 2024);

    assert(leapDay.day() == 29);
    assert(leapDay.month() == 2);
    assert(leapDay.year() == 2024);

    try
    {
        Date badDate(29,2,2025);
        assert(false);
    }
    catch (const std::invalid_argument&)
    {

    }

    try
    {
        Date badMonth(10, 13, 2026);
        assert(false);
    }
    catch (const std::invalid_argument&)
    {
    }

    try
    {
        Date badDay(31, 4, 2026);
        assert(false);
    }
    catch (const std::invalid_argument&)
    {
    }

    Date date1(15, 12, 2025);
    Date date2(10, 1, 2026);

    assert(date1 < date2);

    Date date3(10, 1, 2026);
    Date date4(10, 1, 2026);

    assert(!(date3 < date4));

    Date date5(20, 9, 2026);
    Date date6(25, 9, 2026);

    assert(date5 < date6);

    assert(date3==date4);
    assert(!(date1==date2));

    Date date7(15, 12, 2025);
    Date date8(16, 12, 2025);

    assert(!(date7 == date8));   // different day

    Date date9(15, 11, 2025);
    assert(!(date7 == date9));   // different month

    Date date10(15, 12, 2026);
    assert(!(date7 == date10));  // different year

    Date a(20, 9, 2026);
    Date b(25, 9, 2026);
    Date c(20, 9, 2026);

    // a is earlier than b
    assert(a < b);
    assert(!(a > b));
    assert(a <= b);
    assert(!(a >= b));

    // a and c are equal
    assert(a == c);
    assert(!(a != c));
    assert(a <= c);
    assert(a >= c);

    // a and b are not equal
    assert(a != b);

    // b is later than a
    assert(b > a);
    assert(b >= a);
    assert(!(b < a));

    // Different year
    Date d(20, 9, 2025);
    assert(d < a);
    assert(a > d);

    // Different month
    Date e(20, 8, 2026);
    assert(e < a);
    assert(a > e);

    assert(Date(1, 1, 1900).toSerial() == 1);
    assert(Date(2, 1, 1900).toSerial() == 2);
    assert(Date(31, 1, 1900).toSerial() == 31);
    assert(Date(1, 2, 1900).toSerial() == 32);
    assert(Date(1, 1, 1901).toSerial() == 366);

    Date d1(15, 12, 2025);

    int serial = d1.toSerial();

    Date d2 = Date::fromSerial(serial);

    assert(d1 == d2);

    Date d9(31, 1, 2025);
    assert(Date::fromSerial(d9.toSerial()) == d9);

    Date d8(1, 2, 2025);
    assert(Date::fromSerial(d8.toSerial()) == d8);

    Date d3(31, 12, 2025);
    assert(Date::fromSerial(d3.toSerial()) == d3);

    Date d4(1, 1, 2026);
    assert(Date::fromSerial(d4.toSerial()) == d4);

    Date d5(29, 2, 2024);
    assert(Date::fromSerial(d5.toSerial()) == d5);

    Date d6(29, 2, 2000);
    assert(Date::fromSerial(d6.toSerial()) == d6);

    Date d7(28, 2, 1900);
    assert(Date::fromSerial(d7.toSerial()) == d7);

    Date d10(28, 2, 2024);

    Date d11 = d10 + 1;
    assert(d11 == Date(29, 2, 2024));

    Date d12 = d10 + 2;
    assert(d12 == Date(1, 3, 2024));

    Date d13(31, 12, 2025);
    assert(d13 + 1 == Date(1, 1, 2026));

    Date d14(1, 1, 2024);
    assert(d14 + 59 == Date(29, 2, 2024));

    Date d15(1, 3, 2024);

    Date d16 = d15 - 1;
    assert(d16 == Date(29, 2, 2024));

    Date d17 = d15 - 2;
    assert(d17 == Date(28, 2, 2024));

    Date d18(1, 1, 2026);
    assert(d18 - 1 == Date(31, 12, 2025));

    Date d19(1, 3, 2024);
    assert(d19 - 59 == Date(2, 1, 2024));

    Date d20(10, 1, 2026);
    Date d21(1, 1, 2026);

    assert(d20 - d21 == 9);
    assert(d21 - d20 == -9);

    Date d22(1, 3, 2024);
    Date d23(28, 2, 2024);

    assert(d22 - d23 == 2);
    assert(d23 - d22 == -2);
    
    return 0;
}