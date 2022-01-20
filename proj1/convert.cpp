#include "convert.hpp"
#include "Wordset.hpp"
#include <iostream>
#include <set>
#include <sstream>
#include <map>
#include <stack>
#include <queue>


// You should not need to change this function.
void loadWordsIntoTable(WordSet & words, std::istream & in)
{
	std::string line, word;
	std::stringstream ss;

	while(	getline(in, line) )
	{
		ss.clear();
		ss << line;
		while( ss >> word )
		{
			words.insert( word );
		}
	}
}

// attention: use &neigh, because we need to change neigh
void generateNeighbors(const std::string &start, std::vector<std::string> &neighbors, const WordSet & words) {
    neighbors.clear();

    // a neighbor is one letter different than string start
    for (int i = 0; i < start.size(); i++) {
        std::string s = start;
        for (char c = 'a'; c <= 'z'; c++) {
            if (c == start[i])
                continue;
            s[i] = c;
            if (words.contains(s)) {
                neighbors.push_back(s);
            }
        }
    }
}

// attention: use &map, because we need to change map
void bfs(const std::string & start, const std::string & target,
         std::map<std::string, std::string>& map, const WordSet & words) {

    std::queue<std::string> queue;
    queue.push(start);

    while (!queue.empty()) {
        std::string s = queue.front();
        queue.pop();

        std::vector<std::string> neighbors;
        generateNeighbors(s, neighbors, words);

        for (auto& next: neighbors) {
            queue.push(next);
            if (map[next].empty())
                map[next] = s;
            if (next == target)
                return;
        }
    }
}


// You probably want to change this function.
std::string convert(const std::string & start, const std::string & target, const WordSet & words)
{
    std::string res;
    if (start.size() != target.size())
        return res;

    std::map<std::string, std::string> map;  // parent[]
    bfs(start, target, map, words);

    if (map[target].empty())
        return res;

    // backtrace
    std::string s = target;
    while (s != start) {
        res = " --> "+ s + res;
        s = map[s];
    }
    res = s + res;
    return res;
}
