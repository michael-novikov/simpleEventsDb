#include "node.h"
#include <stdexcept>

bool EmptyNode::Evaluate(const Date& date, const string& event) const
{
	return true;
}

LogicalOperationNode::LogicalOperationNode(LogicalOperation o, shared_ptr<Node> lhs, shared_ptr<Node> rhs)
	: op(o)
	, left(move(lhs))
	, right(move(rhs))
{
}

bool LogicalOperationNode::Evaluate(const Date& date, const string& event) const
{
	switch (op) {
	case LogicalOperation::Or:
		return left->Evaluate(date, event) || right->Evaluate(date, event);
	case LogicalOperation::And:
		return left->Evaluate(date, event) && right->Evaluate(date, event);
	default:
		throw logic_error("Unsupported logical operation");
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

bool DateComparisonNode::Evaluate(const Date& date, const string& event) const
{
	switch (cmp) {
	case Comparison::Less:
		return date < value;
	case Comparison::LessOrEqual:
			return date <= value;
	case Comparison::Greater:
			return date > value;
	case Comparison::GreaterOrEqual:
			return date >= value;
	case Comparison::Equal:
			return date == value;
	case Comparison::NotEqual:
			return date != value;
	default:
		throw logic_error("Unsupported date comparison type");
	}
}

EventComparisonNode::EventComparisonNode(Comparison c, string v)
	: ComparisonNode(c, move(v))
{
}

bool EventComparisonNode::Evaluate(const Date& date, const string& event) const
{
	switch (cmp) {
	case Comparison::Less:
	        return event < value;
	    case Comparison::LessOrEqual:
	            return event <= value;
	    case Comparison::Greater:
	            return event > value;
	    case Comparison::GreaterOrEqual:
	            return event >= value;
	    case Comparison::Equal:
	            return event == value;
	    case Comparison::NotEqual:
	            return event != value;
	default:
		throw logic_error("Unsupported event comparison type");
	}
}
