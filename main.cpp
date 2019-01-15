#include <iostream>
#include <sstream>
#include <string>

#include "database.h"

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
		}
	}

	return 0;
}
