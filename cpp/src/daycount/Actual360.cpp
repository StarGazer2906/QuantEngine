#include "qe/daycount/Actual360.hpp"

double Actual360::yearFraction(const Date& start, const Date& end) const
{
    int actual = end - start;
    return static_cast<double>(actual)/360.0;
}