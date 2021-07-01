#include<iostream>
#include<cmath> 
#include<sstream>
#include<set>
#include<vector>
#include<map>
#include<fstream>
#include<iomanip>
#include<exception>
using namespace std;

int Gcd(int a, int b) 
{
	if (b == 0) {
		return a;
	}
	else {
		return Gcd(b, a % b);
	}
}

int Lcm(int a, int b)
{
	return a * b / Gcd(a, b);
}

class Rational
{
public:
	Rational()
	{
		num = 0;
		denom = 1;
	}
	Rational(int numerator, int denominator)
	{
		if (denominator == 0)
		{
			throw invalid_argument("Invalid argument");
		}
		const int reducer = Gcd(abs(numerator), abs(denominator));
		num = numerator / reducer;
		denom = denominator / reducer;
		if (denom < 0)
		{
			denom = -denom;
			num = -num;
		}
	}

	int Numerator() const
	{
		return num;
	}
	int Denominator() const
	{
		return denom;
	}
private:
	int num;
	int denom;
};

Rational operator+(const Rational& lhs, const Rational& rhs)
{
	int lcm = Lcm(lhs.Denominator(), rhs.Denominator());
	return Rational(lcm*lhs.Numerator() / lhs.Denominator() + lcm * rhs.Numerator() / rhs.Denominator(), lcm);
}

Rational operator-(const Rational& lhs, const Rational& rhs)
{
	int lcm = Lcm(lhs.Denominator(), rhs.Denominator());
	return Rational(lcm*lhs.Numerator() / lhs.Denominator() - lcm * rhs.Numerator() / rhs.Denominator(), lcm);
}

Rational operator*(const Rational& lhs, const Rational& rhs)
{
	return Rational(lhs.Numerator()*rhs.Numerator(), lhs.Denominator()*rhs.Denominator());
}

Rational operator/(const Rational& lhs, const Rational& rhs)
{
	if (rhs.Numerator() == 0)
	{
		throw domain_error("Division by zero");
	}
	return Rational(lhs.Numerator()*rhs.Denominator(), lhs.Denominator()*rhs.Numerator());
}

ostream& operator<<(ostream &stream, const Rational &rational)
{
	stream << rational.Numerator() << "/" << rational.Denominator();
	return stream;
}

istream& operator>>(istream &stream, Rational &rational)
{
	int numerator, denominator;
	char sign;
	if (stream)
	{
		stream >> numerator >> sign >> denominator;
		if (stream && sign == '/')
		{
			rational = { numerator,denominator };
		}
	}
	return stream;
}

bool operator==(const Rational& lhs, const Rational& rhs)
{
	if (lhs.Denominator() == rhs.Denominator() && lhs.Numerator() == rhs.Numerator())
	{
		return true;
	}
	return false;
}

bool operator<(const Rational& lhs, const Rational& rhs)
{
	int lcm = Lcm(lhs.Denominator(), rhs.Denominator());
	if (lcm*lhs.Numerator() / lhs.Denominator() < lcm*rhs.Numerator() / rhs.Denominator())
	{
		return true;
	}
	return false;
}

Rational Calculate(const Rational& left, char operation, const Rational& right)
{
	switch (operation)
	{
	case '+':
	{
		return Rational(left + right);
		break;
	}
	case '-':
	{
		return Rational(left - right);
		break;
	}
	case '*':
	{
		return Rational(left*right);
		break;
	}
	case '/':
	{
		return Rational(left / right);
		break;
	}
	default:
		break;
	}
}

int main() 
{
	Rational num1;
	cin >> num1;
	cout << num1;
	return 0;
}