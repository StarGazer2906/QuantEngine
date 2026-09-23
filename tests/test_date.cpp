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
        
    return 0;
}