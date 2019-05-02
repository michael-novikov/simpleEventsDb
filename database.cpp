#include "database.h"
#include "date.h"

#include <sstream>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <stdexcept>

using namespace std;

bool operator<(const Event &lhs, const Event &rhs)
{
	return lhs.date < rhs.date;
}

ostream& operator<<(ostream& os, const Event& e)
{
	return os << e.date << " " << e.event;
}

void Database::Add(const Date& date, const string& event)
{
	events.insert( { date, event });
}

vector<Event> Database::FindIf(const Predicate& p) const
{
	vector<Event> res;

	for (const auto& item : events) {
		if (p(item.date, item.event)) {
			res.push_back(item);
		}
	}

	return res;
}

string Database::Last(const Date& date) const
{
	const auto last = find_if(rbegin(events), rend(events),
			[&date](const Event& e) {return date == e.date;});
	return last->event;
}

int Database::RemoveIf(const Predicate& p)
{
	int count { 0 };

	for (auto it = begin(events); it != end(events);) {
		if (p(it->date, it->event)) {
			it = events.erase(it);
			++count;
		}
		else {
			++it;
		}
	}

	return count;
}

void Database::Print(ostream& os) const
{
	for (const auto& item : events) {
		os << item << endl;
	}
}
