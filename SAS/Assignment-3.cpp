//===- Software-Analysis-Teaching Assignment 3-------------------------------------//
//
//    SVF: Static Value-Flow Analysis Framework for Source Code       
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
 // Software-Analysis-Teaching Assignment 3 : Andersen's pointer analysis
 //
 // 
 */

#include "SVF-LLVM/LLVMUtil.h"
#include "SVF-LLVM/SVFIRBuilder.h"
#include "WPA/Andersen.h"
#include "Assignment-3.h"
using namespace SVF;
using namespace llvm;
using namespace std;


// TODO: Implement your Andersen's Algorithm here
void AndersenPTA::solveWorklist(){
    processAllAddr();  // Initialize the points-to sets based on address constraints

    // Process the worklist until it's empty
    while (!isWorklistEmpty()) {
        NodeID p = popFromWorklist();
        const PointsTo& pts_p = getPts(p);
        ConstraintNode* pNode = consCG->getConstraintNode(p);

        for (PointsTo::iterator it = pts_p.begin(), ie = pts_p.end(); it != ie; ++it) {
            NodeID o = *it;

            // Process Store edges: q → p
            for (ConstraintEdge* edge : pNode->getStoreInEdges()) {
                ConstraintNode* qNode = edge->getSrcNode();
                NodeID q = qNode->getId();
                if (addCopyEdge(q, o)) {
                    pushIntoWorklist(q);
                }
            }

            // Process Load edges: p → r
            for (ConstraintEdge* edge : pNode->getLoadOutEdges()) {
                ConstraintNode* rNode = edge->getDstNode();
                NodeID r = rNode->getId();
                if (addCopyEdge(o, r)) {
                    pushIntoWorklist(r);
                }
            }
        }

        // Process Copy edges: p → x
        for (ConstraintEdge* edge : pNode->getDirectOutEdges()) {
            if (edge->getEdgeKind() == ConstraintEdge::Copy) {
                NodeID x = edge->getDstID();
                if (unionPts(x, p)) {
                    pushIntoWorklist(x);
                }
            }
        }
    }
}

// Process all address constraints to initialize pointers' points-to sets
void AndersenPTA::processAllAddr(){
    for (ConstraintGraph::const_iterator nodeIt = consCG->begin(), nodeEit = consCG->end(); nodeIt != nodeEit; nodeIt++)
    {
        ConstraintNode *cgNode = nodeIt->second;
        for (ConstraintEdge* edge : cgNode->getAddrInEdges()) {
            const AddrCGEdge *addr = SVFUtil::cast<AddrCGEdge>(edge);
            NodeID dst = addr->getDstID();
            NodeID src = addr->getSrcID();
            if (addPts(dst, src))
                pushIntoWorklist(dst);
        }
    }
}
