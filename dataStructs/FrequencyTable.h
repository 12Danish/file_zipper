#ifndef FREQUENCY_TABLE_H
#define FREQUENCY_TABLE_H

#include <unordered_map>
#include <vector>
#include <iostream>

using namespace std;

class FrequencyTable
{
private:
    unordered_map<char, int> frequencyMap;

public:
    void calculateFrequency(const vector<char> &data);
    void printFrequencyTable() const;
    const unordered_map<char, int> &getFrequencyMap() const;
};

#endif // FREQUENCY_TABLE_H
