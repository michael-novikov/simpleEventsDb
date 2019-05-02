#pragma once

#include <vector>
#include <string>
#include <set>
#include <iostream>
#include <functional>

#include "date.h"

using namespace std;

using Predicate = function<bool(const Date& date, const string& event)>;

struct Event {
	Date date;
	string event;
};

bool operator<(const Event &lhs, const Event &rhs);
ostream& operator<<(ostream& os, const Event& e);

class Database {
public:
	void Add(const Date& date, const string& event);

	vector<Event> FindIf(const Predicate& p) const;
	string Last(const Date& date) const;

	int RemoveIf(const Predicate& p);

	void Print(ostream& os) const;

private:
	multiset<Event> events {};
};
