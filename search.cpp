#include "search.h"

struct SearchNode{
	string state;
	SearchNode *parent;
	long depth;
};

SearchNode *makeNode(string state, SearchNode *parent = NULL) {
	/* Generates a SearchNode and returns a pointer to it. */
	SearchNode *pNode = new SearchNode;
	pNode->state = state;
	pNode->parent = parent;
	if(parent != NULL) 
		pNode->depth = parent->depth;
	else pNode->depth = 0;

	return pNode;
}

void cleanUp(unordered_map<string, SearchNode *> &nodes) {
	/* Frees memory assigned to all nodes */
	auto it = nodes.begin();
	while(it != nodes.end()) {
		delete (*it).second;
		it++;
	}
}

vector<string> reconstruct(SearchNode *goal, 
unordered_map<string, SearchNode *> &nodes) {
	/* Reconstructs the path taken to reach goal */
	vector<string> path;
	path.push_back(goal->state);
	SearchNode *curr = goal;

	while(curr->parent != NULL) {
		curr = curr->parent;
		path.push_back(curr->state);
	}
	
	reverse(path.begin(), path.end());
	return path;
}

vector<string> bfs(string init, vector<string> (*moveGen)(string),
bool (*goalTest)(string)) {	
	/* Breadth First Search goal node based on goalTest and moveGen and 
	 * return a vector of states with the path to the goal node. Strings
	 * are used for state representation because they are hashable and can
	 * be converted to other representations as required.
	 */
	 vector<string> result;			// stores the resulting path
	 list<SearchNode *> openList;	// keeps track of order of insertions
	 unordered_map<string, SearchNode *> nodes;	  // indexes all nodes
	 
	 /* Add initial state to open and index it */
	 SearchNode *pInit = makeNode(init);
	 openList.push_back(pInit);
	 nodes[init] = pInit;

	 while(!openList.empty()) {
		/* Pop a node from the front of the open list */
		SearchNode *N = openList.front();
		openList.pop_front();
		
		/* Check if current node is the goal state */
		if(goalTest(N->state)) {
			result = reconstruct(N, nodes);
			cleanUp(nodes);			// free up space assigned to nodes
			return result;
		}
		else {
			/* Else, generate new moves and add them to open list */
			vector<string> newMoves = moveGen(N->state);
			for(unsigned i = 0; i<newMoves.size(); i++) {
				string mv = newMoves[i];
				if(nodes.count(mv) == 0) {
					SearchNode *pNode = makeNode(mv, N);
					openList.push_back(pNode);
					nodes[mv] = pNode;
				}
			}
		}
	 }
	 cleanUp(nodes);
	 return result;		// Using an empty vector to indicate failure
}

vector<string> dfs(string init, vector<string> (*moveGen)(string),
bool (*goalTest)(string)) {	
	/* Depth First Search goal node based on goalTest and moveGen and 
	 * return a vector of states with the path to the goal node.
	 */
	 vector<string> result;			// stores the resulting path
	 list<SearchNode *> openList;	// keeps track of order of insertions
	 unordered_map<string, SearchNode *> nodes;	  // indexes all nodes
	 
	 /* Add initial state to open and index it */
	 SearchNode *pInit = makeNode(init);
	 openList.push_back(pInit);
	 nodes[init] = pInit;

	 while(!openList.empty()) {
		/* Pop a node from the back of the open list */
		SearchNode *N = openList.back();
		openList.pop_back();
		
		/* Check if current node is the goal state */
		if(goalTest(N->state)) {
			result = reconstruct(N, nodes);
			cleanUp(nodes);			// free up space assigned to nodes
			return result;
		}
		else {
			/* Else, generate new moves and add them to open list */
			vector<string> newMoves = moveGen(N->state);
			for(unsigned i = 0; i<newMoves.size(); i++) {
				string mv = newMoves[i];
				if(nodes.count(mv) == 0) {
					SearchNode *pNode = makeNode(mv, N);
					openList.push_back(pNode);
					nodes[mv] = pNode;
				}
			}
		}
	 }
	 cleanUp(nodes);
	 return result;		// Using an empty vector to indicate failure
}
