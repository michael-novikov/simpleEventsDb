#include "database.h"
#include "date.h"

#include <sstream>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <stdexcept>

using namespace std;

void Database::Add(const Date& date, const string& event)
{
	events.emplace(date, event);
}

vector<pair<Date, string> > Database::FindIf(const Predicate& p) const
{
	vector<pair<Date, string> > res;

	for (const auto& item : events) {
		if (p(item.first, item.second)) {
			res.push_back(item);
		}
	}

	return res;
}

string Database::Last(const Date& date) const
{
	const auto range = events.equal_range(date);

	if (range.first == end(events)) {
		throw invalid_argument {"No entries for " + date.ToString()};
	}

	auto last = prev(range.second);
	return last->second;
}

int Database::RemoveIf(const Predicate& p)
{
	int count { 0 };

	for (auto it = begin(events); it != end(events); ) {
		if (p(it->first, it->second)) {
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
		os << item.first << " " << item.second << endl;
	}
}
