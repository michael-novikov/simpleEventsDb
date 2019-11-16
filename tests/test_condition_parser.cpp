#include "boost/test/unit_test.hpp"

#include "include/condition_parser.h"

#include <sstream>

using namespace std;

BOOST_AUTO_TEST_SUITE(ConditionParserTest)

BOOST_AUTO_TEST_CASE(testParseCondition1_2) {
    istringstream is("date != 2017-11-18");
    shared_ptr<Node> root = ParseCondition(is);
    BOOST_REQUIRE(root->Evaluate({2017, 1, 1}, "")); // Parse condition 1
    BOOST_REQUIRE(!root->Evaluate({2017, 11, 18}, "")); // Parse condition 2
}

BOOST_AUTO_TEST_CASE(testParseCondition3_4) {
    istringstream is(R"(event == "sport event")");
    shared_ptr<Node> root = ParseCondition(is);
    BOOST_REQUIRE(root->Evaluate({2017, 1, 1}, "sport event")); // Parse condition 3
    BOOST_REQUIRE(!root->Evaluate({2017, 1, 1}, "holiday")); // Parse condition 4
}

BOOST_AUTO_TEST_CASE(testParseCondition5_9) {
    istringstream is("date >= 2017-01-01 AND date < 2017-07-01");
    shared_ptr<Node> root = ParseCondition(is);
    BOOST_REQUIRE(root->Evaluate({2017, 1, 1}, "")); // Parse condition 5
    BOOST_REQUIRE(root->Evaluate({2017, 3, 1}, "")); // Parse condition 6
    BOOST_REQUIRE(root->Evaluate({2017, 6, 30}, "")); // Parse condition 7
    BOOST_REQUIRE(!root->Evaluate({2017, 7, 1}, "")); // Parse condition 8
    BOOST_REQUIRE(!root->Evaluate({2016, 12, 31}, "")); // Parse condition 9
}

BOOST_AUTO_TEST_CASE(testParseCondition10_12) {
    istringstream is(R"(event != "sport event" AND event != "Wednesday")");
    shared_ptr<Node> root = ParseCondition(is);
    BOOST_REQUIRE(root->Evaluate({2017, 1, 1}, "holiday")); // Parse condition 10
    BOOST_REQUIRE(!root->Evaluate({2017, 1, 1}, "sport event")); // Parse condition 11
    BOOST_REQUIRE(!root->Evaluate({2017, 1, 1}, "Wednesday")); // Parse condition 12
}

BOOST_AUTO_TEST_CASE(testParseCondition13_15) {
    istringstream is(R"(event == "holiday AND date == 2017-11-18")");
    shared_ptr<Node> root = ParseCondition(is);
    BOOST_REQUIRE(!root->Evaluate({2017, 11, 18}, "holiday")); // Parse condition 13
    BOOST_REQUIRE(!root->Evaluate({2017, 11, 18}, "work day")); // Parse condition 14
    BOOST_REQUIRE(root->Evaluate({1, 1, 1}, "holiday AND date == 2017-11-18")); // Parse condition 15
}

BOOST_AUTO_TEST_CASE(testParseCondition16_17) {
    istringstream is(R"(((event == "holiday" AND date == 2017-01-01)))");
    shared_ptr<Node> root = ParseCondition(is);
    BOOST_REQUIRE(root->Evaluate({2017, 1, 1}, "holiday")); // Parse condition 16
    BOOST_REQUIRE(!root->Evaluate({2017, 1, 2}, "holiday")); // Parse condition 17
}

BOOST_AUTO_TEST_CASE(testParseCondition18_21) {
    istringstream is(R"(date > 2017-01-01 AND (event == "holiday" OR date < 2017-07-01))");
    shared_ptr<Node> root = ParseCondition(is);
    BOOST_REQUIRE(!root->Evaluate({2016, 1, 1}, "holiday")); // Parse condition 18
    BOOST_REQUIRE(root->Evaluate({2017, 1, 2}, "holiday")); // Parse condition 19
    BOOST_REQUIRE(root->Evaluate({2017, 1, 2}, "workday")); // Parse condition 20
    BOOST_REQUIRE(!root->Evaluate({2018, 1, 2}, "workday")); // Parse condition 21
}

BOOST_AUTO_TEST_CASE(testParseCondition22_25) {
    istringstream is(R"(date > 2017-01-01 AND event == "holiday" OR date < 2017-07-01)");
    shared_ptr<Node> root = ParseCondition(is);
    BOOST_REQUIRE(root->Evaluate({2016, 1, 1}, "event")); // Parse condition 22
    BOOST_REQUIRE(root->Evaluate({2017, 1, 2}, "holiday")); // Parse condition 23
    BOOST_REQUIRE(root->Evaluate({2017, 1, 2}, "workday")); // Parse condition 24
    BOOST_REQUIRE(!root->Evaluate({2018, 1, 2}, "workday")); // Parse condition 25
}

BOOST_AUTO_TEST_CASE(testParseCondition26_27) {
    istringstream is(R"(((date == 2017-01-01 AND event == "holiday")))");
    shared_ptr<Node> root = ParseCondition(is);
    BOOST_REQUIRE(root->Evaluate({2017, 1, 1}, "holiday")); // Parse condition 26
    BOOST_REQUIRE(!root->Evaluate({2017, 1, 2}, "holiday")); // Parse condition 27
}

BOOST_AUTO_TEST_CASE(testParseCondition28_30) {
    istringstream is(R"(((event == "2017-01-01" OR date > 2016-01-01)))");
    shared_ptr<Node> root = ParseCondition(is);
    BOOST_REQUIRE(root->Evaluate({1, 1, 1}, "2017-01-01")); // Parse condition 28
    BOOST_REQUIRE(!root->Evaluate({2016, 1, 1}, "event")); // Parse condition 29
    BOOST_REQUIRE(root->Evaluate({2016, 1, 2}, "event")); // Parse condition 30
}

BOOST_AUTO_TEST_SUITE_END()
