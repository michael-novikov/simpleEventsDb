#include "node.h"
#include <stdexcept>

virtual bool EmptyNode::Evaluate(const Date& date, const string& event) const
{
	return true;
}

LogicalOperationNode::LogicalOperationNode(LogicalOperation o, shared_ptr<Node> lhs, shared_ptr<Node> rhs)
	: op(o)
	, left(move(lhs))
	, right(move(rhs))
{
}

virtual bool LogicalOperationNode::Evaluate(const Date& date, const string& event) const
{
	switch (op) {
	case LogicalOperation::Or:
		return left->Evaluate(date, event) || right->Evaluate(date, event);
	case LogicalOperation::And:
		return left->Evaluate(date, event) && right->Evaluate(date, event);
	default:
		throw logic_error("Unsupported logical operation: " + op);
	}
}

template<typename T>
ComparisonNode<T>::ComparisonNode(Comparison c, T v)
	: cmp(c)
	, value(move(v))
{
}

DateComparisonNode::DateComparisonNode(Comparison c, Date v)
	: ComparisonNode<Date>(c, move(v))
{
}

virtual bool DateComparisonNode::Evaluate(const Date& date, const string& event) const
{
	// TODO: implement comparison operator for Date
	switch(cmp) {
	case Comparison::Less:
		return value < date;
	case Comparison::LessOrEqual:
			return value <= date;
	case Comparison::Greater:
			return value > date;
	case Comparison::GreaterOrEqual:
			return value >= date;
	case Comparison::Equal:
			return value == date;
	case Comparison::NotEqual:
			return value != date;
	default:
		throw logic_error("Unsupported comparison type: " + cmp);
	}
}

EventComparisonNode::EventComparisonNode(Comparison c, string v)
	: ComparisonNode(c, move(v))
{
}

virtual bool EventComparisonNode::Evaluate(const Date& date, const string& event) const
{
	switch(cmp) {
		case Comparison::Equal:
				return value == event;
		case Comparison::NotEqual:
				return value != event;
		default:
			throw logic_error("Unsupported comparison type: " + cmp);
		}
}
