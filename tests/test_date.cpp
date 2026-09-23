#include "qe/date/Date.hpp"
#include <cassert>

int main()
{
    Date today(23, 9,2026);

    // std::cout<<today.day()<<"\n";
    // std::cout<<today.month()<<"\n";
    // std::cout<<today.year()<<"\n";

    assert(today.day()==23);
    assert(today.month()==9);
    assert(today.year()==2026);
    
    return 0;
}