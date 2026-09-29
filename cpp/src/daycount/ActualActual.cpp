#include "qe/daycount/ActualActual.hpp"
#include "qe/Calendar.hpp"

double ActualActual::yearFraction(const Date& start, const Date& end) const
{
    if (start.year()==end.year())  //Case: when both the dates have same year
       {
        int year=start.year();
        int actual = end - start;
        return static_cast<double>(actual)/static_cast<double>(daysInYear(year));
       } 

   //Case: when both the dates have different year

    double start_yr_frac= static_cast<double>(Date(1, 1, start.year() +1)- start)/static_cast<double>(daysInYear(start.year()));
    double end_yr_frac=static_cast<double>(end - Date(1,1,end.year()))/ static_cast<double>(daysInYear(end.year()));
    return start_yr_frac + (end.year() - start.year() -1) + end_yr_frac;

}