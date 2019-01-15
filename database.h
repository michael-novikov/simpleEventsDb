#include <string>
#include <iostream>

using namespace std;

// Реализуйте функции и методы классов и при необходимости добавьте свои

class Date {
public:
  int GetYear() const;
  int GetMonth() const;
  int GetDay() const;
};

bool operator<(const Date& lhs, const Date& rhs);

class Database {
public:
  void AddEvent(const Date& date, const string& event);
  bool DeleteEvent(const Date& date, const string& event);
  int  DeleteDate(const Date& date);

  void/* ??? */ Find(const Date& date) const {
	  throw "not implemented";
  }

  void Print() const;
};
