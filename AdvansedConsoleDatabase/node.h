#pragma once
#include"date.h"
#include<memory>
enum class Comparison
{
    Less,
    LessOrEqual,
    Greater,
    GreaterOrEqual,
    Equal,
    NotEqual
};

enum class LogicalOperation
{
    Or,
    And
};


template <typename T>
bool Compare(const Comparison& cmp, const T& lhs, const T& rhs);


class Node
{
public:
    virtual bool Evaluate(const Date& date, const string& event) const = 0;
};

class EmptyNode : public Node
{
public:
    bool Evaluate(const Date& date, const string& event) const override;
};

class LogicalOperationNode : public Node
{
public:
	LogicalOperationNode(LogicalOperation l_op_, shared_ptr<Node> left_, shared_ptr<Node> right_) : l_op(l_op_), left(left_), right(right_) {}
    bool Evaluate(const Date& date, const string& event) const override;
private:
	LogicalOperation l_op;
	shared_ptr<Node> left, right;
};

class EventComparisonNode : public Node
{
public:
    EventComparisonNode(const Comparison& cmp, const string& event) : cmp_(cmp), event_(event) {}
    bool Evaluate(const Date& date, const string& event) const override;
private:
    const Comparison cmp_;
    const string event_;
};

class DateComparisonNode : public Node
{
public:
    DateComparisonNode(const Comparison& cmp, const Date& date) : cmp_(cmp), date_(date) {}
    bool Evaluate(const Date& date, const string& event) const override;
private:
    const Comparison cmp_;
    const Date date_;
};
