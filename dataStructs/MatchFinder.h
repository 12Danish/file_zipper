#ifndef MATCH_FINDER_H
#define MATCH_FINDER_H

#include <string>

using namespace std;

struct Match {
    size_t offset;
    size_t length;
    char nextChar;

    Match(size_t o, size_t l, char c);
};

class MatchFinder {
public:
    Match findMatch(const string& window, const string& lookahead);
};

#endif // MATCH_FINDER_H
