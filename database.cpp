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

bool operator<(const Event& e, const Date& d)
{
    return e.date < d;
}

bool operator<(const Date& d, const Event& e)
{
    return d < e.date;
}

ostream& operator<<(ostream& os, const Event& e)
{
	return os << e.date << " " << e.event;
}

void Database::Add(const Date& date, const string& event)
{
    const auto range = events.equal_range(date);

    if (range.first == end(events)) {
        events.insert({ date, event });
    }
    else {
        const auto it = find_if(range.first, range.second,
                [&](const Event& item) { return event == item.event; });
        if (it == range.second) {
            events.insert({ date, event });
        }
    }
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

Event Database::Last(const Date& date) const
{
    const auto it = events.upper_bound(date);

    if (it == begin(events)) {
        throw invalid_argument("No entries");
    }

    return *prev(it);
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
