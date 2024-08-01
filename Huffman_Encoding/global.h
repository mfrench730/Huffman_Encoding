#pragma once

#include <unordered_map>
#include <string>
#include "tree_node.h"

#ifndef GLOBAL_H

// tree_map will store only the top (parent) nodes while building the tree
// only top level nodes will be in this, and only leaves of this tree will have char values
extern std::unordered_map<std::string, TreeNode*> tree_map;

#endif // !GLOBAL_H
