#include "node.h"
using namespace std;

template <typename T>
bool Compare(const Comparison &cmp, const T &lhs, const T &rhs)
{
	if (cmp == Comparison::Equal)
	{
		return (lhs == rhs);
	}
	else if (cmp == Comparison::Greater)
	{
		return (lhs > rhs);
	}
	else if (cmp == Comparison::GreaterOrEqual)
	{
		return (lhs >= rhs);
	}
	else if (cmp == Comparison::Less)
	{
		return (lhs < rhs);
	}
	else if (cmp == Comparison::LessOrEqual)
	{
		return (lhs <= rhs);
	}
	else if (cmp == Comparison::NotEqual)
	{
		return lhs != rhs;
	}
	else
	{
		return 0;
	}
}

bool EmptyNode::Evaluate(const Date &date, const string &event) const
{
	return true;
}

bool LogicalOperationNode::Evaluate(const Date &date, const string &event) const
{
	if (l_op == LogicalOperation::And)
	{
		return (left->Evaluate(date, event) && right->Evaluate(date, event));
	}
	else if (l_op == LogicalOperation::Or)
	{
		return (left->Evaluate(date, event) || right->Evaluate(date, event));
	}
	return 0;
}

bool EventComparisonNode::Evaluate(const Date &date, const string &event) const
{
	return Compare(cmp_, event, event_);
}

bool DateComparisonNode::Evaluate(const Date &date, const string &event) const
{
	return Compare(cmp_, date, date_);
}
