#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include <map>
#include <set>

using namespace std;

class Date {
public:
	Date(int year, int month, int day);

	int GetYear() const;
	int GetMonth() const;
	int GetDay() const;

	string ToString() const;

	static Date ParseDate(const string& s);
private:
	int year;
	int month;
	int day;
};

bool operator<(const Date& lhs, const Date& rhs);
bool operator==(const Date& lhs, const Date& rhs);
ostream& operator<<(ostream& out, const Date& d);

class Database {
public:
	void AddEvent(const Date& date, const string& event);
	bool DeleteEvent(const Date& date, const string& event);
	int  DeleteDate(const Date& date);

	set<string> Find(const Date& date) const;

	void Print() const;

private:
	map<Date, set<string>> events;
};

#endif // DATABASE_H
