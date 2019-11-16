#ifndef EVENT_H
#define EVENT_H

#include "date.h"
#include <string>
#include <iostream>

struct Event {
    Date date;
    std::string event;
};

bool operator<(const Event &lhs, const Event &rhs);
bool operator<(const Event& e, const Date& d);
bool operator<(const Date& d, const Event& e);

std::ostream& operator<<(std::ostream& os, const Event& e);

std::string ParseEvent(std::istream& is);

#endif // EVENT_H
