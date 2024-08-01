#include <iostream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <vector>
#include "global.h"


using std::cout;
using std::endl;
using std::ostream;
using std::istream;
using std::string;
using std::unordered_map;
using std::pair;
using std::vector;


string read_all(istream& is) {
	std::ostringstream oss;
	oss << is.rdbuf();
	return oss.str();
}

// scan text and fill unordered map with number of occurrences of each char
void fill_map(unordered_map<char, unsigned int>& um, string text) {
	for (char c : text) {
		if (um[c]) {
			um[c] += 1;
		}
		else {
			um[c] = 1;
		}
	}
}

// used in print_map
auto print_key_value = [](const auto& key, const auto& value) {
	cout << "Key: [" << key << "] Value:[" << value << "]" << endl;
	};


void print_map(unordered_map<char, unsigned int>& um) {
	for (const std::pair<const char, const unsigned int>& n : um) {
		print_key_value(n.first, n.second);
	}
}

void print_map(unordered_map<string, unsigned int>& um) {
	for (const std::pair<const string, const unsigned int>& n : um) {
		print_key_value(n.first, n.second);
	}
}

// populate unordered map with strings to use in getting value of each char
void map_to_map(unordered_map<string, unsigned int>& u1, unordered_map<char, unsigned int>& u2) {
	for (const auto& pair : u2) {
		string key(1, pair.first);
		u1[key] = pair.second;
	}
}

void combine_two(unordered_map<string, unsigned int>& u, string* l1, string* l2) {
	// combine elements with keys at l1 and l2 into new element
	// delete two that are combined

	string new_key = *l1 + *l2;
	int new_value = u[*l1] + u[*l2];
	u.insert(
		{ new_key, new_value }
	);
	u.erase(*l1);
	u.erase(*l2);
	

}


void two_lowest(unordered_map<string, unsigned int>& u, string* l1, string* l2, unsigned int* value) {
	if (u.size() > 1) {
		// iterate through unordered map and pull key and value of lowest value
		auto first = u.begin();
		*l1 = first->first;
		unsigned int lowest = first->second;

		for (const auto& pair : u) {
			if (pair.second < lowest) {
				lowest = pair.second;
				*l1 = pair.first;
			}
		}

		if (*l1 == first->first) { // iterate to second if the first lowest found is the first element
			std::advance(first, 1);
		}

		*l2 = first->first;
		unsigned int second_lowest = first->second; // assign next lowest to first value
		for (const auto& pair : u) {
			if (pair.second < second_lowest && pair.first != *l1) { // check if current value is lower, and check that it is not the lowest already found
				second_lowest = pair.second;
				*l2 = pair.first;
			}
		}


	}
	else {
		auto first = u.begin();
		// assign l1 as first and l2 as second
		*l1 = first->first;
		std::advance(first, 1);
		*l2 = first->first;
	}

	// assign value with combined value of two lowest
	*value = u[*l1] + u[*l2];
	//*value = 0;

	// printing used for testing
	//cout << "Two lowest are " << *l1 << " and " << *l2 << " with value " << *value;


	combine_two(u, l1, l2);


}

// tree related utils



void scan_tree(TreeNode* root, int* count) {
	if (root == nullptr) {
		return;
	}

	scan_tree(root->left, count);
	if (root->character != '\0') {
		cout << root->character << ' ';
		(*count)++;
	}
	scan_tree(root->right, count);
}



// build binary tree from bottom using character values based on occurrences
// l1 and l2 are two lowest of the string map found by two_lowest()
// node placement is determined by values in tree_map
void add_node(string* l1, string* l2) {
	TreeNode* parent = new TreeNode();
	string new_key = *l1 + *l2;


	// check if either of the lowest found already exist as nodes
	if (tree_map.find(*l1) != tree_map.end()) {

		if (tree_map.find(*l2) != tree_map.end()) {
			// if both lowest are found, attach together with new parent node
			parent->left = tree_map[*l1];
			parent->right = tree_map[*l2];

			// erase old parent nodes and add new one
			tree_map.erase(*l1);
			tree_map.erase(*l2);
			tree_map.insert( // update tree_map with new parent node
				{ new_key, parent }
			);
		}

		else {
			// if just l1 is found, attach on left side and make new leaf on right
			parent->left = tree_map[*l1];
			TreeNode* right = new TreeNode();
			right->character = (*l2)[0];
			parent->right = right;

			// erase old parent node and add new one
			tree_map.erase(*l1);
			tree_map.insert( // update tree_map with new parent node
				{ new_key, parent }
			);
		}
	}

	// just l2 is found in tree_map
	else if (tree_map.find(*l2) != tree_map.end()) {

		parent->right = tree_map[*l2];
		TreeNode* left = new TreeNode();
		left->character = (*l1)[0];
		parent->left = left;

		// erase old parent node and add new one
		tree_map.erase(*l2);
		tree_map.insert( // update tree_map with new parent node
			{ new_key, parent }
		);
	}

	// two lowest are both not found in tree_map. New tree is started
	else {
		TreeNode* left = new TreeNode();
		TreeNode* right = new TreeNode();
		parent->left = left;
		parent->right = right;
		left->character = (*l1)[0]; // assign characters of new nodes from strings. These strings should both be single chars since they were not found
		right->character = (*l2)[0];

		tree_map.insert( // update tree_map with new parent node
			{ new_key, parent }
		);
	}
}

TreeNode* build_tree(unordered_map<string, unsigned int>& map) {
	string* l1 = new string; // both used to return two lowest values from two_lowest()
	string* l2 = new string;
	unsigned int* value = new unsigned int;
	string new_val;

	while (map.size() > 1) {
		two_lowest(map, l1, l2, value);
		add_node(l1, l2);
	}

	TreeNode* root = new TreeNode();
	if (!tree_map.empty()) {
		auto it = tree_map.begin();
		root = it->second;
	}

	return root;

}

// make table for converting character to binary
// look into using storage other than vectors as another solution
unordered_map<char, vector<bool>> key = {};
vector<bool> position = {};
void keygen(TreeNode* root, vector<bool>& position, unordered_map<char, vector<bool>>& key) {
	if (root == nullptr) {
		return;
	}
	if (root->character != '\0') {
		key[root->character] = position;
	}

	position.push_back(0);
	keygen(root->left, position, key);
	position.pop_back();

	position.push_back(1);
	keygen(root->right, position, key);
	position.pop_back();
}

void print_key(unordered_map<char, vector<bool>> key) {
	for (auto pair : key) {
		cout << pair.first << ": ";
		for (bool b : pair.second) {
			cout << b;
		}
		cout << endl;
	}
}

// use key (unordered_map) to convert text to binary
vector<bool> encode(unordered_map<char, vector<bool>> key, string text) {
	vector<bool> encoded_text = {};
	for (char c : text) {
		// insert value from key c onto end of vector encoded_text
		encoded_text.insert(encoded_text.end(), key[c].begin(), key[c].end());
	}
	return encoded_text;
}