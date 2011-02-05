//@+leo-ver=5-thin
//@+node:gcross.20101206161648.1606: * @thin main.cpp
//@@language cplusplus

//@+<< Includes >>
//@+node:gcross.20101206161648.1607: ** << Includes >>
#include <boost/program_options.hpp>
#include <fstream>
#include <iostream>

#include "illuminate.hpp"
#include "illuminate/runners.hpp"

namespace po = boost::program_options;

using std::cerr;
using std::cout;
using std::endl;

using namespace Illuminate;
//@-<< Includes >>

//@+others
//@+node:gcross.20101206161648.1609: ** main
int main(int argc, char** argv) {
    // Declare the supported options.
    po::options_description desc("Allowed options");
    desc.add_options()
        ("help", "produce help message\n")
        ("fatal,f", po::value<FatalityMode>(),
            "fatality mode\n"
            "\n"
            "The possible values of this option are:\n"
            "    none:       no problems are fatal (default)\n"
            "    exceptions: exceptions are fatal\n"
            "    all:        all problems are fatal\n"
            "\n"
            "The purpose of this option is to allow you cause the test program to die when it encounters a particular type of problem so that you can more easily examine the stack trace in a debugger.\n"
        )
        ("threads,n", po::value<unsigned int>()->default_value(0),
            "number of threads\n\n"
            "If this value is zero (the default), then the number of threads is equal to the detected number of hardware capabilities.\n\n"
            "If this value is one, then the no threads are spawned but rather the tests are run in the main thread (which might make it easier to analyze stack traces).\n"
        )
    ;

    po::variables_map vm;
    try {
        po::store(po::parse_command_line(argc, argv, desc), vm);
        ifstream config_file("test.cfg");
        po::store(po::parse_config_file(config_file, desc), vm);
    } catch(...) {
        cout << desc << "\n";
        cout << "Options may also be specified in 'test.cfg'" << endl;
        return 1;
    }

    if (vm.count("help")) {
        cout << desc << "\n";
        cout << "Options may also be specified in 'test.cfg'" << endl;
        return 1;
    }

    if (vm.count("fatal")) {
        Test::fatality_mode = vm["fatal"].as<FatalityMode>();
    }

    unsigned int const number_of_threads = vm["threads"].as<unsigned int>();

    switch(number_of_threads) {
        case 0:  runTestsInThreadsAndPrintResults(); break;
        case 1:  runTestsAndPrintResults(); break;
        default: runTestsInThreadsAndPrintResults(number_of_threads); break;
    }

    return 0;
}
//@-others
//@-leo
