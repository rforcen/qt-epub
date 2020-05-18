#ifndef TEXTINDEXER_H
#define TEXTINDEXER_H

#include <algorithm>
#include <list>
#include <map>
#include <regex>
#include <string>
#include <vector>

using std::back_inserter;
using std::copy;
using std::list;
using std::map;
using std::regex;
using tkiter = std::sregex_token_iterator;
using std::string;
using std::tolower;
using std::transform;
using std::vector;

class TextIndexer {
 public:
  TextIndexer() {}

  void operator<<(string s) { add_indexes(s); }

  void add_indexes(string s) {
    string w;

    for (auto &ch : s) {
      ch = tolower(ch);
      if (isalnum(ch))
        w.push_back(ch);
      else {
        if (!w.empty()) {
          index[w].push_back(pos);
          w.clear();
        }
      }
      pos++;
    }
    if (!w.empty()) index[w].push_back(pos);
  }

  void clear() {
    index.clear();
    pos = 0;
  }

 public:
  map<string, vector<size_t>> index;

  int pos = 0;
};

#endif  // TEXTINDEXER_H
