#pragma once
#include<iostream>
#include<array>

namespace learningPlatform
{
	class Date
	{
		int day;
		int month;
		int year;
		static const std::array<std::string, 12> months;
	public:
		Date();
		Date(int, int, int);

		int getDay()const;
		int getMonth()const;
		int getYear()const;

		void setDay(int);
		void setMonth(int);
		void setYear(int);
		std::string toString()const;

		static Date getCurrentDate();

		friend std::ostream& operator<<(std::ostream&, const Date&);
		friend std::istream& operator>>(std::istream&, Date&);
		bool operator==(const Date&) const;
		bool operator!=(const Date&) const;
		bool operator<(const Date&) const;
		bool operator>(const Date&) const;
		bool operator<=(const Date&) const;
		bool operator>=(const Date&) const;
		std::string monthToString()const;
		Date& operator--();
		Date& operator-=(int);
	};
}
