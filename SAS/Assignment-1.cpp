//===- Software-Analysis-Teaching Assignment 1-------------------------------------//
//
//     SVF: Static Value-Flow Analysis Framework for Source Code
//
// Copyright (C) <2013->
//

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
//===-----------------------------------------------------------------------===//

/*
 // Software-Analysis-Teaching Assignment 1 : Graph Traversal
 //
 // 
 */


#include "Assignment-1.h"
using namespace std;

/// TODO: print each path once this method is called, and
/// add each path as a string into std::set<std::string> paths
/// Print the path in the format "START: 1->2->4->5->END", where -> indicate an edge connecting two node IDs
void GraphTraversal::printPath(std::vector<const Node *> &path)
{
    // Construct the path string in the required format
    string pathStr = "START: ";
    
    for (size_t i = 0; i < path.size(); ++i) {
        pathStr += to_string(path[i]->getNodeID());
        if (i != path.size() - 1) {
            pathStr += "->";
        }
    }
    pathStr += "->END";

    // Print the path
    cout << pathStr << endl;

    // Store the path in the set to ensure unique paths
    paths.insert(pathStr);
};

/// TODO: Implement your depth first search here to traverse each program path (once for any loop) from src to dst
void GraphTraversal::DFS(set<const Node *> &visited, vector<const Node *> &path, const Node *src, const Node *dst)
{
    // Mark the source node as visited
    visited.insert(src);
    // Add the source node to the current path
    path.push_back(src);

    // If we have reached the destination, print the path
    if (src == dst) {
        printPath(path);
    } else {
        // Explore all the edges from the current node
        for (const Edge *edge : src->getOutEdges()) {
            const Node *nextNode = edge->getDst();
            // If the destination node of this edge has not been visited, recurse
            if (visited.find(nextNode) == visited.end()) {
                DFS(visited, path, nextNode, dst);
            }
        }
    }

    // Backtrack: remove the current node from the path and visited set
    visited.erase(src);
    path.pop_back();
}
