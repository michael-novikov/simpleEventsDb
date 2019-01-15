#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <map>
#include <set>

using namespace std;

class Date {
public:
	Date(int year = 0, int month = 1, int day = 1);

	int GetYear() const;
	int GetMonth() const;
	int GetDay() const;

	string ToString() const;

	static Date ParseDate(const string& s);
private:
	int year;
	int month;
	int day;
};

bool operator<(const Date& lhs, const Date& rhs);
bool operator==(const Date& lhs, const Date& rhs);
ostream& operator<<(ostream& out, const Date& d);
istream& operator>>(istream& out, Date& d);

class Database {
public:
	void AddEvent(const Date& date, const string& event);
	bool DeleteEvent(const Date& date, const string& event);
	int  DeleteDate(const Date& date);

	set<string> Find(const Date& date) const;

	void Print() const;

private:
	map<Date, set<string>> events;
};

Date::Date(int year, int month, int day) {
	if (month < 1 || month > 12) {
		throw domain_error("Month value is invalid: " + to_string(month));
	}

	if (day < 1 || day > 31) {
		throw domain_error("Day value is invalid: " + to_string(day));
	}


	this->year = year;
	this->month = month;
	this->day = day;
}

int Date::GetYear() const {
	return year;
}

int Date::GetMonth() const {
	return month;
}

int Date::GetDay() const {
	return day;
}

string Date::ToString() const {
	stringstream stream;

	stream 	<< setw(4) << setfill('0') << GetYear() << '-'
			<< setw(2) << setfill('0') << GetMonth() << '-'
			<< setw(2) << setfill('0') << GetDay();

	return stream.str();
}

Date Date::ParseDate(const string& s) {
	string error = "Wrong date format: " + s;
	stringstream stream(s);
	int year, month, day;

	if (!(stream >> year)) {
		throw invalid_argument(error);;
	}

	if (stream.peek() != '-') {
		throw invalid_argument(error);
	}

	stream.ignore(1);
	stream >> month;

	if (stream.peek() != '-') {
		throw invalid_argument(error);
	}

	stream.ignore(1);
	stream >> day;

	if (stream.rdbuf()->in_avail()) {
		throw invalid_argument(error);
	}

	return Date(year, month, day);
}

bool operator<(const Date& lhs, const Date& rhs) {
	if (lhs.GetYear() < rhs.GetYear()) {
		return true;
	}
	else if ((lhs.GetYear() == rhs.GetYear())
			&& (lhs.GetMonth() < rhs.GetMonth())) {
		return true;
	}
	else if ((lhs.GetYear() == rhs.GetYear())
			&& (lhs.GetMonth() == rhs.GetMonth())
			&& (lhs.GetDay() < rhs.GetDay())) {
		return true;
	}

	return false;
}

bool operator==(const Date& lhs, const Date& rhs) {
	return (lhs.GetYear() == rhs.GetYear())
			&& (lhs.GetMonth() == rhs.GetMonth())
			&& (lhs.GetDay() == rhs.GetDay());
}

ostream& operator<<(ostream& out, const Date& d) {
	return out << d.ToString();
}

istream& operator>>(istream& in, Date& d) {
	string s;
	in >> s;

	Date new_date = Date::ParseDate(s);
	d = new_date;

	return in;
}

void Database::AddEvent(const Date& date, const string& event) {
	events[date].insert(event);
}

bool Database::DeleteEvent(const Date& date, const string& event) {
	if (events.count(date) == 0) {
		return false;
	}

	return events[date].erase(event) > 0;
}

int Database::DeleteDate(const Date& date) {
	if (events.count(date) == 0) {
		return 0;
	}

	int size = events[date].size();
	events.erase(date);

	return size;
}

set<string> Database::Find(const Date& date) const {
	if (events.count(date) > 0) {
		return events.at(date);
	} else {
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

int main() {
	Database db;

	string command;
	while (getline(cin, command)) {
		if (command == "") {
			continue;
		}

		stringstream stream(command);
		string op_code;

		stream >> op_code;
		if ((op_code == "Add") || (op_code == "Del") || (op_code == "Find")) {
			string dateStr;
			stream >> dateStr;
			Date date;

			try {
				date = Date::ParseDate(dateStr);
			} catch (invalid_argument& e) {
				cout << e.what() << endl;
				return -1;
			} catch (domain_error& e) {
				cout << e.what() << endl;
				return -1;
			}

			if (op_code == "Add") {
				string event;
				stream >> event;

				db.AddEvent(date, event);
			} else if (op_code == "Del") {
				string event;
				if (stream >> event) {
					if (db.DeleteEvent(date, event)) {
						cout << "Deleted successfully" << endl;
					} else {
						cout << "Event not found" << endl;
					}
				} else {
					int n = db.DeleteDate(date);
					cout << "Deleted " << n << " events" << endl;
				}
			} else /* if (op_code == "Find") */ {
				const auto events = db.Find(date);
				for (const auto& event : events) {
					cout << event << endl;
				}
			}
		} else if (op_code == "Print") {
			db.Print();
		} else {
			cout << "Unknown command: " << op_code << endl;
			return -1;
		}
	}

	return 0;
}
