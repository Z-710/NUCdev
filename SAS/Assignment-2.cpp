//===- Software-Analysis-Teaching Assignment 2-------------------------------------//
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
 // Software-Analysis-Teaching Assignment 2 : Source Sink ICFG DFS Traversal
 //
 // 
 */

#include <set>
#include "Assignment-2.h"
#include <iostream>
using namespace SVF;
using namespace std;

/// TODO: print each path once this method is called, and
/// add each path as a string into std::set<std::string> paths
/// Print the path in the format "START->1->2->4->5->END", where -> indicate an ICFGEdge connects two ICFGNode IDs

void ICFGTraversal::collectICFGPath(std::vector<unsigned> &path){
    std::string pathStr = "START";
    for (const auto &node : path) {
        pathStr += "->" + std::to_string(node);
    }
    pathStr += "->END";
    
    // Print the path
    std::cout << pathStr << std::endl;

    // Insert the path into the set
    paths.insert(pathStr);
}


/// TODO: Implement your context-sensitive ICFG traversal here to traverse each program path (once for any loop) from src to dst
void ICFGTraversal::reachability(const ICFGNode *src, const ICFGNode *dst)
{
   std::pair<const ICFGNode*, CallStack> state = {src, callstack};

    // Check if the current node and callstack combination has been visited
    if (visited.count(state) != 0)
        return;

    // Mark this state as visited
    visited.insert(state);

    // Add the current node to the path
    path.push_back(src->getId());

    // If the source and destination are the same, collect the path
    if (src == dst) {
        collectICFGPath(path);
    } else {
        // Traverse all the outgoing edges of the current node
        for (const ICFGEdge *edge : src->getOutEdges()) {
            if (edge->isIntraCFGEdge()) {
                // Intra-procedural edge, continue DFS
                reachability(edge->getDstNode(), dst);
            } else if (edge->isCallCFGEdge()) {
                // Handle a call edge by pushing the calling context onto the callstack
                callstack.push_back(edge->getSrcNode());
                reachability(edge->getDstNode(), dst);
                callstack.pop_back();
            } else if (auto *retNode = SVFUtil::dyn_cast<RetICFGNode>(edge->getDstNode())) {
                // Handle return edge with callstack management
                if (!callstack.empty() && callstack.back() == retNode->getCallICFGNode()) {
                    callstack.pop_back();
                    reachability(edge->getDstNode(), dst);
                    callstack.push_back(retNode->getCallICFGNode());
                } else if (callstack.empty()) {
                    reachability(edge->getDstNode(), dst);
                }
            }
        }
    }

    // Backtrack: remove the current node from the path and unmark the visit
    visited.erase(state);
    path.pop_back();
}
