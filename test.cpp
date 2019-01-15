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
	Date d(2000, 1, 1);

	BOOST_REQUIRE_EQUAL(d.GetYear(), 2000);
	BOOST_REQUIRE_EQUAL(d.GetMonth(), 1);
	BOOST_REQUIRE_EQUAL(d.GetDay(), 1);
}

BOOST_AUTO_TEST_CASE(DateToString) {
	Date d1(2019, 12, 31);
	BOOST_REQUIRE_EQUAL(d1.ToString(), "2019-12-31");

	Date d2(1, 12, 31);
	BOOST_REQUIRE_EQUAL(d2.ToString(), "0001-12-31");

	Date d3(12, 12, 31);
	BOOST_REQUIRE_EQUAL(d3.ToString(), "0012-12-31");

	Date d4(2000, 12, 1);
	BOOST_REQUIRE_EQUAL(d4.ToString(), "2000-12-01");

	Date d5(2000, 1, 12);
	BOOST_REQUIRE_EQUAL(d5.ToString(), "2000-01-12");

	Date d6(1, 1, 1);
	BOOST_REQUIRE_EQUAL(d6.ToString(), "0001-01-01");

}

BOOST_AUTO_TEST_SUITE_END()
