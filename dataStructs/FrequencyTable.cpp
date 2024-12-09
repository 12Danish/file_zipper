#include "FrequencyTable.h"

using namespace std;

void FrequencyTable::calculateFrequency(const vector<char> &data)
{
    for (char c : data)
    {
        frequencyMap[c]++;
    }
}

void FrequencyTable::printFrequencyTable() const
{
    for (const auto &pair : frequencyMap)
    {
        cout << pair.first << ": " << pair.second << endl;
    }
}

const unordered_map<char, int> &FrequencyTable::getFrequencyMap() const
{
    return frequencyMap;
}
