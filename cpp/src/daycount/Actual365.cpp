#include "qe/daycount/Actual365.hpp"
#include <stdexcept>

double Actual365::yearFraction(const Date& start, const Date& end) const
{
    int actual=end-start;
    return static_cast<double>(actual)/365.0;
}