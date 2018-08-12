#ifndef SEARCH_H
#define SEARCH_H

#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <list>
#include <algorithm>
using namespace std;

vector<string> reconstruct(string goal,
unordered_map<string, string> &parents);

vector<string> bfs(string init, vector<string> (*moveGen)(string),
bool (*goalTest)(string));

vector<string> dfs(string init, vector<string> (*moveGen)(string),
bool (*goalTest)(string));

vector<string> dfid(string init, vector<string> (*moveGen)(string), 
bool (*goalTest)(string));

#endif
