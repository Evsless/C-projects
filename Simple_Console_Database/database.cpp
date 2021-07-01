#include <iostream>
#include <string>
#include <set>
#include <map>
#include <exception>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

class Date
{
public:
	Date(){};
	Date(int new_year, int new_month, int new_day)
	{
		year = new_year;
		if (new_month > 12 || new_month < 1)
		{
			throw logic_error("Month value is invalid: " + to_string(new_month));
		}
		month = new_month;
		if (new_day > 31 || new_day < 1)
		{
			throw logic_error("Day value is invalid: " + to_string(new_day));
		}
		day = new_day;
	}

	int GetYear() const
	{
		return year;
	}
	int GetMonth() const
	{
		return month;
	}
	int GetDay() const
	{
		return day;
	}

private:
	int year;
	int day;
	int month;
};

ostream &operator<<(ostream &stream, const Date &date)
{
	stream << setw(4) << setfill('0') << date.GetYear() << "-" << setw(2) << setfill('0') << date.GetMonth() << "-" << setw(2) << setw('0') << date.GetDay();
	return stream;
}

class Database
{
public:
	void AddEvent(const Date &date, const string &event)
	{
		date_event[date].insert(event);
	}
	bool DeleteEvent(const Date &date, const string &event)
	{
		if (date_event[date].count(event) != 0)
		{
			date_event[date].erase(event);
			return true;
		}
		return false;
	}
	int DeleteDate(const Date &date)
	{
		if (date_event.count(date) == 0)
		{
			return 0;
		}
		else
		{
			int size = date_event[date].size();
			date_event.erase(date);
			return size;
		}
	}
	set<string> Find(const Date &date) const
	{
		set<string> events;
		if (date_event.count(date) != 0)
		{
			events = date_event.at(date);
		}
		return events;
	}
	void Print() const
	{
		for (const auto &map_item : date_event)
		{
			if (map_item.first.GetYear() < 0)
			{
				continue;
			}
			for (const auto &event : map_item.second)
			{
				cout << map_item.first << " " << event << endl;
			}
		}
	}

private:
	map<Date, set<string>> date_event;
};

bool operator<(const Date &rhs, const Date &lhs)
{
	return vector<int>{lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()} < vector<int>{rhs.GetYear(), rhs.GetMonth(), rhs.GetDay()};
}

void EnsureOperationCode(const string &command)
{
	vector<string> commands = {"Add", "Del", "Find", "Print"};
	if (count(begin(commands), end(commands), command) == 0)
	{
		stringstream error;
		error << "Unknown command: " << command;
		throw runtime_error(error.str());
	}
}

Date ParseDate(stringstream &command_ss)
{
	stringstream tmp(command_ss.str());
	string date, operation_code;
	tmp >> operation_code;
	tmp >> date;
	//CheckLastSymbolIntDate(date);
	if (command_ss)
	{
		int year = 0, month = 0, day = 0;
		char l_sign, r_sign;
		command_ss >> year >> l_sign >> month >> r_sign >> day;
		if (command_ss && l_sign == '-' && r_sign == '-' && command_ss.eof())
		{
			if (month > 12 || month <= 0)
			{
				throw runtime_error("Month value is invalid: " + to_string(month));
			}
			if (day <= 0 || day > 31)
			{
				throw runtime_error("Day value is invalid: " + to_string(day));
			}
			return Date(year, month, day);
		}
	}
	throw logic_error("Wrong date format: " + date);
}

int main()
{
	Database db;
	string command;
	while (getline(cin, command))
	{
		if (command.empty())
		{
			continue;
		}
		stringstream command_ss(command);
		string operation_code;
		command_ss >> operation_code;
		try
		{
			EnsureOperationCode(operation_code);
		}
		catch (const std::logic_error &err)
		{
			cout << err.what() << endl;
			break;
		}
		if (operation_code == "Add")
		{
			Date date;
			string event;
			try
			{
				date = ParseDate(command_ss);
				command_ss >> event;
				db.AddEvent(date, event);
			}
			catch (const std::logic_error &exc)
			{
				cout << exc.what() << endl;
				break;
			}
		}
		else if (operation_code == "Del")
		{
			Date date;
			string event;
			try
			{
				date = ParseDate(command_ss);
				command_ss >> event;
				if (event.empty())
				{
					cout << "Deleted " << db.DeleteDate(date) << " events" << endl;
				}
				else
				{
					if (db.DeleteEvent(date, event))
					{
						cout << "Deleted successfully" << endl;
					}
					else
					{
						cout << "Event not found" << endl;
					}
				}
			}
			catch (const std::logic_error &exc)
			{
				cout << exc.what() << endl;
				break;
			}
		}
		else if (operation_code == "Find")
		{
			Date date;
			set<string> events;
			try
			{
				date = ParseDate(command_ss);
				events = db.Find(date);
				if (events.empty())
				{
					continue;
				}
				else
				{
					for (const auto &item : events)
					{
						cout << item << endl;
					}
				}
			}
			catch (const std::logic_error &exc)
			{
				cout << exc.what() << endl;
				break;
			}
		}
		else if (operation_code == "Print")
		{
			db.Print();
		}
	}
	return 0;
}