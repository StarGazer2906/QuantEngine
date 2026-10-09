#include "qe/date/Date.hpp"
#include "qe/Calendar.hpp"
#include <stdexcept>



void validateDate(int day, int month, int year)
{
    if (year<=0)
    {
        throw std::invalid_argument("Invalid Year");
    }
    int max_day=daysInMonth(month, year);

    if (day<1 || day > max_day)
    {
        throw std::invalid_argument("Invalid Day");
    }
}


Date:: Date(int day, int month, int year): day_(day), month_(month), year_(year)

{
    validateDate(day, month, year);
}

int Date::day() const
{
    return day_;
}

int Date::month() const
{
    return month_;
}

int Date::year() const
{
    return year_;
}

bool Date::operator<(const Date& other) const
{
    if(year_ !=other.year_)
        return year_ <other.year_;
    if (month_ != other.month_)
        return month_ <other.month_;
    return day_ <other.day_;
}

bool Date::operator==(const Date& other) const
{
    return ((year_==other.year_)&&(month_==other.month_)&&(day_==other.day_));
}

bool Date::operator!=(const Date& other) const
{
    return (!(*this == other));
}

bool Date::operator>(const Date& other) const
{
    return (!((*this<other)||(*this == other)));
}

bool Date::operator<=(const Date& other) const
{
    return ((*this==other)||(*this<other));
}

bool Date::operator>=(const Date& other) const
{
    return (!(*this<other));
}

int Date::toSerial() const
{
    int anchor_yr=1900;
    int num_yrs=year_-anchor_yr;
    int leap_yrs=0;
    for (int i=anchor_yr; i<year_;i++)
    {
        if (isLeapYear(i))
            leap_yrs+=1;
    }
    int tot_days=0;
    for (int i=1; i<month_; i++)
    {
        int days=daysInMonth(i, year_);
        tot_days+=days;
    }
    return leap_yrs+(num_yrs*365) + day_+tot_days;

}


Date Date::fromSerial(int serial) 
{
    int anchor_yr=1900;
    int new_serial = serial;
    int i=1900;
    while (true)
    {
        if (new_serial<=daysInYear(i))
            break;
        else
        {
            new_serial=new_serial-daysInYear(i);
            i++;
        }
    }
    int j = 1;

    while (true)
    {
        if (new_serial <= daysInMonth(j, i))
            break;
        else
        {
            new_serial = new_serial - daysInMonth(j, i);
            j++;
        }
    }

    // new_serial = day
    // j = month
    // i = year
    return Date(new_serial, j, i);
    
}

Date Date::operator+(int days) const
{
    return Date::fromSerial(toSerial() + days); // we can skip writing *this inside a member class function
} 

Date Date::operator-(int days) const
{
    return Date::fromSerial(toSerial() - days); 
} 

int Date::operator-(const Date& other) const
{
    return toSerial() - other.toSerial();
}

int Date::dayOfWeek() const
{
    int serial =toSerial();
    return serial%7; // 0 = Sunday, .., 6 = Saturday
}

bool Date::isWeekend() const
{
    int day=dayOfWeek();
    return (day==6)||(day==0);
}

Date Date::addMonths(int months) const
{

int mth_new = month_ + months;
int yr_new = year_;

if (mth_new % 12 != 0)
{
    if (day_ > daysInMonth(mth_new % 12 , yr_new + (mth_new - 1)/ 12))
    {
        return Date(daysInMonth(mth_new % 12 , yr_new + (mth_new - 1) / 12), mth_new % 12, yr_new + (mth_new - 1) / 12);
    }
        
    return Date(day_, mth_new % 12, yr_new + (mth_new - 1) / 12);
}
else
{
    return Date(day_, 12, yr_new + (mth_new - 1) / 12);
}

}