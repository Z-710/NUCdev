//===- Software-Analysis-Teaching Assignment 4-------------------------------------//
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
 // Software-Analysis-Teaching Assignment 4: Information Flow Tracking
 //
 // 
 */
#include "Assignment-4.h"
#include <fstream>
#include <sstream>
#include <typeinfo>
#include <string>

using namespace SVF;
using namespace llvm;
using namespace std;


// Get sources function names read from checker_source_api collected from a text file
std::set<const CallICFGNode *>& TaintGraphTraversal::identifySources()
{
    for (const CallICFGNode *cs : pag->getCallSiteSet())
    {
        const SVFFunction *fun = cs->getCalledFunction();
        if (checker_source_api.find(fun->getName()) != checker_source_api.end())
        {
            sources.insert(cs);
        }
    }
    return sources;
}
// Get sinks function names read from checker_sink_api collected from a text file
std::set<const CallICFGNode *>& TaintGraphTraversal::identifySinks()
{
    for (const CallICFGNode *cs : pag->getCallSiteSet())
    {
        const SVFFunction *fun = cs->getCalledFunction();
        if (checker_sink_api.find(fun->getName()) != checker_sink_api.end())
        {
            sinks.insert(cs);
        }
    }
    return sinks;
}

// Start taint checking. 
// There is a tainted flow from p@source to q@sink 
// if (1) alias(p,q)==true and (2) source reaches sink on ICFG.
void TaintGraphTraversal::taintChecking(){
    // configure sources and sinks for taint analysis
    readSrcSnkFromFile("./Assignment-4/SrcSnk.txt");
    ander = new AndersenPTA(pag);
    ander->analyze();
    for(const CallICFGNode* src : identifySources()){
        for(const CallICFGNode* snk : identifySinks()){
            if(aliasCheck(src,snk))
                reachability(src, snk);
        }
    }
}

/// TODO: print each path once this method is called, and
/// (1) add each path (a sequence of node IDs) as a string into std::set<std::string> paths
/// in the format "START: 1->2->4->5->END", where -> indicate an ICFGEdge connects two ICFGNode IDs
/// bonus:  dump and append each program path to a `ICFGPaths.txt` in the form of
/// ‘{ln: number cl: number, fl:name} -> {ln: number, cl: number, fl: name} -> {ln:number, cl: number, fl: name}
/// ln : line number  cl: column number fl:file name  for further learning, you can review the code in SVF, SVFUtil
void TaintGraphTraversal::collectICFGPath(std::vector<unsigned> &path){
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


// TODO: Implement your code to parse the two lines from `SrcSnk.txt` in the form of 
// line 1 for sources  "{ api1 api2 api3 }"
// line 2 for sinks    "{ api1 api2 api3 }" 
void TaintGraphTraversal::readSrcSnkFromFile(const string& filename){
    ifstream infile(filename);
    if (!infile.is_open()) {
        SVFUtil::errs() << "Error opening file: " << filename << "\n";
        return;
    }
    string line;
    int lineNumber = 0;
    while (getline(infile, line)) {
        lineNumber++;
        // Remove braces
        size_t start = line.find('{');
        size_t end = line.find('}');
        if (start == string::npos || end == string::npos || start >= end) {
            SVFUtil::errs() << "Invalid format in line " << lineNumber << ": " << line << "\n";
            continue;
        }
        string content = line.substr(start + 1, end - start - 1);
        // Split the content by spaces
        istringstream iss(content);
        string api;
        if (lineNumber == 1) {
            // Sources
            while (iss >> api) {
                checker_source_api.insert(api);
            }
        } else if (lineNumber == 2) {
            // Sinks
            while (iss >> api) {
                checker_sink_api.insert(api);
            }
        } else {
            // Ignore additional lines
            break;
        }
    }
    infile.close();
    
}

/// TODO: Checking aliases of the two variables at source and sink. For example: 
/// src instruction:  actualRet = source();
/// snk instruction:  sink(actualParm,...);
/// return true if actualRet is aliased with any parameter at the snk node (e.g., via ander->alias(..,..))
bool TaintGraphTraversal::aliasCheck(const CallICFGNode *src, const CallICFGNode *snk)
{
    // Get the RetICFGNode corresponding to the source CallICFGNode
    const RetICFGNode* srcRetNode = src->getRetICFGNode();
    if (!srcRetNode) {
        return false;
    }
    // Get the return variable of the source function
    const SVFVar* srcRetVar = srcRetNode->getActualRet();
    if (!srcRetVar || !srcRetVar->hasValue()) {
        return false;
    }
    const SVFValue* svfSrcRetValue = srcRetVar->getValue();
    // Get the NodeID of the return value using SVFValue*
    NodeID srcID = pag->getValueNode(svfSrcRetValue);

    // Get the actual parameters of the sink CallICFGNode
    typedef std::vector<const SVFVar*> SVFVarList;
    const SVFVarList& snkActualParams = snk->getActualParms();
    for (const SVFVar* argVar : snkActualParams) {
        if (!argVar || !argVar->hasValue()) {
            continue;
        }
        const SVFValue* svfArgValue = argVar->getValue();
        NodeID argID = pag->getValueNode(svfArgValue);
        // Check aliasing using Andersen's analysis
        if (ander->alias(srcID, argID)) {
            return true;
        }
    }
    return false;
}
