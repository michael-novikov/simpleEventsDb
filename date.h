#pragma once

#include <string>
#include <iostream>

using namespace std;

class Date {
public:
	Date(int year = 0, int month = 1, int day = 1);

	int GetYear() const;
	int GetMonth() const;
	int GetDay() const;

	string ToString() const;
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

ostream& operator<<(ostream& out, const Date& d);
istream& operator>>(istream& out, Date& d);

Date ParseDate(istream& stream);
Date ParseDate(const string& s);
