#define BOOST_TEST_MODULE database
#include "boost/test/included/unit_test.hpp"

#include "database.h"

BOOST_AUTO_TEST_SUITE(DB)

BOOST_AUTO_TEST_CASE(CreateDate) {
	BOOST_CHECK_NO_THROW(Date(2000, 1, 1));
	BOOST_CHECK_NO_THROW(Date(-1, 12, 31));
	BOOST_CHECK_NO_THROW(Date(0, 1, 1));

	BOOST_CHECK_THROW(Date(1, 1, 0), domain_error);
	BOOST_CHECK_THROW(Date(1, 1, 32), domain_error);

	BOOST_CHECK_THROW(Date(1, 0, 1), domain_error);
	BOOST_CHECK_THROW(Date(1, 13, 1), domain_error);
}

BOOST_AUTO_TEST_CASE(DateGetters) {
	const Date d(2000, 1, 1);

	BOOST_REQUIRE_EQUAL(d.GetYear(), 2000);
	BOOST_REQUIRE_EQUAL(d.GetMonth(), 1);
	BOOST_REQUIRE_EQUAL(d.GetDay(), 1);
}

BOOST_AUTO_TEST_CASE(DateOperators) {
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

BOOST_AUTO_TEST_CASE(DateToString) {
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

BOOST_AUTO_TEST_CASE(ParseDate) {
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
}

BOOST_AUTO_TEST_CASE(DatabaseAddAndFind) {
	Database db;
	db.AddEvent(Date(2000, 01, 01), "event");

	auto e1 = db.Find(Date(2000, 01, 01));
	BOOST_REQUIRE_EQUAL(e1.size(), 1);
	BOOST_REQUIRE_EQUAL(*e1.begin(), "event");

	auto e2 = db.Find(Date(2000, 01, 02));
	BOOST_REQUIRE_EQUAL(e2.size(), 0);
}

BOOST_AUTO_TEST_SUITE_END()
