#pragma once

#include <string>
#include <map>
#include <set>
#include <iostream>

#include "date.h"

using namespace std;

using Predicate = function<bool(const Date& date, const string& event)>;

class Database {
public:
	void Add(const Date& date, const string& event);
	void Print(ostream& os) const;
	int RemoveIf(const Predicate& p);
	vector<pair<Date, set<string> > > FindIf(const Predicate& p) const;
	string Last(const Date& date) const;

	void AddEvent(const Date& date, const string& event);
	bool DeleteEvent(const Date& date, const string& event);
	int  DeleteDate(const Date& date);

	set<string> Find(const Date& date) const;

	void Print() const;

private:
	map<Date, set<string>> events;
};
