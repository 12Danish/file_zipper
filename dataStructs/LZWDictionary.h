#ifndef LZW_DICTIONARY_H
#define LZW_DICTIONARY_H

#include <unordered_map>
#include <string>

using namespace std;

class LZWDictionary
{
private:
    unordered_map<string, int> dictionary;
    int nextCode;

public:
    LZWDictionary();
    int getCode(const string &key);
    void addEntry(const string &key);
    bool contains(const string &key);
};

#endif // LZW_DICTIONARY_H
