#ifndef QE_DATE_HPP
#define QE_DATE_HPP

class Date
{
    private:
        int day_;
        int month_;
        int year_;

    public:
        Date(int day, int month, int year);
        int day() const;
        int month() const;
        int year() const; // These are acessors through which the day, month and year (with integer return 
                                    // type) can be fetched and 'const' ensures this does not modify the Date object
                              // these are called the accessors or the getters    

        bool operator<(const Date& other) const;
        bool operator==(const Date& other) const;
        bool operator!=(const Date& other) const;
        bool operator>(const Date& other) const;
        bool operator>=(const Date& other) const;
        bool operator<=(const Date& other) const;

        int toSerial() const;
        static Date fromSerial(int serial);

        Date operator+(int days) const;
        Date operator-(int days) const;
        int operator-(const Date& other) const; //operator overloading with same symbol but distinguished based on parameter list

};
#endif