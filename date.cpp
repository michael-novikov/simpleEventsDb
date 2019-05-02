#include "date.h"

#include <iostream>
#include <sstream>
#include <iomanip>

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
	string error = "Wrong date format.";
	int year, month, day;

	if (!(stream >> year)) {
		throw invalid_argument(error);
	}

	if (stream.peek() != '-') {
		throw invalid_argument(error);
	}

	stream.ignore(1);
	stream >> month;

	if (stream.peek() != '-') {
		throw invalid_argument(error);
	}

	stream.ignore(1);
	stream >> day;

	return Date(year, month, day);
}

Date ParseDate(const string& s)
{
	istringstream is { s };
	return ParseDate(is);
}
