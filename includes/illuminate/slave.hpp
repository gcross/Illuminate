//@+leo-ver=5-thin
//@+node:gcross.20110809112154.2434: * @file slave.hpp
//@@language cplusplus
//@+<< License >>
//@+node:gcross.20110809112154.2436: ** << License >>
//@+at
// ISC License (http://www.opensource.org/licenses/isc-license)
// 
// Copyright (c) 2011, Gregory Crosswhite <gcrosswhite@gmail.com>
// 
// Permission to use, copy, modify, and/or distribute this software for any purpose with or without fee is hereby granted, provided that the above copyright notice and this permission notice appear in all copies.
// 
// THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
//@@c
//@-<< License >>

#ifndef ILLUMINATE_SLAVE_HPP
#define ILLUMINATE_SLAVE_HPP

//@+<< Includes >>
//@+node:gcross.20110809112154.2437: ** << Includes >>
#include <boost/optional.hpp>
#include <iosfwd>
#include <string>
#include <vector>

#include "illuminate/test_tree.hpp"
//@-<< Includes >>

namespace Illuminate {

//@+others
//@+node:gcross.20110809112154.2472: ** Values
extern std::string const slave_sentinel;
extern std::vector<std::string> const slave_arguments;
//@+node:gcross.20110809112154.2458: ** Classes
//@+node:gcross.20110809112154.2459: *3* Slave
class Slave {
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
};
//@+node:gcross.20110809112154.2471: *3* SlaveProcess
//@+<< Forward declarations >>
//@+node:gcross.20110809112154.2489: *4* << Forward declarations >>
class Process;  // Note:  This class is intentionally left opaque in the headers.
//@-<< Forward declarations >>

class SlaveProcess: public Slave {
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
};
//@+node:gcross.20110809112154.2439: ** Functions
//@+node:gcross.20110809112154.2440: *3* runInSlaveMode
void runInSlaveMode();
//@-others

}

#endif
//@-leo
