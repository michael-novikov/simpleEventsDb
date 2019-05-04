#include "database.h"

#include <sstream>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <stdexcept>

using namespace std;

void Database::Add(const Date& date, const string& event)
{
    if (!unordered_storage[date].count(event)) {
        storage.insert({ date, event });
        unordered_storage[date].insert(event);
    }
}

vector<Event> Database::FindIf(const Predicate& p) const
{
	vector<Event> res;

	for (const auto& item : storage) {
		if (p(item.date, item.event)) {
			res.push_back(item);
		}
	}

	return res;
}

Event Database::Last(const Date& date) const
{
    const auto it = storage.upper_bound(date);

    if (it == begin(storage)) {
        throw invalid_argument("No entries");
    }

    return *prev(it);
}

int Database::RemoveIf(const Predicate& p)
{
	int count { 0 };

	for (auto it = begin(storage); it != end(storage);) {
		if (p(it->date, it->event)) {
		    unordered_storage[it->date].erase(it->event);
		    it = storage.erase(it);
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
	for (const auto& item : storage) {
		os << item << endl;
	}
}
