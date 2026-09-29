#pragma once //header protection that tells C++ that include this header only once per compilation unit
#include "qe/date/Date.hpp"

class DayCountConvention
{
    public:
    virtual double yearFraction(const Date& start, const Date& end) const=0;
};