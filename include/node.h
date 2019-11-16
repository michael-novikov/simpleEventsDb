#ifndef NODE_H
#define NODE_H

#include <memory>
#include "../include/date.h"

class Node {
public:
	virtual bool Evaluate(const Date& date, const std::string& event) const = 0;
	virtual ~Node() = default;
};

class EmptyNode: public Node {
public:
	virtual bool Evaluate(const Date& date, const std::string& event) const override;
};

enum class LogicalOperation { Or, And };

class LogicalOperationNode: public Node {
public:
	LogicalOperationNode(LogicalOperation op, std::shared_ptr<Node> lhs, std::shared_ptr<Node> rhs);
	virtual bool Evaluate(const Date& date, const std::string& event) const override;
private:
	LogicalOperation op;
	std::shared_ptr<Node> left;
	std::shared_ptr<Node> right;
};

enum class Comparison { Less, LessOrEqual, Greater, GreaterOrEqual, Equal, NotEqual };

template<typename T>
class ComparisonNode: public Node {
public:
	ComparisonNode(Comparison c, T v);
protected:
	Comparison cmp;
	T value;
};

class DateComparisonNode: public ComparisonNode<Date> {
public:
	DateComparisonNode(Comparison c, Date v);
	virtual bool Evaluate(const Date& date, const std::string& event) const override;
};

class EventComparisonNode: public ComparisonNode<std::string> {
public:
	EventComparisonNode(Comparison c, std::string v);
	virtual bool Evaluate(const Date& date, const std::string& event) const override;
};

#endif // NODE_H
