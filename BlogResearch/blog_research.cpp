#include "test_runner.h"
#include "profile.h"

#include <string>
#include <functional>
#include <iterator>
#include <map>
#include <vector>
#include <sstream>
#include <future>

using namespace std;

struct Stats
{
    map<string, int> word_frequences;

    void operator+=(const Stats &other)
    {
        for (auto &[word, num_of_entries] : other.word_frequences)
        {
            word_frequences[word] += num_of_entries;
        }
    }
};

vector<string> SplitLine(const string &line)
{
    istringstream split_line(line);
    return {istream_iterator<string>(split_line), istream_iterator<string>()};
}

Stats ExploreLine(const set<string> &key_words, const string &line)
{
    Stats result;
    for (auto &word : SplitLine(line))
    {
        if (key_words.count(word) > 0)
        {
            ++result.word_frequences[word];
        }
    }
    return result;
}

Stats ExploreBatch(const set<string> &key_words, vector<string> lines) //check adding a constant
{
    Stats result;
    for (const string &line : lines)
    {
        result += ExploreLine(key_words, line);
    }
    return result;
}

Stats ExploreKeyWordsSingleThread(
    const set<string> &key_words, istream &input)
{
    Stats result;
    for (string line; getline(input, line);)
    {
        result += ExploreLine(key_words, line);
    }
    return result;
}

Stats ExploreKeyWords(const set<string> &key_words, istream &input)
{
    const size_t max_batch_size = 2;

    vector<string> batch;
    batch.reserve(max_batch_size);
    vector<future<Stats>> futures;

    for (string line; getline(input, line);)
    {
        batch.push_back(move(line));
        if (batch.size() >= max_batch_size)
        {
            futures.push_back(
                async(ExploreBatch, ref(key_words), move(batch)));
        }
    }

    Stats result;

    if (!batch.empty())
    {
        result += ExploreBatch(key_words, move(batch));
    }

    for (auto &f : futures)
    {
        result += f.get();
    }

    return result;
}

// void TestSplit()
// {
//     const vector<string> expected1 = {
//         "abc", "def", "ghi,", "!", "jklmnop-qrs,", "tuv"};
//     ASSERT_EQUAL(SplitLine("  abc def ghi, !  jklmnop-qrs, tuv"), expected1);

//     const vector<string> expected2 = {"a", "b"};
//     ASSERT_EQUAL(SplitLine("a b      "), expected2);
//     ASSERT_EQUAL(SplitLine(""), vector<string>());
// }

// void TestBasic()
// {
//     const set<string> key_words = {"yangle", "rocks", "sucks", "all"};

//     stringstream ss;
//     ss << "this new yangle service really rocks\n";
//     ss << "It sucks when yangle isn't available\n";
//     ss << "10 reasons why yangle is the best IT company\n";
//     ss << "yangle rocks others suck\n";
//     ss << "Goondex really sucks, but yangle rocks. Use yangle\n";

//     const auto stats = ExploreKeyWords(key_words, ss);
//     const map<string, int> expected = {
//         {"yangle", 6},
//         {"rocks", 2},
//         {"sucks", 1}};
//     ASSERT_EQUAL(stats.word_frequences, expected);
// }

int main()
{
    // TestRunner tr;
    // RUN_TEST(tr, TestSplit);
    // RUN_TEST(tr, TestBasic);
    return 0;
}