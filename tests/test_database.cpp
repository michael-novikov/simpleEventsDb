#include "boost/test/unit_test.hpp"

#include "include/date.h"
#include "include/event.h"
#include "include/database.h"
#include "include/node.h"

#include <sstream>
#include <memory>

using namespace std;

BOOST_AUTO_TEST_SUITE(DatabaseTest)

BOOST_AUTO_TEST_CASE(testCreateDate) {
    BOOST_CHECK_NO_THROW(Date(2000, 1, 1));
    BOOST_CHECK_NO_THROW(Date(-1, 12, 31));
    BOOST_CHECK_NO_THROW(Date(0, 1, 1));

    BOOST_CHECK_THROW(Date(1, 1, 0), domain_error);
    BOOST_CHECK_THROW(Date(1, 1, 32), domain_error);

    BOOST_CHECK_THROW(Date(1, 0, 1), domain_error);
    BOOST_CHECK_THROW(Date(1, 13, 1), domain_error);
}

BOOST_AUTO_TEST_CASE(testDateGetters) {
    const Date d(2000, 1, 1);

    BOOST_REQUIRE_EQUAL(d.GetYear(), 2000);
    BOOST_REQUIRE_EQUAL(d.GetMonth(), 1);
    BOOST_REQUIRE_EQUAL(d.GetDay(), 1);
}

BOOST_AUTO_TEST_CASE(testDateOperators) {
    const Date d1(2000, 1, 1);
    const Date d2(2000, 1, 1);
    BOOST_CHECK(d1 == d2);

    const Date d3(2001, 1, 1);
    BOOST_CHECK(!(d1 == d3));
    BOOST_CHECK(d1 < d3);

    const Date d4(2000, 2, 1);
    BOOST_CHECK(d1 < d4);

    const Date d5(2000, 1, 2);
    BOOST_CHECK(d1 < d5);

    const Date d6(2002, 1, 2);
    const Date d7(2001, 2, 1);
    BOOST_CHECK(!(d6 < d7));
}

BOOST_AUTO_TEST_CASE(testDateToString) {
    const Date d1(2019, 12, 31);
    BOOST_REQUIRE_EQUAL(d1.ToString(), "2019-12-31");

    const Date d2(1, 12, 31);
    BOOST_REQUIRE_EQUAL(d2.ToString(), "0001-12-31");

    const Date d3(12, 12, 31);
    BOOST_REQUIRE_EQUAL(d3.ToString(), "0012-12-31");

    const Date d4(2000, 12, 1);
    BOOST_REQUIRE_EQUAL(d4.ToString(), "2000-12-01");

    const Date d5(2000, 1, 12);
    BOOST_REQUIRE_EQUAL(d5.ToString(), "2000-01-12");

    const Date d6(1, 1, 1);
    BOOST_REQUIRE_EQUAL(d6.ToString(), "0001-01-01");
}

BOOST_AUTO_TEST_CASE(testParseDate) {
    BOOST_CHECK_NO_THROW(ParseDate("2000-01-01"));

    const Date d1 = ParseDate("2000-01-01");
    const Date d2(2000, 1, 1);
    BOOST_REQUIRE_EQUAL(d1, d2);

    BOOST_CHECK_THROW(ParseDate("2000---01-01"), invalid_argument);
    BOOST_CHECK_THROW(ParseDate("2000-01---01"), invalid_argument);

    BOOST_CHECK_THROW(ParseDate("2000.01.01"), invalid_argument);
    BOOST_CHECK_THROW(ParseDate("2000/01/01"), invalid_argument);

    BOOST_CHECK_THROW(ParseDate("a2000-01-01"), invalid_argument);
    BOOST_CHECK_THROW(ParseDate("2000-a01-01"), invalid_argument);
    BOOST_CHECK_THROW(ParseDate("2000-01-a01"), invalid_argument);

    BOOST_CHECK_THROW(ParseDate("2000-1-0"), domain_error);
    BOOST_CHECK_THROW(ParseDate("2000-0-1"), domain_error);

    Date d3;
    stringstream stream("2000-01-01");
    BOOST_CHECK_NO_THROW(stream >> d3);
    BOOST_REQUIRE_EQUAL(d3, Date(2000, 01, 01));

    Date d4;
    stringstream stream2("a2000-01-01");
    BOOST_CHECK_THROW(stream2 >> d4, invalid_argument);

    Date d5;
    stringstream stream3("2000-1-0");
    BOOST_CHECK_THROW(stream3 >> d5, domain_error);

    BOOST_REQUIRE_EQUAL(ParseDate("1-1-1"), Date(1, 1, 1));
    BOOST_REQUIRE_EQUAL(ParseDate("-1-1-1"), Date(-1, 1, 1));
    BOOST_CHECK_THROW(ParseDate("1--1-0"), domain_error);
    BOOST_CHECK_THROW(ParseDate("1-1--1"), domain_error);
    BOOST_CHECK_THROW(ParseDate("1---1-1"), invalid_argument);
    BOOST_CHECK_THROW(ParseDate("1-1---1"), invalid_argument);
}

 BOOST_AUTO_TEST_CASE(TestParseEventSimple) {
    istringstream is {"event"};
    BOOST_REQUIRE_EQUAL(ParseEvent(is), "event");
 }

 BOOST_AUTO_TEST_CASE(testParseEventWithLeadingSpaces){
    istringstream is {"   sport event "};
    BOOST_REQUIRE_EQUAL(ParseEvent(is), "sport event ");
}

