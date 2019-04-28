#include "node.h"

LogicalOperationNode::LogicalOperationNode(LogicalOperation o, shared_ptr<Node> lhs, shared_ptr<Node> rhs)
	: op(o)
	, left(move(lhs))
	, right(move(rhs))
{
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

EventComparisonNode::EventComparisonNode(Comparison c, string v)
	: ComparisonNode(c, move(v))
{
}
