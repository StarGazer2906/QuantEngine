#include "qe/Schedule.hpp"
#include <stdexcept> 


Schedule::Schedule(const Date& start_date, const Date& end_date, int frequency, const USExchangeCalendar& calendar, 
BusinessDayConvention convention): start_date_(start_date), end_date_(end_date), frequency_(frequency), calendar_(calendar), 
convention_(convention)
{


    generateScheduleDates();


}

void Schedule::generateScheduleDates()
{
    if (frequency_ < 1 || frequency_ > 12)
    {
        throw std::invalid_argument("Frequency must be between 1 and 12");
    }
    
    Date vec_date = start_date_;
    dates_ = {start_date_};
    int n = 12 / frequency_;

    while (vec_date.addMonths(n) <= end_date_)
    {
        vec_date = vec_date.addMonths(n);

        switch (convention_)
        {
            case BusinessDayConvention::following:
                dates_.push_back(calendar_.following(vec_date));
                break;

            case BusinessDayConvention::modifiedFollowing:
                dates_.push_back(calendar_.modifiedFollowing(vec_date));
                break;

            case BusinessDayConvention::preceding:
                dates_.push_back(calendar_.preceding(vec_date));
                break;

            case BusinessDayConvention::modifiedPreceding:
                dates_.push_back(calendar_.modifiedPreceding(vec_date));
                break;
        }
    }
}

const std::vector<Date>& Schedule::getScheduleDates() const
{
    return dates_;
}