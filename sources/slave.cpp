//@+leo-ver=5-thin
//@+node:gcross.20110809112154.2441: * @file slave.cpp
//@@language cplusplus
//@+<< License >>
//@+node:gcross.20110809112154.2443: ** << License >>
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

//@+<< Includes >>
//@+node:gcross.20110809112154.2444: ** << Includes >>
#include <boost/archive/archive_exception.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/format.hpp>
#include <boost/make_shared.hpp>
#include <boost/process.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/vector.hpp>
#include <iostream>
#include <sstream>

#include "illuminate/slave.hpp"
#include "illuminate/test_tree.hpp"
//@-<< Includes >>

namespace Illuminate {

//@+<< Usings >>
//@+node:gcross.20110809112154.2445: ** << Usings >>
using boost::archive::text_iarchive;
using boost::archive::text_oarchive;
using boost::format;
using boost::function;
using boost::make_shared;
using boost::none;
using boost::optional;

using std::auto_ptr;
using std::endl;
using std::getline;
using std::istream;
using std::ostream;
using std::ostringstream;
using std::string;
using std::stringstream;
using std::vector;
//@-<< Usings >>

//@+others
//@+node:gcross.20110809112154.2447: ** Values
string const slave_sentinel("<[<[<[***!...MARK...!***]>]>]>");
vector<string> const slave_arguments(1,string("--slave-mode"));

struct SlaveProcessContext : public boost::process::context {
    SlaveProcessContext() {
        stdin_behavior  = boost::process::capture_stream();
        stderr_behavior = boost::process::redirect_stream_to_stdout();
        stdout_behavior = boost::process::capture_stream();
    }
} const slave_process_context;
//@+node:gcross.20110809112154.2467: ** Classes
//@+node:gcross.20110809112154.2490: *3* Process
struct Process : public boost::process::child {
    Process(boost::process::child const& child)
      : boost::process::child(child)
    {}
    ~Process() { terminate(true); }
};
//@+node:gcross.20110809112154.2461: *3* Slave
//@+node:gcross.20110809112154.2477: *4* (constructor)
Slave::Slave() : started(false) {}
//@+node:gcross.20110809112154.2506: *4* (copy)
Slave::Slave(Slave const& other) : started(false) {}
//@+node:gcross.20110809112154.2478: *4* (destructor)
Slave::~Slave() { }
//@+node:gcross.20110809112154.2453: *4* operator()
TestResult Slave::operator()(Test const& test) {
    return (*this)(test.id);    
}

TestResult Slave::operator()(unsigned int test_id) {
    start();
    istream& input_from_slave = getInput();
    ostream& output_to_slave = getOutput();
    string s;
    while (s != slave_sentinel) getline(input_from_slave,s);
    output_to_slave << test_id << endl;
    TestResult result(make_shared<vector<string> >());
    ostringstream log;
    stringstream result_text;
    try {
        string s;
        while(s != slave_sentinel) {
            getline(input_from_slave,s);
            log << s << endl;
        }
        s.clear();
        while(s != slave_sentinel) {
            getline(input_from_slave,s);
            result_text << s << endl;
        }
        text_iarchive(result_text) >> *result;
    } catch(...) {
        optional<int> maybe_status = stop();
        result->push_back(
            (
            format(
                "%1%\n"
                "==============================\n"
                "    STANDARD OUTPUT+ERROR:    \n"
                "==============================\n"
                "%2%\n"
            ) % (maybe_status
                    ? format("Test caused a crash with error code %1%!") % (*maybe_status)
                    : format("Test caused a crash!")
                )
              % log.str()
        ).str());
    }
    return result;
}
//@+node:gcross.20110809112154.2507: *4* operator=
void Slave::operator=(Slave const& _) {
    started = false;
}
//@+node:gcross.20110809112154.2456: *4* start
void Slave::start() {
    if(!started) {
        initiateConnection();
        getInput().exceptions (istream::eofbit | istream::failbit | istream::badbit);
        getOutput().exceptions(ostream::eofbit | ostream::failbit | ostream::badbit);
        started = true;
    }
}
//@+node:gcross.20110809112154.2464: *4* stop
optional<int> Slave::stop() {
    if(started) {
        started = false;
        return terminateConnection();
    }
    return none;
}
//@+node:gcross.20110809112154.2473: *3* SlaveProcess
//@+node:gcross.20110809112154.2475: *4* (constructor)
SlaveProcess::SlaveProcess(string const& executable)
  : executable(make_shared<string const>(executable))
{}
//@+node:gcross.20110809112154.2505: *4* (copy)
SlaveProcess::SlaveProcess(SlaveProcess const& other)
  : Slave(other)
  , executable(other.executable)
{}
//@+node:gcross.20110809112154.2488: *4* (destructor)
SlaveProcess::~SlaveProcess() {}
//@+node:gcross.20110809112154.2483: *4* getInput
istream& SlaveProcess::getInput() {
    return process->get_stdout();
}
//@+node:gcross.20110809112154.2485: *4* getOutput
ostream& SlaveProcess::getOutput() {
    return process->get_stdin();
}
//@+node:gcross.20110809112154.2480: *4* initiateConnection
void SlaveProcess::initiateConnection() {
    process.reset(new Process(boost::process::launch(*executable,slave_arguments,slave_process_context)));
}
//@+node:gcross.20110809112154.2509: *4* operator=
void SlaveProcess::operator=(SlaveProcess const& other) {
    Slave::operator=(*this);
    executable = other.executable;
}
//@+node:gcross.20110809112154.2482: *4* terminateConnection
optional<int> SlaveProcess::terminateConnection() {
    auto_ptr<Process> old_process = process;
    old_process->terminate(true);
    boost::process::status status = old_process->wait();
    if(status.exited())
        return status.exit_status();
    else
        return none;
}
//@+node:gcross.20110809112154.2451: ** Functions
//@+node:gcross.20110809112154.2452: *3* runInSlaveMode
void runInSlaveMode() {
    using std::cerr;
    using std::cin;
    using std::cout;
    Root const& root = getRoot();
    while(true) {
        cout << endl << slave_sentinel << endl; cout.flush();
        unsigned int test_id;
        //text_iarchive(cin) >> test_id;
        cin >> test_id;
        TestResult result = root.lookupTest(test_id)();
        cerr.flush();
        cout.flush();
        cout << slave_sentinel << endl;
        text_oarchive(cout) << *result;
        cout << endl << slave_sentinel << endl;
        cout.flush();
    }
}
//@-others

}
//@-leo
