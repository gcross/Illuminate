#ifndef ILLUMINATE_SLAVE_HPP
#define ILLUMINATE_SLAVE_HPP

// Includes {{{
#include <boost/optional.hpp>
#include <iosfwd>
#include <string>
#include <vector>

#include "illuminate/test_tree.hpp"
// }}}

namespace Illuminate {

// Values {{{
extern std::string const slave_sentinel;
extern std::vector<std::string> const slave_arguments;
// }}}

// Classes {{{
class Slave { // {{{
public:
    Slave();
    virtual ~Slave();
    TestResult operator()(Test const& test);
    TestResult operator()(unsigned int test_id);
protected:
    bool started;
    Slave(Slave const& other);
    void operator=(Slave const& other);
    void start();
    boost::optional<int> stop();
    virtual void initiateConnection() = 0;
    virtual boost::optional<int> terminateConnection() = 0;
    virtual std::istream& getInput() = 0;
    virtual std::ostream& getOutput() = 0;
}; // }}}

// Forward declarations {{{
class Process;  // Note:  This class is intentionally left opaque in the headers.
// }}}

class SlaveProcess: public Slave { // {{{
public:
    SlaveProcess(std::string const& executable);
    SlaveProcess(SlaveProcess const& other);
    virtual ~SlaveProcess();
    void operator=(SlaveProcess const& other);
protected:
    boost::shared_ptr<std::string const> executable;
    std::auto_ptr<Process> process;
    virtual void initiateConnection();
    virtual boost::optional<int> terminateConnection();
    virtual std::istream& getInput();
    virtual std::ostream& getOutput();
}; // }}}
// }}}

// Functions {{{
void runInSlaveMode();
// }}}

}

#endif
