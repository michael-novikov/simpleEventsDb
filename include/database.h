#ifndef DATABASE_H
#define DATABASE_H

#include <vector>
#include <string>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <iostream>
#include <functional>
#include "../include/date.h"
#include "../include/event.h"

using Predicate = std::function<bool(const Date& date, const std::string& event)>;

class Database {
public:
	void Add(const Date& date, const std::string& event);

	std::vector<Event> FindIf(const Predicate& p) const;
	Event Last(const Date& date) const;

	int RemoveIf(const Predicate& p);

	void Print(std::ostream& os) const;

private:
	std::multiset<Event, std::less<> > storage {};
	std::unordered_map<Date, std::unordered_set<std::string> > unordered_storage;
};

#endif // DATABASE_H
