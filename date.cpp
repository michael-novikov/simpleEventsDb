#include "date.h"

#include <iostream>
#include <sstream>
#include <iomanip>

using namespace std;

Date::Date(int year, int month, int day)
{
	if (month < 1 || month > 12) {
		throw domain_error("Month value is invalid: " + to_string(month));
	}

	if (day < 1 || day > 31) {
		throw domain_error("Day value is invalid: " + to_string(day));
	}

	this->year = year;
	this->month = month;
	this->day = day;
}

int Date::GetYear() const
{
	return year;
}

int Date::GetMonth() const
{
	return month;
}

int Date::GetDay() const
{
	return day;
}

string Date::ToString() const
{
	stringstream stream;

	stream << setw(4) << setfill('0') << GetYear() << '-'
			<< setw(2) << setfill('0') << GetMonth() << '-'
			<< setw(2) << setfill('0') << GetDay();

	return stream.str();
}

bool operator==(const Date& lhs, const Date& rhs)
 {
	return (lhs.GetYear() == rhs.GetYear())
			&& (lhs.GetMonth() == rhs.GetMonth())
			&& (lhs.GetDay() == rhs.GetDay());
}

bool operator!=(const Date& lhs, const Date& rhs)
{
	return !(lhs == rhs);
}

bool operator<(const Date& lhs, const Date& rhs)
{
	if (lhs.GetYear() < rhs.GetYear()) {
		return true;
	}
	else if ((lhs.GetYear() == rhs.GetYear())
			&& (lhs.GetMonth() < rhs.GetMonth())) {
		return true;
	}
	else if ((lhs.GetYear() == rhs.GetYear())
			&& (lhs.GetMonth() == rhs.GetMonth())
			&& (lhs.GetDay() < rhs.GetDay())) {
		return true;
	}

	return false;
}

bool operator<=(const Date& lhs, const Date& rhs)
{
	return lhs < rhs || lhs == rhs;
}

bool operator>(const Date& lhs, const Date& rhs)
{
	return rhs < lhs;
}

bool operator>=(const Date& lhs, const Date& rhs)
{
	return rhs < lhs || rhs == lhs;
}

ostream& operator<<(ostream& out, const Date& d)
{
	return out << d.ToString();
}

istream& operator>>(istream& in, Date& d)
{
	d = ParseDate(in);
	return in;
}

Date ParseDate(istream& stream)
{
	int year, month, day;

	auto parsing_assert = [](bool stmt) {
	    if (!stmt) {
	        throw invalid_argument("Wrong date format");
	    }
	};

	parsing_assert(static_cast<bool>(stream >> year));

	parsing_assert(stream.peek() == '-');
	stream.ignore(1);

	parsing_assert(static_cast<bool>(stream >> month));

	parsing_assert(stream.peek() == '-');
	stream.ignore(1);

	parsing_assert(static_cast<bool>(stream >> day));

	return Date(year, month, day);
}

Date ParseDate(const string& s)
{
	istringstream is { s };
	return ParseDate(is);
}

namespace std
{
    size_t hash<Date>::operator()(const Date & d) const noexcept
        {
            size_t const h1 ( hash<int>{}(d.GetYear()) );
            size_t const h2 ( hash<int>{}(d.GetMonth()) );
            size_t const h3 ( hash<int>{}(d.GetDay()) );
            return h1 ^ (h2 << 1) ^ (h3 << 2);
        }
}
