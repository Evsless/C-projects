#pragma once
#include<deque>
#include<map>
#include<algorithm>
#include<tuple>
#include<stdexcept>
#include"date.h"
using namespace std;

struct Event
{
	set<string> set_events;
	deque<string> deque_events;
};

class Database
{
public:
	void Add(const Date& date, const string& event);
	void Print(ostream& os) const;

	template <typename Predicate>
	vector<pair<Date, string>> FindIf(Predicate predicate) const
	{
		vector<pair<Date, string>> answer;
		for (const auto& item : database)
		{
			for (const auto& event : item.second.deque_events)
			{
				if (predicate(item.first, event))
				{
					answer.push_back({ item.first, event });
				}
			}
		}
		return answer;
	}

	template<typename Predicate>
	int RemoveIf(Predicate predicate)
	{
		deque<Date> date_for_deleting;
		int num_deleted_elements = 0;
		for (auto it = database.begin(); it != database.end(); ++it)
		{
			auto& date = it->first;
			auto& events = it->second.deque_events;
			int counter = 0;
			auto separator = stable_partition(events.begin(), events.end(), [date, predicate](const string& evnt) {return !predicate(date, evnt); });
			counter += distance(separator, events.end());
			// Deleting elements from the back of the vector after using stable_partition algorithm
			for (int i = 0; i < counter; ++i)
			{
				it->second.set_events.erase(events.back());
				events.pop_back();
			}
			// Stacking dates to delete
			if (events.empty())
			{
				date_for_deleting.push_back(date);
			}
			num_deleted_elements += counter;
		}
		
		for (const auto& r_dates : date_for_deleting)
		{
			database.erase(r_dates);
		}

		return num_deleted_elements;
	}


	pair<Date, string> Last(const Date& date) const;
private:
	map<Date, Event> database;
};

ostream& operator<<(ostream& os, const pair<Date, string>& date_event_pair);