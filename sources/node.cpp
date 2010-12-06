//@+leo-ver=5-thin
//@+node:gcross.20101205182001.1356: * @thin node.cpp
//@@language cplusplus

//@+<< Includes >>
//@+node:gcross.20101205182001.1357: ** << Includes >>
#include "illuminate/core.hpp"
//@-<< Includes >>

namespace Illuminate {

//@+<< Usings >>
//@+node:gcross.20101205182001.1358: ** << Usings >>
//@-<< Usings >>

//@+others
//@+node:gcross.20101205182001.1365: ** struct Node
//@+node:gcross.20101205182001.1366: *3* (constructors)
Node::Node(const string& name, const Suite* parent)
    : name(name)
    , parent(parent)
    , full_name(
        parent == NULL
            ? name
            : (parent->name + "::" + name)
      )
{ }
//@-others

}
//@-leo
