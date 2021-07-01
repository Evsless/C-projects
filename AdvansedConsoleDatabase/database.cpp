#include"database.h"
#include"date.h"

void Database::Add(const Date& date, const string& event)
{
	auto element = database[date].set_events.insert(event);
	if (element.second)
	{
		database[date].deque_events.push_back(event);
	}
}

void Database::Print(ostream& os) const
{
	for (const auto& date : database)
	{
		for (const auto& event : date.second.deque_events)
		{
			os << date.first << ' ' << event << endl;
		}
	}
}

	pair<Date, string> Database::Last(const Date& date) const
	{
		auto it = database.upper_bound(date);
		if (it == database.begin())
		{
			throw invalid_argument("No entries");
		}
		return { prev(it)->first, prev(it)->second.deque_events.back() };
	}

	ostream& operator<<(ostream& os, const pair<Date, string>& date_event_pair)
	{
		return os << date_event_pair.first << ' ' << date_event_pair.second;
	}