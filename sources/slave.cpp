// Includes {{{
#include <boost/archive/archive_exception.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/format.hpp>
#include <boost/make_shared.hpp>
#include <boost/process.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/vector.hpp>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <sstream>

#include "illuminate/slave.hpp"
#include "illuminate/test_tree.hpp"
// }}}

// Usings {{{
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
using std::runtime_error;
using std::string;
using std::stringstream;
using std::vector;
// }}}

namespace Illuminate {

// Values {{{
string const slave_sentinel("<[<[<[***!...MARK...!***]>]>]>");
vector<string> const slave_arguments(1,string("--slave-mode"));

struct SlaveProcessContext : public boost::process::context {
    SlaveProcessContext() {
        stdin_behavior  = boost::process::capture_stream();
        stderr_behavior = boost::process::redirect_stream_to_stdout();
        stdout_behavior = boost::process::capture_stream();
        if(getenv("PATH") != NULL) environment["PATH"] = getenv("PATH");
        if(getenv("LIBRARY_PATH") != NULL) environment["LIBRARY_PATH"] = getenv("LIBRARY_PATH");
        if(getenv("LD_LIBRARY_PATH") != NULL) environment["LD_LIBRARY_PATH"] = getenv("LD_LIBRARY_PATH");
        if(getenv("DYLD_LIBRARY_PATH") != NULL) environment["DYLD_LIBRARY_PATH"] = getenv("DYLD_LIBRARY_PATH");
    }
} const slave_process_context;
// }}}

// Classes {{{
struct Process : public boost::process::child { // {{{
    Process(boost::process::child const& child)
      : boost::process::child(child)
    {}
    ~Process() {
        try {
            terminate(true);
        } catch(boost::system::system_error const& _) {
            // This exception is ignored by intention.
        }
    }
}; // }}}
// class Slave {{{
Slave::Slave() : started(false) {}
Slave::Slave(Slave const& other) : started(false) {}
Slave::~Slave() { }
// TestResult Slave::operator(...) {{{
TestResult Slave::operator()(Test const& test) {
    return (*this)(test.id);    
}

using std::cerr;
TestResult Slave::operator()(unsigned int test_id) {
    start();
    istream& input_from_slave = getInput();
    ostream& output_to_slave = getOutput();
    string s;
    {
        ostringstream prelude_log;
        try {
            while (s != slave_sentinel) {
                getline(input_from_slave,s);
                prelude_log << s << endl;
            }
        } catch(...) {
            throw runtime_error(string("Error starting slave process:\n") + prelude_log.str());
        }
    }
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
} // }}}
void Slave::operator=(Slave const& _) { // {{{
    started = false;
} // }}}
void Slave::start() { // {{{
    if(!started) {
        initiateConnection();
        getInput().exceptions (istream::eofbit | istream::failbit | istream::badbit);
        getOutput().exceptions(ostream::eofbit | ostream::failbit | ostream::badbit);
        started = true;
    }
} // }}}
optional<int> Slave::stop() { // {{{
    if(started) {
        started = false;
        return terminateConnection();
    }
    return none;
} // }}}
// }}}
// class SlaveProcess {{{
SlaveProcess::SlaveProcess(string const& executable) // {{{
  : executable(make_shared<string const>(executable))
{} // }}}
SlaveProcess::SlaveProcess(SlaveProcess const& other) // {{{
  : Slave(other)
  , executable(other.executable)
{} // }}}
SlaveProcess::~SlaveProcess() {}
istream& SlaveProcess::getInput() { // {{{
    return process->get_stdout();
} // }}}
ostream& SlaveProcess::getOutput() { // {{{
    return process->get_stdin();
} // }}}
void SlaveProcess::initiateConnection() { // {{{
    process.reset(new Process(boost::process::launch(*executable,slave_arguments,slave_process_context)));
} // }}}
void SlaveProcess::operator=(SlaveProcess const& other) { // {{{
    Slave::operator=(*this);
    executable = other.executable;
} // }}}
optional<int> SlaveProcess::terminateConnection() { // {{{
    auto_ptr<Process> old_process = process;
    old_process->terminate(true);
    boost::process::status status = old_process->wait();
    if(status.exited())
        return status.exit_status();
    else
        return none;
} // }}}
// }}}
// }}}

// Functions {{{
void runInSlaveMode() { // {{{
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
} // }}}
// }}}

}
