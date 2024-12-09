#include "MatchFinder.h"

using namespace std;

Match::Match(size_t o, size_t l, char c) : offset(o), length(l), nextChar(c) {}

Match MatchFinder::findMatch(const string &window, const string &lookahead)
{
    size_t maxLength = 0;
    size_t bestOffset = 0;

    for (size_t i = 0; i < window.size(); i++)
    {
        size_t length = 0;
        while (length < lookahead.size() && window[i + length] == lookahead[length])
        {
            length++;
        }

        if (length > maxLength)
        {
            maxLength = length;
            bestOffset = i;
        }
    }

    char nextChar = maxLength < lookahead.size() ? lookahead[maxLength] : '\0';
    return Match(window.size() - bestOffset, maxLength, nextChar);
}
