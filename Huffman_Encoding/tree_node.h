#pragma once

#ifndef TREE_NODE_H

struct TreeNode {
	char character;
	TreeNode* left;
	TreeNode* right;
	TreeNode* parent;

	TreeNode(char c) : character(c), left(nullptr), right(nullptr), parent(nullptr) {}
	TreeNode() : character('\0'), left(nullptr), right(nullptr), parent(nullptr) {}
};

#endif // !TREE_NODE_H
