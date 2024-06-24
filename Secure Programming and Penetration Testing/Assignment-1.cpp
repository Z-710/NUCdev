
//===- Teaching-Software-Verification Assignment 1-------------------------------------//
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
 // Teaching-Software-Verification Assignment 1 : Graph Traversal
 //
 // 
 */


#include "Assignment-1.h"
using namespace std;
#include <sstream>
/// TODO: print each path once this method is called, and
/// add each path as a string into std::set<std::string> paths
/// Print the path in the format "START: 1->2->4->5->END", where -> indicate an edge connecting two node IDs
void GraphTraversal::printPath(std::vector<const Edge *> &path)
{
    std::ostringstream oss;
    oss << "START: ";
    for (size_t i = 0; i < path.size(); ++i) {
        oss << path[i]->getDst()->getNodeID();
        if (i < path.size() - 1) {
            oss << "->";
        }
    }
    oss << "->END";

    std::string pathString = oss.str();
    paths.insert(pathString);

    std::cout << pathString << std::endl;
};

/// TODO: Implement your depth first search here to traverse each program path (once for any loop) from src to dst
void GraphTraversal::DFS(const Edge *src_edge, const Node *dst)
{
    Node *src = src_edge->getDst();
    visited.insert(src);
    path.push_back(src_edge);
    if(src == dst){
        printPath(path);
    }
    for(const Edge *e : src->getOutEdges()){
        const Node *neighbor = e->getDst();
        if(visited.find(neighbor) == visited.end()){
            DFS(e,dst);
        }
    }
    visited.erase(src);
    path.pop_back();
}
