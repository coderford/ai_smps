/* Solving the sliding 8 puzzle using BFS and DFS:
 *
 *		|3 _ 5|							|1 2 3|
 *		|1 6 4|			 --> 			|4 5 6|
 *		|8 2 7|							|7 8 _|
 *	 initial state					   goal state
 *
 * the above initial state is represented as the string "3_5164827"
 *///////////////////////////////////////////////////////////////////

#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <list>
#include <algorithm>

using namespace std;

vector<string> moveGen(string state);
bool goalTest(string state);
void printState(string state);

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

int main(int argc, char *argv[]) {
	if(argc < 2) {
		cout<<"Usage: 8puzzle <initial state>\n";
		return 0;
	}
	string init_state = argv[1];
	/* Move generation test:
	vector<string> moves = moveGen(init_state);
	for(unsigned i = 0; i<moves.size(); i++)
		printState(moves[i]);
	*/

	vector<string> result = solve_dfs(init_state, moveGen, goalTest);
	if(result.empty())
		cout<<"Failed!\n";
	else {
		for(unsigned i = 0; i<result.size(); i++)
			printState(result[i]);
		cout<<"No. of moves: "<<result.size()-1<<"\n";
	}
	return 0;
}

vector<string> moveGen(string state) {
	vector<string> moves;

	int blank_pos = state.find('_');
	if(blank_pos == string::npos) {
		cout<<"ERROR! invalid state!\n";
		return moves;
	}

	int blank_r = blank_pos/3;
	int blank_c = blank_pos%3;

	// generate moves in all directions possible:
	if(blank_r>0) {			// slide from above
		string mv = state;
		swap(mv[blank_pos], mv[(blank_r-1)*3 + blank_c]);
		moves.push_back(mv);
	}
	if(blank_r<2) {			// slide from below
		string mv = state;
		swap(mv[blank_pos], mv[(blank_r+1)*3 + blank_c]);
		moves.push_back(mv);
	}
	if(blank_c>0) {			// slide from left
		string mv = state;
		swap(mv[blank_pos], mv[(blank_r)*3 + blank_c-1]);
		moves.push_back(mv);
	}
	if(blank_c<2) {			// slide from right
		string mv = state;
		swap(mv[blank_pos], mv[(blank_r)*3 + blank_c+1]);
		moves.push_back(mv);
	}
	
	return moves;
}

bool goalTest(string state) {
	if(state == "12345678_") return true;
	return false;
}

void printState(string state) {
	for(int i = 0; i<3; i++) {
		for(int j = 0; j<3; j++) {
			cout<<state[i*3+j]<<" ";
		}
		cout<<"\n";
	}
	cout<<"\n";
}
