#include"date.h"

Date ParseDate(istream& is)
{
	bool ok = true;

	int year = 0;
	ok = ok && (is >> year);
	ok = ok && (is.peek() == '-');
	is.ignore(1);

	int month = 0;
	ok = ok && (is >> month);
	ok = ok && (is.peek() == '-');
	is.ignore(1);

	int day = 0;
	ok = ok && (is >> day);
	ok = ok && (is.eof());

	return Date(year, month, day);
}

int Date::GetYear() const
{
	return year;
}

int Date::GetMonth() const
{
	return month;
}

int Date::GetDay() const
{ 
	return day;
}

string Date::GetFullDate() const
{
	return to_string(GetYear()) + '-' + to_string(GetMonth()) + '-' + to_string(GetDay());
}

bool operator<(const Date& lhs, const Date& rhs)
{
	return vector<int>{lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()} < vector<int>{rhs.GetYear(), rhs.GetMonth(), rhs.GetDay()};
}

bool operator>(const Date& lhs, const Date& rhs)
{
	return vector<int>{lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()} > vector<int>{rhs.GetYear(), rhs.GetMonth(), rhs.GetDay()};
}

bool operator==(const Date& lhs, const Date& rhs)
{
	return vector<int>{lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()} == vector<int>{rhs.GetYear(), rhs.GetMonth(), rhs.GetDay()};
}

bool operator!=(const Date& lhs, const Date& rhs)
{
	return vector<int>{lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()} != vector<int>{rhs.GetYear(), rhs.GetMonth(), rhs.GetDay()};
}

bool operator<=(const Date& lhs, const Date& rhs)
{
	return vector<int>{lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()} <= vector<int>{rhs.GetYear(), rhs.GetMonth(), rhs.GetDay()};
}

bool operator>=(const Date& lhs, const Date& rhs)
{
	return vector<int>{lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()} >= vector<int>{rhs.GetYear(), rhs.GetMonth(), rhs.GetDay()};
}

ostream& operator<<(ostream& os, const Date& date)
{
	return os << setw(4) << setfill('0') << date.GetYear() << '-' 
		<< setw(2) << setfill('0') << date.GetMonth() << '-'
		<< setw(2) << setfill('0') << date.GetDay();
}

ostream& operator<<(ostream& os, const deque<string>& events)
{
	bool first = true;
	for (const auto& item : events)
	{
		if (!first)
		{
			os << ' ';
		}
		first = false;
		os << item;
	}
	return os;
}

ostream& operator<<(ostream& os, const set<string>& events)
{
	bool first = true;
	for (const auto& item : events)
	{
		if (!first)
		{
			os << ' ';
		}
		first = false;
		os << item;
	}
	return os;
}
