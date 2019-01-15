#include "database.h"
#include <sstream>
#include <iomanip>

using namespace std;

Date::Date(int year, int month, int day) {
	if (month < 1 || month > 12) {
		throw domain_error("Month value is invalid");
	}

	if (day < 1 || day > 31) {
		throw domain_error("Day value is invalid");
	}


	this->year = year;
	this->month = month;
	this->day = day;
}

int Date::GetYear() const {
	return year;
}

int Date::GetMonth() const {
	return month;
}

int Date::GetDay() const {
	return day;
}

string Date::ToString() const {
	stringstream stream;

	stream 	<< setw(4) << setfill('0') << GetYear() << '-'
			<< setw(2) << setfill('0') << GetMonth() << '-'
			<< setw(2) << setfill('0') << GetDay();

	return stream.str();
}
