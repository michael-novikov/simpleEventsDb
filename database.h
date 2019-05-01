#pragma once

#include <vector>
#include <string>
#include <map>
#include <iostream>

#include "date.h"

using namespace std;

using Predicate = function<bool(const Date& date, const string& event)>;

class Database {
public:
	void Add(const Date& date, const string& event);

	vector<pair<Date, string> > FindIf(const Predicate& p) const;
	string Last(const Date& date) const;

	int RemoveIf(const Predicate& p);

	void Print(ostream& os) const;

private:
	multimap<Date, string> events;
};
