#include "LZWDictionary.h"

using namespace std;

LZWDictionary::LZWDictionary() : nextCode(256)
{
    for (int i = 0; i < 256; i++)
    {
        dictionary[string(1, i)] = i;
    }
}

int LZWDictionary::getCode(const string &key)
{
    return dictionary[key];
}

void LZWDictionary::addEntry(const string &key)
{
    dictionary[key] = nextCode++;
}

bool LZWDictionary::contains(const string &key)
{
    return dictionary.find(key) != dictionary.end();
}
