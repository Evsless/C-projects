#pragma once
#include<sstream>
#include<deque>
#include<iomanip>
#include<string>
#include<set>
#include<vector>
#include <functional>

using namespace std;

class Date
{
public:
	Date(int year_, int month_, int day_) : year(year_), month(month_), day(day_) {}
	int GetYear() const;
	int GetMonth() const;
	int GetDay() const;
	string GetFullDate() const;
private:
	const int year = 0;
	const int month = 0;
	const int day = 0;
};

bool operator<(const Date& lhs, const Date& rhs);
bool operator>(const Date& lhs, const Date& rhs);
bool operator>=(const Date& lhs, const Date& rhs);
bool operator<=(const Date& lhs, const Date& rhs);
bool operator==(const Date& lhs, const Date& rhs);
bool operator!=(const Date& lhs, const Date& rhs);

ostream& operator<<(ostream& os, const Date& date);
ostream& operator<<(ostream& os, const deque<int>& events);

Date ParseDate(istream& is);
