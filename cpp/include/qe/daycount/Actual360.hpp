#pragma once
#include "qe/daycount/DayCountConvention.hpp"

class Actual360: public DayCountConvention
{
    public:
        double yearFraction(const Date& start, const Date& end) const override;
};