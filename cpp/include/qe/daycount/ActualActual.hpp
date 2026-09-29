#pragma once 
#include "qe/daycount/DayCountConvention.hpp"

class ActualActual: public DayCountConvention
{
    public:
        double yearFraction(const Date& start, const Date& end) const override;
};