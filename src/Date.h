// Source: http://www.ece.uc.edu/~franco/C321/html/date.html
//

#ifndef Date_hpp
#define Date_hpp

#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <chrono>
#include <map>


class Date
{
    public:
        static int monthLength[];
        Date(const int day, const int month, const int year);
        Date(const std::string dateDB);
        Date();

        int getMonth() const;
        void setMonth(const int month);

        int getDay() const;
        void setDay(const int day);

        int getYear() const;
        void setYear(const int year);

        int daysSoFar() const;
    
        void addDay(int days);
        void addMonth(int months);
        void addYear(int years);
    
        std::string dateToDB() const;

        friend std::ostream& operator<< (std::ostream& stream, const Date& date);
        friend std::istream& operator>> (std::istream& stream, Date& date);

    private:
        int _month, _day, _year;
};


#endif /* Date_hpp */
