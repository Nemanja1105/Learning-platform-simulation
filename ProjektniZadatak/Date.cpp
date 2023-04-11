#include "Date.h"
#include<ctime>
#include<iomanip>
#include<string>
#include<sstream>

#pragma warning(disable:4996)

namespace learningPlatform
{
    Date::Date() : day(1), month(1), year(2001) {}
    Date::Date(int day, int month, int year) : day(day), month(month), year(year) {};

    const std::array<std::string,12> Date::months{ "Januar","Februar","Mart","April","Maj","Jun","Jul","Avgust",
        "Septembar","Oktobar","Novembar","Decembar" };

    std::ostream& operator<<(std::ostream& os, const Date& curr)
    {
        os << std::setw(2)<<std::setfill('0') << curr.day << "/";
        os << std::setw(2)<<std::setfill('0') << curr.month << "/";
        os << std::setw(4)<<curr.year << std::setfill(' ');
        return os;
    }

    bool Date::operator==(const Date& other) const
    {
        return this->day == other.day && this->month == other.month && this->year == other.year;
    }

    bool Date::operator!=(const Date& other) const
    {
        return !(*this == other);
    }
    bool Date::operator<(const Date& other) const
    {
        if (this->year < other.year)
            return true;
        else if (this->year == other.year && this->month < other.month)
            return true;
        else if (this->year == other.year && this->month == other.month && this->day < other.day)
            return true;
        else return false;
    }
    bool Date::operator>(const Date& other) const
    {
        return !(*this < other);
    }
    bool Date::operator<=(const Date& other) const
    {
        return *this < other || *this == other;
    }
    bool Date::operator>=(const Date& other) const
    {
        return *this > other || *this == other;
    }

    int Date::getDay()const
    {
        return this->day;
    }

    int Date::getMonth()const
    {
        return this->month;
    }

    int Date::getYear()const
    {
        return this->year;
    }

    void Date::setDay(int day) { this->day = day; }
    void Date::setMonth(int month) { this->month = month; }
    void Date::setYear(int year) { this->year = year; }

    Date Date::getCurrentDate()
    {
        std::time_t tim = std::time(0);
        std::tm* timeNow = std::localtime(&tim);
        return Date(timeNow->tm_mday, timeNow->tm_mon + 1, 1900 + timeNow->tm_year);
    }


    std::istream& operator>>(std::istream& is, Date& datum)
    {
        std::string dan, mjesec, godina;
        std::getline(is, dan, '/');
        std::getline(is, mjesec, '/');
        is >> godina;
        std::stringstream stream(dan + " " + mjesec+" "+godina);
        stream >> datum.day >> datum.month >> datum.year;

        return is;
    }

    std::string Date::toString()const
    {
        return std::to_string(this->day) + "/" + std::to_string(this->month) + "/" + std::to_string(this->year);
    }

    Date& Date::operator--()
    {

        switch (this->month)
        {
        case 1:
            if (this->day == 1)
            {
                this->day = 31;
                this->month = 12;
                this->year--;
            }
            else
                this->day--;
            break;
        case 3:
            if (this->day == 1)
            {
                if ((this->year % 4 == 0 && this->year % 100 != 0) || (this->year % 400 == 0))
                {
                    this->day = 29;
                    this->month--;
                }
                else
                {
                    this->day = 28;
                    this->month--;
                }
            }
            else
                this->day--;
            break;
        case 2:case 4:case 6:case 8:case 9:case 11:
            if (this->day == 1)
            {
                this->day = 31;
                this->month--;
            }
            else
                this->day--;
            break;
        case 5:case 7:case 10:case 12:
            if (this->day == 1)
            {
                this->day = 30;
                this->month--;
            }
            else
                this->day--;
            break;
        default:
            throw std::exception("Mjesec nije validan!!");
        }
        return *this;
    }
    Date& Date::operator-=(int pomjeraj)
    {
        for (int i = 0; i < pomjeraj; i++)
        {
            --* this;
        }
        return *this;
    }

    std::string Date::monthToString()const
    {
        return Date::months[this->month - 1];
    }
}