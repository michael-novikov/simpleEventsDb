#include "include/event.h"

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

std::ostream& operator<<(std::ostream& os, const Event& e)
{
    return os << e.date << " " << e.event;
}

std::string ParseEvent(std::istream& is) {
    std::string event;
    std::getline(is >> std::ws, event);
    return event;
}
