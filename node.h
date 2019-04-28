#pragma once

#include "date.h"

class Node {
public:
	virtual bool Evaluate(const Date& date, const string& event) const = 0;
};

class EmptyNode: public Node {

};

enum LogicalOperation { Or, And };

class LogicalOperationNode: public Node {

};

enum Comparison { Less, LessOrEqual, Greater, GreaterOrEqual, Equal, NotEqual };

template<typename T>
class ComparisonNode: Node {
public:

private:
	Comparison cmp;
	T value;
};

class DateComparisonNode: public ComparisonNode<Date> {
};

class EventComparisonNode: public ComparisonNode<string> {
};
