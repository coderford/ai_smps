/* State representation and move generation for the 8 puzzle:
 *		|3   5|
 *		|1 6 4|
 *		|8 2 7|
 *
 * Note: compile with -std=c++11 flag!!
 *//////////////////////////////////////////////////////////

#include <iostream>
#include <vector>
using namespace std;

void swap(int &a, int &b) {
	int tmp;
	tmp = a;
	a = b;
	b = tmp;
}

vector<vector<vector<int> > > moveGen(vector<vector<int> > &state) {
	vector<vector<vector<int> > > result;

	// Find out the position of the blank:
	int br, bc;								// row and col of blank
	for(int i = 0; i<3; i++) 
		for(int j = 0; j<3; j++) 
			if(state[i][j] == 0) {
				br = i;
				bc = j; 
			}
	
	// Generate moves in all possible directions:
	vector<vector<int> > tmp_move = state;	
	if(br < 2) {
		swap(tmp_move[br][bc], tmp_move[br+1][bc]); // Fill in from down
		result.push_back(tmp_move);
	}
	tmp_move = state;
	if(br > 0) {
		swap(tmp_move[br][bc], tmp_move[br-1][bc]); // Fill in from up
		result.push_back(tmp_move);
	}
	tmp_move = state;
	if(bc < 2) {
		swap(tmp_move[br][bc], tmp_move[br][bc+1]); // Fill in from right 
		result.push_back(tmp_move);
	}
	tmp_move = state;
	if(bc > 0) {
		swap(tmp_move[br][bc], tmp_move[br][bc-1]); // Fill in from left 
		result.push_back(tmp_move);
	}
	return result;
}

void print2DVector(vector<vector<int> > &v) {
	int rows = v.size();
	if(rows == 0) return;
	int cols = v[0].size();

	for(int i = 0; i<rows; i++) {
		for(int j = 0; j<cols; j++) {
			cout<<v[i][j]<<" ";
		}
		cout<<"\n";
	}
	cout<<"\n";
}

int main(int argc, char *argv[]) {
	// Simplest way to represent the state will be to use an 3x3 vector/array:
	vector<vector<int> > curr = {{3, 0, 5}, {1, 6, 4}, {8, 2, 7}};
	// ^ note that 0 is used to represent blank space

	vector<vector<vector<int> > > move_set = moveGen(curr);
	for(unsigned int i = 0; i<move_set.size(); i++) {
		print2DVector(move_set[i]);
	}

	return 0;
}
