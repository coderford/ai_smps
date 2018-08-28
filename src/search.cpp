#include "search.h"
#include <iostream>

struct SearchNode{
	string state;
	SearchNode *parent;
	long depth;
	bool open;
	bool closed;
};

SearchNode *makeNode(string state, SearchNode *parent = NULL) {
	/* Generates a SearchNode and returns a pointer to it. */
	SearchNode *pNode = new SearchNode;
	pNode->state = state;
	pNode->parent = parent;
	pNode->open = false;
	pNode->closed = false;
	if(parent != NULL) 
		pNode->depth = parent->depth+1;
	else pNode->depth = 0;

	return pNode;
}

void freeMem(unordered_map<string, SearchNode *> &nodes) {
	/* Frees memory assigned to all nodes */
	auto it = nodes.begin();
	while(it != nodes.end()) {
		delete (*it).second;
		it++;
	}
}

void resetStatus(unordered_map<string, SearchNode *> &nodes) {
	/* Resets open/closed status of all nodes */
	auto it = nodes.begin();
	while(it != nodes.end()) {
		(*it).second->open = false;
		(*it).second->closed = false;
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
	/*
	 * Breadth First Search goal node based on goalTest and moveGen and 
	 * return a vector of states with the path to the goal node. Strings
	 * are used for state representation because they are hashable and can
	 * be converted to other representations as required.
	 */
	 vector<string> result;			// stores the resulting path
	 list<SearchNode *> openList;	// keeps track of order of insertions
	 unordered_map<string, SearchNode *> nodes;	  // indexes and stores graph
	 
	 /* Add initial state to open and index it */
	 SearchNode *pInit = makeNode(init);
	 pInit->open = true;
	 openList.push_back(pInit);
	 nodes[init] = pInit;

	 while(!openList.empty()) {
		/* Pop a node from the front of the open list */
		SearchNode *N = openList.front();
		openList.pop_front();
		N->open = false;
		N->closed = true;
		
		/* Check if current node is the goal state */
		if(goalTest(N->state)) {
			result = reconstruct(N, nodes);
			freeMem(nodes);			// free up space assigned to nodes
			return result;
		}
		else {
			/* Else, generate new moves and add them to open list */
			vector<string> newMoves = moveGen(N->state);
			for(unsigned i = 0; i<newMoves.size(); i++) {
				string mv = newMoves[i];
				if(nodes.count(mv) == 0) {
					SearchNode *pNode = makeNode(mv, N);
					pNode->open = true;
					openList.push_back(pNode);
					nodes[mv] = pNode;
				}
				else if(!(nodes[mv]->open) && !(nodes[mv]->closed)) {
					/* This segment is unnecessary here, but I am including
					 * it for uniformity */
					nodes[mv]->open = true;
					openList.push_back(nodes[mv]);
				}
			}
		}
	 }
	 freeMem(nodes);
	 return result;		// Using an empty vector to indicate failure
}

vector<string> dfs(string init, vector<string> (*moveGen)(string),
bool (*goalTest)(string)) {	
	/*
	 * Depth First Search goal node based on goalTest and moveGen and 
	 * return a vector of states with the path to the goal node.
	 */
	 vector<string> result;			// stores the resulting path
	 list<SearchNode *> openList;	// keeps track of order of insertions
	 unordered_map<string, SearchNode *> nodes;	  // indexes and stores graph
	 
	 /* add initial state to open and index it */
	 SearchNode *pinit = makeNode(init);
	 pinit->open = true;
	 openList.push_back(pinit);
	 nodes[init] = pinit;

	 while(!openList.empty()) {
		/* pop a node from the back of the open list */
		SearchNode *N = openList.back();
		openList.pop_back();
		N->open = false;
		N->closed = true;
		
		/* Check if current node is the goal state */
		if(goalTest(N->state)) {
			result = reconstruct(N, nodes);
			freeMem(nodes);			// free up space assigned to nodes
			return result;
		}
		else {
			/* Else, generate new moves and add them to open list */
			vector<string> newMoves = moveGen(N->state);
			for(unsigned i = 0; i<newMoves.size(); i++) {
				string mv = newMoves[i];
				if(nodes.count(mv) == 0) {
					SearchNode *pNode = makeNode(mv, N);
					pNode->open = true;
					openList.push_back(pNode);
					nodes[mv] = pNode;
				}
				else if(!(nodes[mv]->open) && !(nodes[mv]->closed)) {
					nodes[mv]->open = true;
					openList.push_back(nodes[mv]);
				}
			}
		}
	 }
	 freeMem(nodes);
	 return result;		// Using an empty vector to indicate failure
}

vector<string> dfid(string init, vector<string> (*moveGen)(string),
bool (*goalTest)(string)) {	
	/* Search using Depth First Iterative Deepening(DFID) */

	vector<string> result;			// stores the resulting path
	list<SearchNode *> openList;	// keeps track of order of insertion
	unordered_map<string, SearchNode *> nodes;	  // indexes and stores graph

	long max_depth = 0;

	/* Add initial state to known graph beforehand */
	SearchNode *pInit = makeNode(init);
	nodes[init] = pInit;

	while(true) {
		long depth_explored = 0;	// actual depth explored 

		/* reset status of previously stored nodes */
		resetStatus(nodes);

		/* Add initial state to open and index it */
		nodes[init]->open = true;
		openList.push_back(nodes[init]);

		while(!openList.empty()) {
			/* Pop a node from the back of the open list */
			SearchNode *N = openList.back();
			openList.pop_back();
			N->open = false;
			N->closed = true;

			if(N->depth > depth_explored)
				depth_explored = N->depth; 
			/* Check if current node is the goal state */
			if(goalTest(N->state)) {
				result = reconstruct(N, nodes);
				freeMem(nodes);			// free up space assigned to nodes
				return result;
			}
			else if(N->depth < max_depth) {
				/* Else, generate new moves and add them to open list */
				/* if the new nodes are not too deep */
				vector<string> newMoves = moveGen(N->state);
				for(unsigned i = 0; i<newMoves.size(); i++) {
					string mv = newMoves[i];
					if(nodes.count(mv) == 0) { 
						SearchNode *pNode = makeNode(mv, N);
						pNode->open = true;
						openList.push_back(pNode);
						nodes[mv] = pNode;
					}
					else if(!(nodes[mv]->open) && !(nodes[mv]->closed)) {
						nodes[mv]->open = true;
						openList.push_back(nodes[mv]);
					}
				}
			}
		}
		if(depth_explored < max_depth) break;
		max_depth++;
	}
	freeMem(nodes);
	return result;		// Using an empty vector to indicate failure
}

vector<string> steepestAscent(string init, vector<string> (*moveGen)(string),
bool (*goalTest)(string), long (*heuristic)(string)) {
	/*
	 * Steepest ascent hill-climbing: returns the best path found.
	 * At each stage, select the next state with best heuristic and stop
	 * if no better heuristic can be achieved.
	 */
	vector<string> result;			// stores the resulting path
	unordered_map<string, SearchNode *> nodes;	  // indexes and stores graph
	
	/* generate node for initial state and index it */
	SearchNode *N = makeNode(init);
	nodes[init] = N;
	long curr_h = heuristic(N->state);		// current heurisitc

	 while(true) {
		/* Check if current node is the goal state */
		if(goalTest(N->state)) {
			result = reconstruct(N, nodes);
			freeMem(nodes);					// free space assigned to nodes
			return result;
		}
		else {
			/* Else, generate new moves and select the best one */
			vector<string> newMoves = moveGen(N->state);
			bool found = false;				// better state found?

			for(unsigned i = 0; i<newMoves.size(); i++) {
				string mv = newMoves[i];
				long new_h = heuristic(mv);

				if(new_h > curr_h) {
					if(found) {
						// forget previous 
						nodes.erase(N->state);
						delete N;
					}
					found = true;
					SearchNode *pNode = makeNode(mv, N);
					nodes[mv] = pNode;

					curr_h = new_h;
					N = pNode;
				}
			}
			if(!found) {
				// cannot climb further; return current path
				result = reconstruct(N, nodes);
				freeMem(nodes);
				return result;
			}
		}
	 }
}
