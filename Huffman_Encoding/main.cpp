#include <iostream>
#include <fstream>
#include <string>
#include "utils.cpp"

using std::cout;
using std::ofstream;
using std::ifstream;
using std::string;
using std::unordered_map;
using std::endl;



int main() {
	ifstream input_file("sample_long.txt");
	string text = read_all(input_file);
	cout << text << endl;
	cout << sizeof(text) << endl;

	unordered_map<char, unsigned int> charMap;
	fill_map(charMap, text);
	//print_map(charMap);
	cout << endl;

	unordered_map<string, unsigned int> stringMap;
	map_to_map(stringMap, charMap);
	print_map(stringMap);

	// test finding lowest
	/*string* l1 = new string;
	string* l2 = new string;
	unsigned int* value = new unsigned int;
	two_lowest(stringMap, l1, l2, value);
	add_node(l1, l2);

	cout << endl;
	print_map(stringMap);


	string key = *l1 + *l2;
	scan_tree(tree_map[key]);*/

	TreeNode* tree = new TreeNode();
	tree = build_tree(stringMap);
	int scan_count = 0;
	scan_tree(tree, &scan_count);
	cout << endl;
	cout << "Tree scan count: " << scan_count << endl;

	print_map(stringMap);

	vector<bool> position = {};
	unordered_map<char, vector<bool>> key = {};

	keygen(tree, position, key);
	print_key(key);

	vector<bool> encoded_text = encode(key, text);
	/*for (bool b : encoded_text) {
		cout << b;
	}*/


	cout << endl;
	cout << "Text size: " << text.size() * sizeof(char) << endl;

	// .size() of vector<bool> returns num of bits. Divide by 8 to get num of bytes
	cout << "Encoded size: " << (encoded_text.size() + 7) / 8 << endl;
}