BOOST_AUTO_TEST_CASE(testParseMultipleEvents) {
    istringstream is {"  first event  \n  second event"};

    vector<string> events;
    events.push_back(ParseEvent(is));
    events.push_back(ParseEvent(is));

    const vector<string> events_correct {"first event  ", "second event"};
    BOOST_REQUIRE_EQUAL_COLLECTIONS(begin(events), end(events), begin(events_correct), end(events_correct));
}

auto date_equal = [](const Date& date_eq) -> Predicate {
    auto date_cmp = make_shared<DateComparisonNode>(Comparison::Equal, date_eq);

    return [date_cmp](const Date& date, const string& event) -> bool {
        return date_cmp->Evaluate(date, event);
    };
};

auto date_event_equal = [](const Date& date_eq, const string& event_eq) -> Predicate {
    auto date_cmp = make_shared<DateComparisonNode>(Comparison::Equal, date_eq);
    auto event_cmp = make_shared<EventComparisonNode>(Comparison::Equal, event_eq);

    auto cmp = make_shared<LogicalOperationNode>(LogicalOperation::And, date_cmp, event_cmp);

    return [cmp](const Date& date, const string& event) -> bool {
        return cmp->Evaluate(date, event);
    };
};

BOOST_AUTO_TEST_CASE(testDatabaseAddAndFind) {
    const auto db = []() {
        Database d;
        d.Add({2000, 01, 02}, "event");
        return d;
    }();

    auto e1 = db.FindIf(date_equal({2000, 01, 02}));

    BOOST_REQUIRE_EQUAL(e1.size(), 1);
    BOOST_REQUIRE_EQUAL(e1.begin()->event, std::string{"event"});

    auto e2 = db.FindIf(date_equal({2000, 01, 03}));

    BOOST_REQUIRE_EQUAL(e2.size(), 0);
}

BOOST_AUTO_TEST_CASE(testDatabaseDeleteEvent) {
  Database db;
  db.Add(Date(2000, 01, 01), "event");

  BOOST_REQUIRE_EQUAL(db.RemoveIf(date_event_equal(Date(2000, 01, 01), "strange")), 0);
  BOOST_REQUIRE_EQUAL(db.RemoveIf(date_event_equal(Date(2000, 01, 31), "event")), 0);

  BOOST_REQUIRE_EQUAL(db.RemoveIf(date_event_equal(Date(2000, 01, 01), "event")), 1);
}

BOOST_AUTO_TEST_CASE(testDatabaseDeleteAllEvents) {
  Database db;

  Date d(2000, 01, 01);
  db.Add(d, "event1");
  db.Add(d, "event2");
  db.Add(d, "event3");

  int removed1 = db.RemoveIf(date_equal(d));
  BOOST_REQUIRE_EQUAL(removed1, 3);

  int removed2 = db.RemoveIf(date_equal(d));
  BOOST_REQUIRE_EQUAL(removed2, 0);

  int removed3 = db.RemoveIf(date_equal({2000, 01, 31}));
  BOOST_REQUIRE_EQUAL(removed3, 0);
}

BOOST_AUTO_TEST_SUITE_END()
