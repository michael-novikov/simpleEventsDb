#define BOOST_TEST_MODULE DatabaseTestModule
#include "boost/test/included/unit_test.hpp"

#include <sstream>

#include "database.h"

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
	BOOST_CHECK_NO_THROW(Date::ParseDate("2000-01-01"));

	const Date d1 = Date::ParseDate("2000-01-01");
	const Date d2(2000, 1, 1);
	BOOST_REQUIRE_EQUAL(d1, d2);

	BOOST_CHECK_THROW(Date::ParseDate("2000---01-01"), invalid_argument);
	BOOST_CHECK_THROW(Date::ParseDate("2000-01---01"), invalid_argument);

	BOOST_CHECK_THROW(Date::ParseDate("2000.01.01"), invalid_argument);
	BOOST_CHECK_THROW(Date::ParseDate("2000/01/01"), invalid_argument);

	BOOST_CHECK_THROW(Date::ParseDate("a2000-01-01"), invalid_argument);
	BOOST_CHECK_THROW(Date::ParseDate("2000-01-01a"), invalid_argument);

	BOOST_CHECK_THROW(Date::ParseDate("2000-1-0"), domain_error);
	BOOST_CHECK_THROW(Date::ParseDate("2000-0-1"), domain_error);

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

	BOOST_REQUIRE_EQUAL(Date::ParseDate("1-1-1"), Date(1, 1, 1));
	BOOST_REQUIRE_EQUAL(Date::ParseDate("-1-1-1"), Date(-1, 1, 1));
	BOOST_CHECK_THROW(Date::ParseDate("1--1-0"), domain_error);
	BOOST_CHECK_THROW(Date::ParseDate("1-1--1"), domain_error);
	BOOST_CHECK_THROW(Date::ParseDate("1---1-1"), invalid_argument);
	BOOST_CHECK_THROW(Date::ParseDate("1-1---1"), invalid_argument);
}

BOOST_AUTO_TEST_CASE(testDatabaseAddAndFind) {
	Database db;
	db.AddEvent(Date(2000, 01, 01), "event");

	auto e1 = db.Find(Date(2000, 01, 01));
	BOOST_REQUIRE_EQUAL(e1.size(), 1);
	BOOST_REQUIRE_EQUAL(*e1.begin(), "event");

	auto e2 = db.Find(Date(2000, 01, 02));
	BOOST_REQUIRE_EQUAL(e2.size(), 0);
}

BOOST_AUTO_TEST_CASE(testDatabaseDeleteEvent) {
	Database db;
	db.AddEvent(Date(2000, 01, 01), "event");

	BOOST_REQUIRE_EQUAL(db.DeleteEvent(Date(2000, 01, 01), "strange"), false);
	BOOST_REQUIRE_EQUAL(db.DeleteEvent(Date(2000, 01, 31), "event"), false);

	BOOST_REQUIRE_EQUAL(db.DeleteEvent(Date(2000, 01, 01), "event"), true);
}

BOOST_AUTO_TEST_CASE(testDatabaseDeleteAllEvents) {
	Database db;
	Date d(2000, 01, 01);

	db.AddEvent(d, "event1");
	db.AddEvent(d, "event2");
	db.AddEvent(d, "event3");

	int removed1 = db.DeleteDate(d);
	BOOST_REQUIRE_EQUAL(removed1, 3);

	int removed2 = db.DeleteDate(Date(2000, 01, 31));
	BOOST_REQUIRE_EQUAL(removed2, 0);
}

BOOST_AUTO_TEST_SUITE_END()
