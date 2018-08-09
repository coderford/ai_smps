#include "search.h"

vector<string> reconstruct(string goal, 
unordered_map<string, string> &parents) {
	vector<string> path;
	path.push_back(goal);
	string curr = goal;
	string parent = parents[curr];

	while(parent != "") {
		path.push_back(parent);
		curr = parent;
		parent = parents[curr];
	}
	
	reverse(path.begin(), path.end());
	return path;
}

vector<string> solve_bfs(string init, vector<string> (*moveGen)(string), 
											    bool (*goalTest)(string))
{
	unordered_set<string> open;
	list<string> open_list;					// for keeping track of insertions
	unordered_set<string> closed;
	unordered_map<string, string> parents;	// for reconstructing path
	
	open.insert(init);
	open_list.push_back(init);
	parents[init] = "";

	while(!open.empty()) {
		string N = open_list.front();
		open_list.pop_front();
		open.erase(N);
		closed.insert(N);

		if(goalTest(N)) {
			return reconstruct(N, parents);
		}
		else {
			vector<string> new_moves = moveGen(N);
			for(unsigned i = 0; i<new_moves.size(); i++) {
				string mv = new_moves[i];
				if(open.count(mv) == 0 && closed.count(mv) == 0) {
					open.insert(mv);
					open_list.push_back(mv);
					parents[mv] = N;
				}
			}
		}
	}
	
	vector<string> failed;
	return failed;
}

vector<string> solve_dfs(string init, vector<string> (*moveGen)(string), 
											    bool (*goalTest)(string))
{
	unordered_set<string> open;
	list<string> open_list;					// for keeping track of insertions
	unordered_set<string> closed;
	unordered_map<string, string> parents;	// for reconstructing path
	
	open.insert(init);
	open_list.push_back(init);
	parents[init] = "";

	while(!open.empty()) {
		string N = open_list.back();
		open_list.pop_back();
		open.erase(N);
		closed.insert(N);

		if(goalTest(N)) {
			return reconstruct(N, parents);
		}
		else {
			vector<string> new_moves = moveGen(N);
			for(unsigned i = 0; i<new_moves.size(); i++) {
				string mv = new_moves[i];
				if(open.count(mv) == 0 && closed.count(mv) == 0) {
					open.insert(mv);
					open_list.push_back(mv);
					parents[mv] = N;
				}
			}
		}
	}
	
	vector<string> failed;
	return failed;
}

