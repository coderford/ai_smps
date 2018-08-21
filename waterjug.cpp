/* The water-jug problem:
 * A state is represented as the string "a,b" where a is the amount
 * of water in the left jug while b is the amount in the right jug.
 * So, for the 4, 3 instance, the initial state will be "0,0" and the final
 * will be "2,0".
 */

#include <iostream>
#include <vector>
#include "search.h"

using namespace std;

string capacity;
string init_state;
string goal_state;

int left_cap;
int right_cap;

vector<string> moveGen(string state);
bool goalTest(string state);
void printState(string state);
void getVals(string pair, int &left, int &right);
string mkState(int left, int right);

int main(int argc, char *argv[]) {
	if(argc < 4) {
		cout<<"Usage: waterjug CAPACITY INIT_STATE GOAL_STATE [ALGORITHM]\n";
		return 0;
	}
	// ^capacity should also be entered as pair of comma-separated numbers
	
	capacity = argv[1];
	init_state = argv[2];
	goal_state = argv[3];
	getVals(capacity, left_cap, right_cap);

	vector<string> result;

	if(argc < 5)
		result = bfs(init_state, moveGen, goalTest);
	else {
		string algo = argv[4];
		if(algo == "dfs") 
			result = dfs(init_state, moveGen, goalTest);
		else if(algo == "bfs")
			result = bfs(init_state, moveGen, goalTest);
		else if(algo == "dfid")
			result = dfid(init_state, moveGen, goalTest);
		else {
			cout<<"ERROR: Unknown algorithm!\n";
			return 1;
		}
	}

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
	int left;
	int right;

	getVals(state, left, right);
	// fill up the left jug:
	moves.push_back(mkState(left_cap, right));

	// fill up the right jug:
	moves.push_back(mkState(left, right_cap));

	// empty the left jug:
	moves.push_back(mkState(0, right));

	// empty the right jug:
	moves.push_back(mkState(left, 0));

	// transfer from left to right:
	if(right < right_cap && left > 0) {
		int newl, newr;
		int space = right_cap - right;
		newr = right + left;
		if(newr > right_cap) {
			newr = right_cap;
			newl = left-space;
		}
		else {
			newl = 0;
		}
		moves.push_back(mkState(newl, newr));
	}

	// transfer from right to left:
	if(left < left_cap && right > 0) {
		int newl, newr;
		int space = left_cap - left;
		newl = left + right;
		if(newl > left_cap) {
			newl = left_cap;
			newr = right-space;
		}
		else {
			newr = 0;
		}
		moves.push_back(mkState(newl, newr));
	}
	return moves;
}

bool goalTest(string state) {
	if(state == goal_state) return true;
	return false;
}

void printState(string state) {
	cout<<state<<"\n";
}

void getVals(string state, int &left, int &right) {
	int comma_idx = state.find(',');
	string l_str = state.substr(0, comma_idx);
	string r_str = state.substr(comma_idx+1, state.length()-comma_idx-1);
	left = stoi(l_str);
	right = stoi(r_str);
}

string mkState(int left, int right) {
	return to_string(left)+","+to_string(right);
}
