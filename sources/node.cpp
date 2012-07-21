// Includes {{{
#include "illuminate/test_tree.hpp"
// }}}

// Usings {{{
using boost::optional;

using std::string;
// }}}

namespace Illuminate {

Node::Node(string const& name, optional<Suite const&> const parent, optional<bool> const skipped)
    : name(name)
    , parent(parent)
    , skipped(
        skipped
            ? *skipped
            : parent
                ? parent->skipped
                : false
      )
{ }

}
