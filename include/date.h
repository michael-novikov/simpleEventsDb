#ifndef DATE_H
#define DATE_H

#include <string>
#include <iostream>

class Date {
public:
	Date(int year = 0, int month = 1, int day = 1);

	int GetYear() const;
	int GetMonth() const;
	int GetDay() const;

	std::string ToString() const;
private:
	int year;
	int month;
	int day;
};

bool operator==(const Date& lhs, const Date& rhs);
bool operator!=(const Date& lhs, const Date& rhs);
bool operator<(const Date& lhs, const Date& rhs);
bool operator<=(const Date& lhs, const Date& rhs);
bool operator>(const Date& lhs, const Date& rhs);
bool operator>=(const Date& lhs, const Date& rhs);

std::ostream& operator<<(std::ostream& out, const Date& d);
std::istream& operator>>(std::istream& out, Date& d);

Date ParseDate(std::istream& stream);
Date ParseDate(const std::string& s);

namespace std
{
    template<> struct hash<Date>
    {
        std::size_t operator()(Date const& s) const noexcept;
    };
}

#endif // DATE_H
