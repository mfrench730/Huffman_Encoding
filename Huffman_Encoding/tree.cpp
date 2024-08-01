#include <iostream>
#include <string>
#include <sstream>
#include <unordered_map>
#include "utils.cpp"

using std::cout;
using std::endl;
using std::ostream;
using std::istream;
using std::string;
using std::unordered_map;
using std::pair;

unordered_map<string, TreeNode*> tree_map;

struct TreeNode {
	char character;
	TreeNode* left;
	TreeNode* right;
	TreeNode* parent;

	TreeNode(char c) : character(c), left(nullptr), right(nullptr) , parent(nullptr){}
	TreeNode() : left(nullptr), right(nullptr), parent(nullptr) {}
};

// not currently used, remove at end
void scan_tree(TreeNode* root, string* s) {
	char left, right;
	s->push_back(root->left->character);
	scan_tree(root->left, s);
	scan_tree(root->right, s);
	s->push_back(root->right->character);
}

// used to track node additions in tree building
void add_tree_map(unordered_map<string, TreeNode*>& tree_map, string s, TreeNode* node) {

}

// build binary tree from bottom using character values based on occurrences
// current is node being built off of. start_left determines if this node is to be the left or right child of the new node
void add_node(TreeNode* current, char left_char = '\0', char right_char = '\0', bool start_left) {
	TreeNode* parent = new TreeNode;

	if (current != nullptr) {
		if (start_left) { // check if new node is building of off left or right
			TreeNode* right = new TreeNode;

			parent->left = current;
			parent->right = right;

			current->parent = parent;

			right->character = right_char;
			right->parent = parent;

		}
		else {
			TreeNode* left = new TreeNode;

			parent->right = current;
			parent->left = left;

			current->parent = parent;

			left->character = left_char;
			left->parent = parent;

		}
	}
	else {
		TreeNode* left = new TreeNode;
		TreeNode* right = new TreeNode;

		left->character = left_char;
		left->parent = parent;

		right->character = right_char;
		right->parent = parent;

	}
}

TreeNode* build_tree(unordered_map<string, unsigned int> map, unordered_map<string, TreeNode*> tree_map) {
	int left, right = 0; // stores value of highest combined tree value of each side
	string* l1 = new string; // both used to return two lowest values from two_lowest()
	string* l2 = new string;
	unsigned int* value;

	// new map to store string and TreeNode* combinations as they are added to tree
	//


	TreeNode* current = new TreeNode;

	
	while (map.size() > 2) {
		two_lowest(map, l1, l2, value);

	}

}