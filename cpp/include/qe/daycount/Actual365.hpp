#pragma once
#include "qe/daycount/DayCountConvention.hpp"

class Actual365: public DayCountConvention //inheritance - Actual365 inherits from DayCountConvention

{
    public:
         
         double yearFraction(const Date& start, const Date& end) const override; //the "override" keyword tells C++ that we are implementing the virtual function
                                                                                 // from DayCountConvention

};