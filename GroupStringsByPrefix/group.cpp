#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <utility>
using namespace std;

template <typename RandomIt>
pair<RandomIt, RandomIt> FindStartsWithChar(RandomIt range_begin, RandomIt range_end, char prefix)
{
	auto left_border = lower_bound(range_begin, range_end, string(1, prefix));
	char symbolic_border = static_cast<char>(prefix + 1);
	auto right_border = lower_bound(range_begin, range_end, string(1, symbolic_border));
	return make_pair(left_border, right_border);
}

template <typename RandomIt>
pair<RandomIt, RandomIt> FindStartsWith(RandomIt range_begin, RandomIt range_end, const string &prefix)
{
	auto left_border = lower_bound(range_begin, range_end, prefix);
	string border = prefix;
	++border[prefix.size() - 1];
	auto right_border = lower_bound(range_begin, range_end, border);
	return make_pair(left_border, right_border);
}

int main()
{
	const vector<string> sorted_strings = {"moscow", "motovilikha", "murmansk"};

	const auto mo_result = FindStartsWith(begin(sorted_strings), end(sorted_strings), "mo");
	for (auto it = mo_result.first; it != mo_result.second; ++it)
	{
		cout << *it << " ";
	}
	cout << endl;

	const auto mt_result = FindStartsWith(begin(sorted_strings), end(sorted_strings), "mt");
	cout << (mt_result.first - begin(sorted_strings)) << " " << (mt_result.second - begin(sorted_strings)) << endl;

	const auto na_result = FindStartsWith(begin(sorted_strings), end(sorted_strings), "na");
	cout << (na_result.first - begin(sorted_strings)) << " " << (na_result.second - begin(sorted_strings)) << endl;
	return 0;
}
