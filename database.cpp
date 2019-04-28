#include "database.h"
#include "date.h"

#include <sstream>
#include <iostream>
#include <iomanip>

using namespace std;

void Database::AddEvent(const Date& date, const string& event)
{
	events[date].insert(event);
}

bool Database::DeleteEvent(const Date& date, const string& event)
{
	if (events.count(date) == 0) {
		return false;
	}

	return events[date].erase(event) > 0;
}

int Database::DeleteDate(const Date& date)
{
	if (events.count(date) == 0) {
		return 0;
	}

	int size = events[date].size();
	events.erase(date);

	return size;
}

set<string> Database::Find(const Date& date) const
{
	if (events.count(date) > 0) {
		return events.at(date);
	}
	else {
		return {};
	}
}

void Database::Print() const {
	for (const auto& item : events) {
		for (const auto& event : item.second) {
			cout << item.first << " " << event << endl;
		}
	}
}
